
typedef struct {
    u8 dummy[0x20];
} DmaRequest;

typedef struct {
    u8 dummy1[0x138];
    /* 0x0138 */ u8*    icon_itemSegment;
    u8 dummy2[0x160 - 0x13C];
    /* 0x0160 */ DmaRequest dmaRequest_160;
    /* 0x0180 */ DmaRequest dmaRequest_180;
    /* 0x01A0 */ char   unk_1A0[0x20];
    /* 0x01C0 */ OSMesgQueue loadQueue;
    /* 0x01D8 */ OSMesg loadMsg;
    u8 dummy3[0x270 - 0x1DC];
} InterfaceContext; // size = 0x270

extern void DmaMgr_SendRequest2(DmaRequest *req, u8 *dest, u32 rom, u32 size, 
    s32 unk, OSMesgQueue *queue, s32 unk2);

extern void Interface_LoadItemIcon1(z64_global_t *globalCtx, u16 button);
extern void Interface_LoadItemIcon2(z64_global_t *globalCtx, u16 button);

extern void Construct_Icon_Start();
extern void Construct_Icon_Target();
