#include "ootmain.h"
#include "audio.h"

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
    /* 0x000B */ u8 unk_0D; //0xFF
    /* 0x000C */ u8 numInst;
    /* 0x000D */ u8 numDrum;
    /* 0x000E */ u8 unk_0E; //0x00
    /* 0x000F */ u8 numSfx;
} AudioIndexEntry; // size = 0x10

typedef struct {
    AudioIndexHeader header;
    AudioIndexEntry entries[0x80];
} AudioIndex;

typedef struct {
    u8 dummy[0x1E18];
    OSPiHandle* cartHandle;
    OSPiHandle* unk_1E1C;
    u8 dummy2[(0x2830-0x1E20)];
    AudioIndex* audioseqIndex;
    AudioIndex* audiobankIndex;
    AudioIndex* audiotableIndex;
    u8 dummy3[(0x2984-0x283C)];
    volatile s32 resetTimer;
} FakeAudioContext;

#define NUM_ORIG_SEQS 0x6E
#define NUM_ORIG_BANKS 0x26
static AudioIndex NewAudioseqIndex;
static AudioIndex NewAudiobankIndex;

extern FakeAudioContext gAudioContext;

extern s32 (*sDmaHandler)(OSPiHandle* handle, OSIoMesg* mb, s32 direction);

extern void Audio_DMA();

static s32 Patched_AudioDMA(OSIoMesg* mesg, u32 priority, s32 direction, u32 devAddr,
    void* ramAddr, u32 size, OSMesgQueue* reqQueue, s32 handleType)
{
    if(gAudioContext.resetTimer > 0x10) return -1;
    
    size = (size + 0xF) & ~0xF;
    
    if(devAddr >= 0x04000000 && devAddr < 0x04800000){
        //Injected data
        osYieldThread();
        z_bcopy(InjectRomRamMap(devAddr), ramAddr, size);
        osSendMesg(reqQueue, NULL, OS_MESG_NOBLOCK);
        return 0;
    }
    
    OSPiHandle* handle;
    if(handleType == 2) handle = gAudioContext.cartHandle;
    else if(handleType == 3) handle = gAudioContext.unk_1E1C;
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

void Statics_AudioCodePatches(u8 isLiveRun)
{
    CopyReplaceIndex(&gAudioContext.audioseqIndex, &NewAudioseqIndex, NUM_ORIG_SEQS);
    CopyReplaceIndex(&gAudioContext.audiobankIndex, &NewAudiobankIndex, NUM_ORIG_BANKS);
    s32 i = __osDisableInt();
    // Patch Audio_DMA
    *( (u32*)Audio_DMA   ) = JUMPINSTR(Patched_AudioDMA);
    *(((u32*)Audio_DMA)+1) = 0;
    // finally
    __osRestoreInt(i);
}
