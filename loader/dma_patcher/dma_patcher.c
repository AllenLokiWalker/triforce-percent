#include "dma_patcher.h"
#include "../debugger/debugger.h"

typedef u32 OSMesgQueue; typedef u32 OSMesg; //not using them
typedef struct
{
    /* 0x00 */ u32      vromAddr; // VROM address (source)
    /* 0x04 */ void*    dramAddr; // DRAM address (destination)
    /* 0x08 */ u32      size;     // File Transfer size
    /* 0x0C */ char*    filename; // Filename for debugging
    /* 0x10 */ s32      line;     // Line for debugging
    /* 0x14 */ s32      unk_14;
    /* 0x18 */ OSMesgQueue* notifyQueue; // Message queue for the notification message
    /* 0x1C */ OSMesg   notifyMsg;       // Completion notification message
} DmaRequest; // size = 0x20

typedef struct
{
    /* 0x00 */ u32 vromStart;
    /* 0x04 */ u32 vromEnd;
    /* 0x08 */ u32 romStart;
    /* 0x0C */ u32 romEnd; 
} DmaEntry;

extern DmaEntry* gDmaDataTable;

// DmaPatcher RAM

typedef struct
{
    u32 vrom;
    u8* patch;
} DmaPatchEntry;

#define DMAPATCHER_MAXPATCHES 1024

typedef struct
{
    u32 npatches;
    u32 dummy1;
    u32 dummy2;
    u32 dummy3;
    DmaPatchEntry patches[DMAPATCHER_MAXPATCHES];
} DmaPatcher_t;

static DmaPatcher_t patcher;

static void DmaPatcher_ProcessMsg(DmaRequest* req);

__attribute__((section(".start"))) void DmaPatcher_Init()
{
    s32 i = __osDisableInt();
    patcher.npatches = 0;
    // Patch DmaMgr_ProcessMsg to jump to DmaPatcher_ProcessMsg
	*((u32*)0x80000B0C) = 0x08000000 | ( ( ((u32)DmaPatcher_ProcessMsg) >> 2 ) & 0x03FFFFFF );
	*((u32*)0x80000B10) = 0; //nop
    __osRestoreInt(i);
}

void DmaPatcher_AddPatch(u32 vrom, u8* patch)
{
    s32 i = __osDisableInt();
    if(patcher.npatches >= DMAPATCHER_MAXPATCHES){
        Debugger_Printf("AddPatch %08X: Too many patches!", vrom);
    }else{
        patcher.patches[patcher.npatches].vrom = vrom;
        patcher.patches[patcher.npatches].patch = patch;
        ++patcher.npatches;
    }
    __osRestoreInt(i);
}

void DmaPatcher_ReplaceFile(u32 filenum, u32 injectedAddr)
{
    gDmaDataTable[filenum].romStart = injectedAddr;
}

static void DmaPatcher_ApplyPatch(u32 ram, u32 size, u8* patch)
{
    u8 skipcount, writecount;
    u8* ptr = (u8*)ram;
    u8* ptrend = (u8*)ram + size;
    while(1){
        skipcount = *patch++;
        writecount = *patch++;
        if(!skipcount && !writecount) return;
        ptr += skipcount;
        if(ptr + writecount > ptrend){
            Debugger_Printf("Patch to %08X overflowing file sz %X!", ram, size);
            return;
        }
        while(writecount--) *ptr++ = *patch++;
    }
}

static void DmaPatcher_ProcessMsg(DmaRequest* req)
{
    u32 vrom = req->vromAddr;
    u32 ram = (u32)req->dramAddr;
    u32 size = req->size;
    u32 romStart;
    u32 romSize;
    u32 copyStart;
    u32 p;
    DmaEntry* iter = gDmaDataTable;
    
    while(iter->vromEnd){
        if(vrom >= iter->vromStart && vrom < (iter+1)->vromStart){
            //It's in this file
            //Changed from originally checking between vromStart and vromEnd
            //because this way we can patch files to be bigger than they
            //originally were, as long as the file is always loaded starting
            //from its start.
            if(vrom + size > iter->vromEnd){
                Debugger_Printf("DMA @%08X sz %X off end %08X", vrom, size, iter->vromEnd);
                return;
            }
            romStart = iter->romStart;
            copyStart = romStart + (vrom - iter->vromStart);
            if(romStart & 0x80000000){
                //The file is actually in RAM, copy it
                _memcpy((void*)ram, (void*)copyStart, size);
                return;
            }
            romStart &= 0x7FFFFFFF;
            copyStart &= 0x7FFFFFFF;
            if(iter->romEnd == 0){
                //Uncompressed file
                DmaMgr_DMARomToRam(copyStart, ram, size);
            }else{
                romSize = iter->romEnd - romStart;
                if(copyStart != romStart || size != romSize){
                    Debugger_Printf("DMA @%08X middle of compressed file %08X", copyStart, romStart);
                }
                osSetThreadPri(0, 0x0A);
                Yaz0_Decompress(romStart, ram, romSize);
                osSetThreadPri(0, 0x10);
            }
            //Patch file after loading
            for(p=0; p<patcher.npatches; ++p){
                if(patcher.patches[p].vrom == vrom){
                    DmaPatcher_ApplyPatch(ram, size, patcher.patches[p].patch);
                    return;
                }
            }
            return;
        }
        ++iter;
    }
    Debugger_Printf("DMA %08X not found", vrom);
    DmaMgr_DMARomToRam(vrom, ram, size);
}
