#ifndef __DMA_PATCHER_H__
#define __DMA_PATCHER_H__

#include "../common/common.h"
#include "../common/z_functions.h"


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

// DmaPatcher code

void DmaPatcher_ProcessMsg(DmaRequest* req);


#endif //__DMA_PATCHER_H__
