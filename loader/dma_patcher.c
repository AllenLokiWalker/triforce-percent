
typedef unsigned long long u64;
typedef          long long s64;
typedef unsigned int u32;
typedef          int s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char u8;
typedef          char s8;

typedef u32 OSMesgQueue; //since we're not using it
typedef u32 OSMesg; //again not using it

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

void memcpy(void* dest, void* src, u32 size)
{
    if(!((u32)dest & 0x7) && !((u32)src & 0x7) && !(size & 0x7)){
        //All multiple of 8 bytes
        u64* dest64 = (u64*)dest;
        u64* src64 = (u64*)src;
        while(size){
            *dest64++ = *src64++;
            size -= 8;
        }
        return;
    }
    u8* dest8 = (u8*)dest;
    u8* src8 = (u8*)src;
    while(size--) *dest8++ = *src8++;
}

void DmaPatcher_Error(const char* message)
{
    //TODO
}

void DmaPatcher_ProcessMsg(DmaRequest* req)
{
    u32 vrom = req->vromAddr;
    u32 ram = (u32)req->dramAddr;
    u32 size = req->size;
    u32 romStart;
    u32 romSize;
    u32 copyStart;
    u32 patchFlags;
    DmaEntry* iter = gDmaDataTable;
    
    while(iter->vromEnd){
        if(vrom >= iter->vromStart && vrom < (iter+1)->vromStart){
            //It's in this file
            //Changed from originally checking between vromStart and vromEnd
            //because this way we can patch files to be bigger than they
            //originally were, as long as the file is always loaded starting
            //from its start.
            if(vrom + size > iter->vromEnd){
                DmaPatcher_Error("Tried to load off end of file!");
                return;
            }
            romStart = iter->romStart & 0x3FFFFFFF;
            patchFlags = (iter->romStart & 0xC0000000) >> 30;
            copyStart = romStart + (vrom - iter->vromStart);
            if(patchFlags & 2){
                //The file is actually in RAM, copy it
                memcpy((void*)ram, (void*)(copyStart | 0x80000000), size);
                return;
            }
            if(iter->romEnd == 0){
                //Uncompressed file
                DmaMgr_DMARomToRam(copyStart, ram, size);
            }else{
                romSize = iter->romEnd - romStart;
                if(copyStart != romStart || size != romSize){
                    DmaPatcher_Error("Tried to load only portion of compressed file!");
                }
                osSetThreadPri(0, 0x0A);
                Yaz0_Decompress(romStart, ram, romSize);
                osSetThreadPri(0, 0x10);
            }
            if(patchFlags & 1){
                //The file needs to be patched after loading
                //TODO
            }
        }
        ++iter;
    }
}
