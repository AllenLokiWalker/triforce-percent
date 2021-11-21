#define AdsrEnvelope BADAdsrEnvelope
#define AdpcmLoop BADAdpcmLoop
#define AdpcmBook BADAdpcmBook
#define AudioBankSample BADAudioBankSample
#define AudioBankSound BADAudioBankSound
#define Instrument BADInstrument
#define Drum BADDrum

#include "ootmain.h"

#undef AdsrEnvelope
#undef AdpcmLoop
#undef AdpcmBook
#undef AudioBankSample
#undef AudioBankSound
#undef Instrument
#undef Drum

#include "audio.h"
#include "../toolchain/AudiobankToC/include/audiobank.h"

#define link_demo_1_32Table NULL
#define link_demo_2_32Table NULL
#define link_demo_3_32Table NULL

#include "../voice/link_demo_1_32.c"
#include "../voice/link_demo_2_32.c"
#include "../voice/link_demo_3_32.c"

#define NUM_CUST_SAMPLES 3
AudioBankSample *cust_samples[NUM_CUST_SAMPLES] = {
    &link_demo_1_32Sample,
    &link_demo_2_32Sample,
    &link_demo_3_32Sample,
};
float cust_sample_tuning[NUM_CUST_SAMPLES] = {
    1.0f,
    1.0f,
    1.0f
};
s32 sound_replace_offset[NUM_CUST_SAMPLES] = {
    0x1660 + 8*23, // EN_GANON_LAUGH
    0x1660 + 8*24, // EN_GANON_VOICE_DEMO
    0x1660 + 8*25, // EN_GANON_THROW
};
u8 cust_sample_bank_idx[NUM_CUST_SAMPLES] = {
    1, 1, 1,
};
s32 bank_ram_addr[2] = {
    0x80192A10, // Master Bank
    0x80191260  // Actor Bank
};
#define AUDIOTABLE_01_ROM 0x00079470
#define AUDIOTABLE_2_ROM (AUDIOTABLE_01_ROM + 0x3FA9E0)
#define AUDIOTABLE_3_ROM (AUDIOTABLE_01_ROM + 0x4006B0)
#define AUDIOTABLE_4_ROM (AUDIOTABLE_01_ROM + 0x41D760)
#define AUDIOTABLE_5_ROM (AUDIOTABLE_01_ROM + 0x427D30)
#define AUDIOTABLE_6_ROM (AUDIOTABLE_01_ROM + 0x4377E0)

#include "bankdata.c"

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

#define Audio_SeqCmd1(playerIdx, a) Audio_QueueSeqCmd(0x100000FF | ((u8)playerIdx << 24) | ((u8)(a) << 16))

extern void Message_Use_PlayFanfare();

void Patched_PlayWarpSong(u16 song)
{
    if(song == 0x33){ // Bolero of Fire -> Overture of Sages
        func_800F5E18(0, song, 0, 7, -1); // Main internal start sequence, on player 0
        Audio_SeqCmd1(1, 0); // Stop player 1
    }else{
        func_800F5C64(song); // Normal play fanfare on player 1
    }
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
    // Patch play warp song, originally Audio_PlayFanfare in z_message_PAL
    *((u32*)Message_Use_PlayFanfare) = JALINSTR(Patched_PlayWarpSong);
    // Patch instruments in Master Bank
    AudioBank *bank0 = (AudioBank*)(bank_ram_addr[0]);
    bank0->instruments[83] = &Shehnai_Inst; //replacing accordion
    bank0->instruments[85] = &Choir_Inst; //replacing Malon
    __osRestoreInt(i);
}

void Statics_AudioRegisterSample(void* ram_addr, s32 cspl)
{
    if(cspl < 0 || cspl >= NUM_CUST_SAMPLES) return;
    AudioBankSound *replaceSound = (AudioBankSound*)(
        bank_ram_addr[cust_sample_bank_idx[cspl]] + sound_replace_offset[cspl]);
    replaceSound->sample = cust_samples[cspl];
    replaceSound->tuning = cust_sample_tuning[cspl];
    cust_samples[cspl]->sampleAddr = (u8*)(InjectRamRomMap(ram_addr));
}

void Statics_AudioRegisterStaticData(void* ram_addr, s32 size, 
    u8 type, s32 data1, s32 data2)
{
    AudioIndex* index;
    if(type == 1) index = &NewAudioseqIndex;
    else if(type == 2) index = &NewAudiobankIndex;
    else if(type == 3){
        Statics_AudioRegisterSample(ram_addr, data1);
        return;
    }else return;
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
