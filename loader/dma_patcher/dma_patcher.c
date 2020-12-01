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

//Table starts in RAM 0x8000B140
//First empty line after end of table 0x80010FA0 --i.e. 0x5E6 (1510) lines in table
//Next data after empty space 0x800110A0--i.e. 16 blank lines
extern DmaEntry gDmaDataTable[];
#define N_DMADATA 0x5E6

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

void DmaPatcher_ProcessMsg(DmaRequest* req);
void DmaPatcher_PatchAudio_Pre();
void DmaPatcher_PatchAudio_Post();

__attribute__((section(".start"))) void DmaPatcher_Init()
{
    Debugger_Printf("DmaPatcher loaded");
    s32 i = __osDisableInt();
    patcher.npatches = 0;
    // Patch DmaMgr_ProcessMsg to jump to DmaPatcher_ProcessMsg
	*((u32*)0x80000B0C) = 0x08000000 | ( ( ((u32)DmaPatcher_ProcessMsg) >> 2 ) & 0x03FFFFFF );
	*((u32*)0x80000B10) = 0;
	// Patch Sound_LoadFile to jump to DmaPatcher_PatchAudio_Pre and _Post
	*((u32*)0x800B806C) = 0x08000000 | ( ( ((u32)DmaPatcher_PatchAudio_Pre) >> 2 ) & 0x03FFFFFF );
	*((u32*)0x800B8184) = 0x08000000 | ( ( ((u32)DmaPatcher_PatchAudio_Post) >> 2 ) & 0x03FFFFFF );
    /*
	// Add another line to dmadata that maps 8 MiB of VROM after end to entire RAM
	gDmaDataTable[N_DMADATA].vromStart   = 0x04000000;
	gDmaDataTable[N_DMADATA].vromEnd     = 0x04800000;
	gDmaDataTable[N_DMADATA].romStart    = 0x80000000;
	gDmaDataTable[N_DMADATA+1].vromStart = 0x04800000;
	gDmaDataTable[N_DMADATA+1].vromEnd   = 0;
    */
    __osRestoreInt(i);
}

void DmaPatcher_AddPatch(u32 vrom, u8* patch)
{
    s32 i = __osDisableInt();
    if(patcher.npatches >= DMAPATCHER_MAXPATCHES){
        Debugger_Printf("AddPatch %08X: Too many patches!", vrom);
    }else{
        //Debugger_Printf("AddPatch %d VROM %08X inj %08X", patcher.npatches+1, vrom, patch);
        patcher.patches[patcher.npatches].vrom = vrom;
        patcher.patches[patcher.npatches].patch = patch;
        ++patcher.npatches;
    }
    __osRestoreInt(i);
}

void DmaPatcher_ReplaceFile(u32 filenum, void* injectedAddr, u32 newsize)
{
    s32 i = __osDisableInt();
    gDmaDataTable[filenum].romStart = (u32)injectedAddr;
    gDmaDataTable[filenum].vromEnd = gDmaDataTable[filenum].vromStart + newsize;
    __osRestoreInt(i);
}

static void DmaPatcher_ApplyPatch(u8* ram, u32 size, u8* patch)
{
    u8 skipcount, writecount;
    u8* ptr = ram;
    u8* ptrend = ram + size;
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

void DmaPatcher_PatchAudio_Impl(u32 vrom, void* ram, u32 size)
{
	u32 p;
    //Debugger_Printf("Audio DMA %08X sz %04X", vrom, size);
	for(p=0; p<patcher.npatches; ++p){
		if(patcher.patches[p].vrom == vrom){
			//Debugger_Printf("Audio DMA @%08X patching file", vrom);
			DmaPatcher_ApplyPatch(ram, size, patcher.patches[p].patch);
			return;
		}
	}
}

void DmaPatcher_PatchAudio_Pre()
{
	asm(".set noat\n .set noreorder\n"
	//a0 = romaddr, a1 = ramaddr, a2 = size
    //Store them onto the stack, in their "original" (optimized out) positions
    "sw      $a0, 0x0050($sp)\n"
    "sw      $a1, 0x0054($sp)\n"
    "sw      $a2, 0x0058($sp)\n"
    "j       0x800B8074\n" //three instructions into the function
    "sw      $s2, 0x0038($sp)\n"
    ".set at\n .set reorder");
}

void DmaPatcher_PatchAudio_Post()
{
	asm(".set noat\n .set noreorder\n"
    "lw      $a0, 0x0000($sp)\n"
    "lw      $a1, 0x0004($sp)\n"
	"j       DmaPatcher_PatchAudio_Impl\n"
    "lw      $a2, 0x0008($sp)\n"
    ".set at\n .set reorder");
}

void DmaPatcher_ProcessMsg(DmaRequest* req)
{
    u32 vrom = req->vromAddr;
    void* ram = req->dramAddr;
    u32 size = req->size;
    u32 romStart, vromSize, copyStart, p;
    DmaEntry* iter = gDmaDataTable;
    if(vrom >= 0x04000000 && vrom < 0x04800000){
        //Debugger_Printf("DMA %08X VROM RAM map", vrom);
        _memcpy(ram, (void*)(0x80000000 + ((s32)vrom - 0x04000000)), size);
        return;
    }
    while (iter->vromEnd) {
        if(vrom >= iter->vromStart && (vrom < (iter+1)->vromStart || vrom < iter->vromEnd)){
            //It's in this file
            //Changed from originally checking between vromStart and vromEnd
            //because this way we can patch files to be bigger than they
            //originally were, as long as the file is always loaded starting
            //from its start.
            if(vrom + size > iter->vromEnd){
                Debugger_Printf("!! DMA @%08X sz %X off end %08X", vrom, size, iter->vromEnd);
            }
            romStart = iter->romStart;
            copyStart = romStart + (vrom - iter->vromStart);
            if(romStart & 0x80000000){
                //The file is actually in RAM, copy it
                _memcpy(ram, (void*)copyStart, size);
                //Debugger_Printf("DMA @%08X replaced file", vrom);
                return;
            }
            if (iter->romEnd == 0) {
                DmaMgr_DMARomToRam(copyStart, ram, size);
            }else{
                if(copyStart != romStart){
                    Debugger_Printf("!! DMA @%08X middle of compressed file %08X", copyStart, romStart);
                }
                vromSize = iter->vromEnd - iter->vromStart;
                if(size != vromSize){
                    Debugger_Printf("!! DMA @%08X wrong size %08X should be %08X", size, vromSize);
                }
                osSetThreadPri(NULL, 0x0A);
                Yaz0_Decompress(romStart, ram, iter->romEnd - romStart); //romSize
                osSetThreadPri(NULL, 0x10);
            }
            //Patch file after loading
            for(p=0; p<patcher.npatches; ++p){
                if(patcher.patches[p].vrom == vrom){
                    //Debugger_Printf("DMA @%08X patching file", vrom);
                    DmaPatcher_ApplyPatch(ram, size, patcher.patches[p].patch);
                    return;
                }
            }
            return;
        }
        ++iter;
    }
    Debugger_Printf("!! DMA @%08X not found", vrom);
    DmaMgr_DMARomToRam(vrom, ram, size);
}
