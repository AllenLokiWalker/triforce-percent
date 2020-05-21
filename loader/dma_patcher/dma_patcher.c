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

extern DmaEntry gDmaDataTable[];

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

__attribute__((section(".start"))) void DmaPatcher_Init()
{
    Debugger_Printf("DmaPatcher loaded");
    s32 i = __osDisableInt();
    patcher.npatches = 0;
    // Patch DmaMgr_ProcessMsg to jump to DmaPatcher_ProcessMsg
	*((u32*)0x80000B0C) = 0x08000000 | ( ( ((u32)DmaPatcher_ProcessMsg) >> 2 ) & 0x03FFFFFF );
	*((u32*)0x80000B10) = 0; //nop
    /*
    //Debugging: Copy original DmaMgr_ProcessMsg code to somewhere on expansion pack
    //and then patch the original one to jump to it
#define DUMMY_DMAMGR_LOC 0x80410000
    _memcpy((void*)DUMMY_DMAMGR_LOC, (const void*)0x80000B0C, 0xCA8-0xB0C);
    *((u32*)0x80000B0C) = 0x08000000 | ((DUMMY_DMAMGR_LOC >> 2) & 0x03FFFFFF);
	*((u32*)0x80000B10) = 0; //nop
    */
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

void DmaPatcher_ReplaceFile(u32 filenum, void* injectedAddr)
{
    gDmaDataTable[filenum].romStart = (u32)injectedAddr;
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

void DmaPatcher_ProcessMsg(DmaRequest* req)
{
    u32 vrom = req->vromAddr;
    void* ram = req->dramAddr;
    u32 size = req->size;
    u32 romStart, romSize, copyStart, p;
    DmaEntry* iter = gDmaDataTable;
    while (iter->vromEnd) {
        if(vrom >= iter->vromStart && vrom < (iter+1)->vromStart){
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
                _memcpy((void*)ram, (void*)copyStart, size);
                Debugger_Printf("DMA @%08X replaced file", vrom);
                return;
            }
            if (iter->romEnd == 0) {
                DmaMgr_DMARomToRam(copyStart, ram, size);
            }else{
                romSize = iter->romEnd - romStart;
                if(copyStart != romStart || size != romSize){
                    Debugger_Printf("!! DMA @%08X middle of compressed file %08X", copyStart, romStart);
                }
                osSetThreadPri(NULL, 0x0A);
                Yaz0_Decompress(romStart, ram, romSize);
                osSetThreadPri(NULL, 0x10);
            }
            //Patch file after loading
            for(p=0; p<patcher.npatches; ++p){
                if(patcher.patches[p].vrom == vrom){
                    Debugger_Printf("DMA @%08X patching file", vrom);
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


#if 0
    //Working homebrewed version, less than half the length of the original
    asm(".set noat\n .set noreorder\n"
    //a0 = req (for now); at, t9 temps
    "lw      $a1, 0x0004($a0)\n" //a1 = dramAddr
    "lw      $a2, 0x0008($a0)\n" //a2 = size
    "lw      $a3, 0x0000($a0)\n" //a3 = vromAddr
    "lui     $v0, 0x8001\n"
    "addiu   $v0, $v0, 0xB130\n" //v0 = iter = 8000B140 (gDmaDataTable) - 0x10
"lbl_loop:\n"
    "addiu   $v0, $v0, 0x0010\n"
    "lw      $t1, 0x0004($v0)\n" //t1 = vromEnd
    "beq     $t1, $zero, lbl_notfound\n"
    "lw      $t0, 0x0000($v0)\n" //t0 = vromStart
    "sltu    $at, $a3, $t0\n"    //if(vromAddr < iter->vromStart)
    "bne     $at, $zero, lbl_loop\n"
    "sltu    $t9, $a3, $t1\n"    //if(vromAddr >= iter->vromEnd)
    "beq     $t9, $zero, lbl_loop\n"
    "lw      $t3, 0x000C($v0)\n" //t3 = romEnd
    "lw      $t2, 0x0008($v0)\n" //t2 = romStart
    "bne     $t3, $zero, lbl_compressed\n"
    "addu    $t9, $t2, $a3\n"    //t9 = iter->romStart + req->vromAddr
    "j       DmaMgr_DMARomToRam\n"//DmaMgr_DMARomToRam(iter->romStart + (vrom - iter->vromStart), ram, size);
	"subu    $a0, $t9, $t0\n"    //a0 = t9 - iter->vromStart
"lbl_compressed:\n"
    "addiu   $sp, $sp, 0xFFF0\n"
    "sw      $ra, 0x0000($sp)\n"
    "sw      $t2, 0x0004($sp)\n" //romStart
    "sw      $a1, 0x0008($sp)\n" //dramAddr
    "subu    $t9, $t3, $t2\n" //romSize = romEnd - romStart
    "sw      $t9, 0x000C($sp)\n" //romSize
    "or      $a0, $zero, $zero\n" //a0 = 0
	"jal     osSetThreadPri\n"
	"addiu   $a1, $zero, 0x000A\n"//a1 = 0A
	"lw      $a0, 0x0004($sp)\n" //romStart
	"lw      $a1, 0x0008($sp)\n" //dramAddr
	"jal     Yaz0_Decompress\n"  //Yaz0_Decompress(romStart, ram, romSize);
	"lw      $a2, 0x000C($sp)\n" //romSize
    "lw      $ra, 0x0000($sp)\n"
    "addiu   $sp, $sp, 0x0010\n"
    "or      $a0, $zero, $zero\n" //a0 = 0
	"j       osSetThreadPri\n"
	"addiu   $a1, $zero, 0x0010\n"//a1 = 0x10
"lbl_notfound:\n"
    "j       DmaMgr_DMARomToRam\n"//DmaMgr_DMARomToRam(vrom, ram, size);
    "or      $a0, $a3, $zero\n"//a0 = vromAddr
    ".set at");

    //This one works
    asm(".set noat\n .set noreorder\n"
    "addiu   $sp, $sp, 0xFFC0             \n"//## $sp = FFFFFFC0
	"lui     $a2, 0x8001                  \n"//
	"addiu   $a2, $a2, 0xB140             \n"//## $a2 = 8000B140 = gDmaDataTable
	"sw      $ra, 0x001C($sp)             \n"//
	"sw      $s0, 0x0018($sp)             \n"//
	"lw      $t6, 0x0004($a0)             \n"//## $t6 = req->dramAddr
	"lw      $s0, 0x0000($a0)             \n"//## $s0 = req->vromAddr
	"lw      $t8, 0x0004($a2)             \n"//## iter->vromEnd
	"sw      $t6, 0x0038($sp)             \n"//## 0x38 = dramAddr
	"lw      $t7, 0x0008($a0)             \n"//## $t7 = req->size
	"or      $a1, $zero, $zero            \n"//## $a1 = found = 0
	"or      $v1, $zero, $zero            \n"//## v1 = 00000000
	"or      $v0, $a2, $zero              \n"//## v0 = 8000B140 = iter
	"beq     $t8, $zero, lbl_80000C58     \n"//## if(gDmaDataTable->vromEnd == 0) goto endloop
	"sw      $t7, 0x0034($sp)             \n"//## 0x34 = size
	"lw      $a3, 0x0000($v0)             \n"//## $a3 = iter->vromStart
"lbl_80000B4C:                            \n"//
	"sltu    $at, $s0, $a3                \n"//## if(vromAddr < iter->vromStart)
	"bne     $at, $zero, lbl_80000C3C     \n"//##    nextloop
	"nop                                  \n"//
	"lw      $a0, 0x0004($v0)             \n"//## $a0 = iter->vromEnd
	"sltu    $at, $s0, $a0                \n"//## if(vromAddr >= iter->vromEnd)
	"beq     $at, $zero, lbl_80000C3C     \n"//##    nextloop
	"nop                                  \n"//
	"lw      $a1, 0x000C($v0)             \n"//## $a1 = iter->romEnd
	"lw      $t9, 0x0034($sp)             \n"//## $t8 = size
	"bne     $a1, $zero, lbl_80000BBC     \n"//## if(iter->romEnd != 0) goto compressed
	"nop                                  \n"//"addu    $t0, $s0, $t9                \n"//## $t0 = req->vromAddr + size
	//"nop                                  \n"//"sltu    $at, $a0, $t0                \n"//## if(iter->vromEnd >= req->vromAddr + size)
	//"nop                                  \n"//"beq     $at, $zero, lbl_80000B9C     \n"//##   goto no_error_uncompressed
	//"nop                                  \n"//"lui     $a0, 0x8000                  \n"//
	//"nop                                  \n"//"addiu   $a0, $a0, 0x6594             \n"//## $a0 = 80006594 #pointer to error string
	//"nop                                  \n"//"addiu   $a1, $zero, 0x023F           \n"//## $a1 = 0000023F #line number
	//"nop                                  \n"//"jal     DmaMgr_Error                 \n"
	//"nop                                  \n"//"sw      $v0, 0x0024($sp)             \n"//
	//"nop                                  \n"//"lw      $v0, 0x0024($sp)             \n"//## restore v0 == iter
	//"nop                                  \n"//"lw      $a3, 0x0000($v0)             \n"//## restore $a3 = iter->vromStart
//"lbl_80000B9C:                            \n"//## no_error_uncompressed:
	"lw      $t1, 0x0008($v0)             \n"//## $t1 = iter->romStart
	"lw      $a1, 0x0038($sp)             \n"//## $a1 = dramAddr
	"lw      $a2, 0x0034($sp)             \n"//## $a2 = size
	"addu    $t2, $t1, $s0                \n"//## $t2 = iter->romStart + req->vromAddr
	"jal     DmaMgr_DMARomToRam           \n"//## DmaMgr_DMARomToRam(iter->romStart + (vrom - iter->vromStart), ram, size);
	"subu    $a0, $t2, $a3                \n"//## $a0 = iter->romStart + req->vromAddr - iter->vromStart
	"beq     $zero, $zero, lbl_80000C58   \n"//## break, goto endloop
	"addiu   $a1, $zero, 0x0001           \n"//## $a1 = found = 1

"lbl_80000BBC:                            \n"//## compressed:
	"lw      $v1, 0x0008($v0)             \n"//## 00000008
	"subu    $t3, $a1, $v1                \n"//
	"sw      $t3, 0x002C($sp)             \n"//
	//"nop                                  \n"//"beq     $s0, $a3, lbl_80000BF0       \n"//
	"sw      $v1, 0x0030($sp)             \n"//
	//"nop                                  \n"//"lui     $a0, 0x8000                  \n"//
	//"nop                                  \n"//"addiu   $a0, $a0, 0x65A4             \n"//## $a0 = 800065A4 #pointer to error string
	//"nop                                  \n"//"addiu   $a1, $zero, 0x0253           \n"//## $a1 = 00000253 #line number
	//"nop                                  \n"//"jal     DmaMgr_Error                 \n"
	//"nop                                  \n"//"sw      $v0, 0x0024($sp)             \n"//
	//"nop                                  \n"//"lw      $v0, 0x0024($sp)             \n"//
	//"nop                                  \n"//"lw      $a3, 0x0000($v0)             \n"//## 00000000
	//"nop                                  \n"//"lw      $a0, 0x0004($v0)             \n"//## 00000004
//"lbl_80000BF0:                            \n"//
	//"nop                                  \n"//"lw      $t4, 0x0034($sp)             \n"//
	//"nop                                  \n"//"subu    $t5, $a0, $a3                \n"//
	//"nop                                  \n"//"lui     $a0, 0x8000                  \n"//## $a0 = 80000000
	//"nop                                  \n"//"beq     $t4, $t5, lbl_80000C0C       \n"//
	//"nop                                  \n"//"addiu   $a0, $a0, 0x65B4             \n"//## $a0 = 800065B4
	//"nop                                  \n"//"jal     DmaMgr_Error                 \n"
	//"nop                                  \n"//"addiu   $a1, $zero, 0x0259           \n"//## $a1 = 00000259
//"lbl_80000C0C:                            \n"//
	"or      $a0, $zero, $zero            \n"//## $a0 = 00000000
	"jal     osSetThreadPri               \n"//## osSetThreadPri
	"addiu   $a1, $zero, 0x000A           \n"//## $a1 = 0000000A
	"lw      $a0, 0x0030($sp)             \n"//
	"lw      $a1, 0x0038($sp)             \n"//
	"jal     Yaz0_Decompress              \n"//## Yaz0_Decompress(romStart, ram, romSize);
	"lw      $a2, 0x002C($sp)             \n"//
	"or      $a0, $zero, $zero            \n"//## $a0 = 00000000
	"jal     osSetThreadPri               \n"//## osSetThreadPri
	"addiu   $a1, $zero, 0x0010           \n"//## $a1 = 00000010
	"beq     $zero, $zero, lbl_80000C58   \n"//
	"addiu   $a1, $zero, 0x0001           \n"//## $a1 = 00000001
    
"lbl_80000C3C:                            \n"//nextloop:
	"beql    $v1, $zero, lbl_80000C4C     \n"//
	"lw      $t6, 0x0014($v0)             \n"//## 00000014
	"addiu   $v1, $v1, 0x0004             \n"//## v1 = 00000004
	"lw      $t6, 0x0014($v0)             \n"//## 00000014
"lbl_80000C4C:                            \n"//
	"addiu   $v0, $v0, 0x0010             \n"//## v0 = 00000010
	"bnel    $t6, $zero, lbl_80000B4C     \n"//
	"lw      $a3, 0x0000($v0)             \n"//## 00000010

"lbl_80000C58:                            \n"//## endloop:
	"bne     $a1, $zero, lbl_80000C94     \n"//if found, return
	"lui     $t7, 0x8000                  \n"//## $t7 = 80000000
	"lw      $t7, 0x6278($t7)             \n"//## 80006278
	"or      $a0, $s0, $zero              \n"//## $a0 = 00000000
	"lw      $a1, 0x0038($sp)             \n"//
	"beq     $t7, $zero, lbl_80000C8C     \n"// if !sDmaMgrDataExistError, goto DmaMgr_DMARomToRam
	"nop                                  \n"// else error
	//"nop                                  \n"//"lui     $a0, 0x8000                  \n"//
	//"nop                                  \n"//"addiu   $a0, $a0, 0x65C4             \n"//## $a0 = 800065C4 #pointer to error string
	//"nop                                  \n"//"jal     DmaMgr_Error                 \n"
	//"nop                                  \n"//"addiu   $a1, $zero, 0x026D           \n"//## $a1 = 0000026D #line number
	"beq     $zero, $zero, lbl_80000C98   \n"//
	"lw      $ra, 0x001C($sp)             \n"//
    
"lbl_80000C8C:                            \n"//
	"jal     DmaMgr_DMARomToRam           \n"//## DmaMgr_DMARomToRam(vrom, ram, size);
	"lw      $a2, 0x0034($sp)             \n"//
"lbl_80000C94:                            \n"//
	"lw      $ra, 0x001C($sp)             \n"//
"lbl_80000C98:                            \n"//
	"lw      $s0, 0x0018($sp)             \n"//
	"addiu   $sp, $sp, 0x0040             \n"//## $sp = 00000000
	"jr      $ra                          \n"//
	"nop                                  \n"//
".set at");

    //Attempt at replicating original
    u32 vrom;
    void* ram;
    u32 size;
    u32 romStart;
    u32 romSize;
    u8 found;
    DmaEntry* iter;

    vrom = req->vromAddr;
    ram = req->dramAddr;
    size = req->size;
    found = 0;
    iter = gDmaDataTable;

    while (iter->vromEnd) {
        if (vrom >= iter->vromStart && vrom < iter->vromEnd) {
            if (iter->romEnd == 0) {
                DmaMgr_DMARomToRam(iter->romStart + (vrom - iter->vromStart), ram, size);
                found = 1;
            } else {
                romStart = iter->romStart;
                romSize = iter->romEnd - iter->romStart;
                osSetThreadPri(NULL, 0x0A);
                Yaz0_Decompress(romStart, ram, romSize);
                osSetThreadPri(NULL, 0x10);
                found = 1;
            }
            break;
        }
        iter++;
    }
    if (!found) {
        DmaMgr_DMARomToRam(vrom, ram, size);
    }

    //First hack
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
            /*
            if(vrom + size > iter->vromEnd){
                Debugger_Printf("DMA @%08X sz %X off end %08X", vrom, size, iter->vromEnd);
                return;
            }
            */
            romStart = iter->romStart;
            copyStart = romStart + (vrom - iter->vromStart);
            /*
            if(romStart & 0x80000000){
                //The file is actually in RAM, copy it
                _memcpy((void*)ram, (void*)copyStart, size);
                return;
            }
            romStart &= 0x7FFFFFFF;
            copyStart &= 0x7FFFFFFF;
            */
            if(iter->romEnd == 0){
                //Uncompressed file
                DmaMgr_DMARomToRam(copyStart, ram, size);
            }else{
                romSize = iter->romEnd - romStart;
                /*
                if(copyStart != romStart || size != romSize){
                    Debugger_Printf("DMA @%08X middle of compressed file %08X", copyStart, romStart);
                }
                */
                osSetThreadPri(0, 0x0A);
                Yaz0_Decompress(romStart, ram, romSize);
                osSetThreadPri(0, 0x10);
            }
            /*
            //Patch file after loading
            for(p=0; p<patcher.npatches; ++p){
                if(patcher.patches[p].vrom == vrom){
                    DmaPatcher_ApplyPatch(ram, size, patcher.patches[p].patch);
                    return;
                }
            }
            */
            return;
        }
        ++iter;
    }
    //Debugger_Printf("DMA %08X not found", vrom);
    DmaMgr_DMARomToRam(vrom, ram, size);
    
#endif
