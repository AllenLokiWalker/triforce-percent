#include "ootmain.h"
#include "audio.h"

//These max values come from the sizes of the LoadStatus fields in AudioContext
#define MAX_SEQS 0x80
#define MAX_BANKS 0x30
#define NUM_ORIG_SEQS 0x6E
#define NUM_ORIG_BANKS 0x26

#define SEQ_OVERTUREOFSAGES_LEARN (NUM_ORIG_SEQS+0)
#define SEQ_OVERTUREOFSAGES_WARP  (NUM_ORIG_SEQS+1)
#define SEQ_AWAKENINGTHESAGES     (NUM_ORIG_SEQS+2)
#define SEQ_OBTAINTHETRIFORCE     (NUM_ORIG_SEQS+3)
#define SEQ_POWEROFTHEGODS        (NUM_ORIG_SEQS+4)
#define SEQ_INITSPEECH1           (NUM_ORIG_SEQS+5)
#define SEQ_INITSPEECH2           (NUM_ORIG_SEQS+6)
#define SEQ_AVOICETOTHEHEAVENS    (NUM_ORIG_SEQS+7)
#define SEQ_STAFFROLL             (NUM_ORIG_SEQS+8)

// For normal seqs: 2 bytes for u16 offset, 1 byte for length (1), 1 byte for bank
// Some seqs have 2 banks, so add a bit after that
// Original size is 0x1C0
#define NEW_SEQBANKSMAP_SIZE (4 * MAX_SEQS + 32)

typedef struct {
    /* 0x0000 */ s16 entryCnt;
    /* 0x0002 */ s16 unk_02;
    /* 0x0004 */ u32 romAddr;
    /* 0x0008 */ char pad[0x8];
} AudioIndexHeader; // size = 0x10

typedef struct {
    /* 0x0000 */ u32 addr;
    /* 0x0004 */ u32 size;
    /* 0x0008 */ s8 loadLocation;
    /* 0x0009 */ s8 seqPlayerIdx;
    //Following used in Audiobank Index only, in others all zeros
    /* 0x000A */ u8 audiotableIdx;
    /* 0x000B */ u8 unk_0B; //0xFF
    /* 0x000C */ u8 numInst;
    /* 0x000D */ u8 numDrum;
    /* 0x000E */ u8 unk_0E; //0x00
    /* 0x000F */ u8 numSfx;
} AudioIndexEntry; // size = 0x10

typedef struct {
    AudioIndexHeader header;
    AudioIndexEntry entries[MAX_SEQS];
} AudioIndex;

typedef struct {
    u8 dummy[0x1E18];
    OSPiHandle* cartHandle;
    OSPiHandle* unk_1E1C;
    u8 dummy2[(0x2830-0x1E20)];
    AudioIndex* audioseqIndex;
    AudioIndex* audiobankIndex;
    AudioIndex* audiotableIndex;
    u8* seqBanksMap;
    u16 seqTabEntCnt;
    CtlEntry* gCtlEntries;
    u8 dummy3[(0x2984-0x2848)];
    volatile s32 resetTimer;
} FakeAudioContext;

static AudioIndex NewAudioseqIndex;
static AudioIndex NewAudiobankIndex;
static CtlEntry NewCtlEntries[MAX_BANKS];
static u8 NewSeqBanksMap[NEW_SEQBANKSMAP_SIZE];
static u16 SeqBanksMapWriteOffset;

extern FakeAudioContext gFakeAudioContext;

extern s32 (*sDmaHandler)(OSPiHandle* handle, OSIoMesg* mb, s32 direction);

extern void Audio_DMA();

static s32 Patched_AudioDMA(OSIoMesg* mesg, u32 priority, s32 direction, u32 devAddr,
    void* ramAddr, u32 size, OSMesgQueue* reqQueue, s32 handleType)
{
    if(gFakeAudioContext.resetTimer > 0x10) return -1;
    
    size = (size + 0xF) & ~0xF;
    
    if(devAddr >= 0x04000000 && devAddr < 0x04800000){
        //Injected data
        osYieldThread();
        bcopy(InjectRomRamMap(devAddr), ramAddr, size);
        osSendMesg(reqQueue, NULL, OS_MESG_NOBLOCK);
        return 0;
    }
    
    OSPiHandle* handle;
    if(handleType == 2) handle = gFakeAudioContext.cartHandle;
    else if(handleType == 3) handle = gFakeAudioContext.unk_1E1C;
    else return 0;
    
    mesg->hdr.pri = priority;
    mesg->hdr.retQueue = reqQueue;
    mesg->dramAddr = ramAddr;
    mesg->devAddr = devAddr;
    mesg->size = size;
    handle->transferInfo.cmdType = 2;
    sDmaHandler(handle, mesg, direction);
    return 0;
}

static inline void CopyReplaceIndex(AudioIndex** origIdx, AudioIndex* newIdx, u32 entries)
{
    bcopy((const void*)*origIdx, (void*)newIdx, 
        sizeof(AudioIndexHeader) + entries * sizeof(AudioIndexEntry));
    *origIdx = newIdx;
}

extern void func_800E3034(s32 bank);

void Statics_AudioCodePatches(u8 isLiveRun)
{
    s32 i = __osDisableInt();
    CopyReplaceIndex(&gFakeAudioContext.audioseqIndex, &NewAudioseqIndex, NUM_ORIG_SEQS);
    CopyReplaceIndex(&gFakeAudioContext.audiobankIndex, &NewAudiobankIndex, NUM_ORIG_BANKS);
    // Banks have metadata copied to gCtlEntries, by func_800E3034 / InitCtlTable
    // This is probably a holdover of the older audio subsystem where the bank metadata
    // was stored at the beginning of the bank (i.e. needs DMA), not in a table in code
    // This is originally allocated from the audio pool, but we need to make it bigger
    bcopy(gFakeAudioContext.gCtlEntries, NewCtlEntries, sizeof(CtlEntry) * NUM_ORIG_BANKS);
    gFakeAudioContext.gCtlEntries = NewCtlEntries;
    // Copy and expand seqBanksMap
    SeqBanksMapWriteOffset = 2 * MAX_SEQS;
    s32 seq = 0;
    for(; seq<NUM_ORIG_SEQS; ++seq){
        u16 readoffset = ((u16*)gFakeAudioContext.seqBanksMap)[seq];
        u8 numBanks = gFakeAudioContext.seqBanksMap[readoffset++];
        ((u16*)&NewSeqBanksMap)[seq] = SeqBanksMapWriteOffset;
        NewSeqBanksMap[SeqBanksMapWriteOffset++] = numBanks;
        for(u8 b=0; b<numBanks; ++b){
            NewSeqBanksMap[SeqBanksMapWriteOffset++] = gFakeAudioContext.seqBanksMap[readoffset++];
        }
    }
    for(; seq<MAX_SEQS; ++seq){
        ((u16*)&NewSeqBanksMap)[seq] = 0;
    }
    gFakeAudioContext.seqBanksMap = NewSeqBanksMap;
    // Patch Audio_DMA
    *( (u32*)Audio_DMA   ) = JUMPINSTR(Patched_AudioDMA);
    *(((u32*)Audio_DMA)+1) = 0;
    __osRestoreInt(i);
}

void Statics_AudioRegisterStaticData(void* ram_addr, s32 size, 
    u8 type, s32 data1, s32 data2)
{
    AudioIndex* index;
    if(type == 1) index = &NewAudioseqIndex;
    else if(type == 2) index = &NewAudiobankIndex;
    else return;
    u8 idx = (data1 >> 24) & 0xFF;
    //Fix counts
    if(index->header.entryCnt <= idx){
        index->header.entryCnt = idx + 1;
    }
    if(type == 1 && gFakeAudioContext.seqTabEntCnt <= idx){
        gFakeAudioContext.seqTabEntCnt = idx + 1;
    }
    //Write data to index
    AudioIndexEntry* entry = &index->entries[idx];
    entry->addr = InjectRamRomMap(ram_addr);
    entry->size = size;
    entry->loadLocation = (data1 >> 16) & 0xFF;
    entry->seqPlayerIdx = (data1 >>  8) & 0xFF;
    if(type == 1){
        u8 numBanks = data1 & 0xFF;
        u8 oldNumBanks = 0x69;
        u16 offset = ((u16*)NewSeqBanksMap)[idx];
        if(offset != 0){
            oldNumBanks = NewSeqBanksMap[offset++];
        }
        if(numBanks == oldNumBanks){
            for(u8 b=0; b<numBanks; ++b){
                NewSeqBanksMap[offset++] = (data2 >> 24) & 0xFF;
                data2 <<= 8;
            }
        }else{
            ((u16*)NewSeqBanksMap)[idx] = SeqBanksMapWriteOffset;
            NewSeqBanksMap[SeqBanksMapWriteOffset++] = numBanks;
            for(u8 b=0; b<numBanks; ++b){
                NewSeqBanksMap[SeqBanksMapWriteOffset++] = (data2 >> 24) & 0xFF;
                data2 <<= 8;
            }
        }
    }else if(type == 2){
        entry->audiotableIdx = data1 & 0xFF;
        entry->unk_0B = 0xFF;
        entry->numInst = (data2 >> 24) & 0xFF;
        entry->numDrum = (data2 >> 16) & 0xFF;
        entry->unk_0E = 0;
        entry->numSfx = (data2 >>  8) & 0xFF;
        //Need to update the copy of metadata in gCtlEntries
        func_800E3034(idx);
    }
}
