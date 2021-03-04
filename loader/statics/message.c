#include "message.h"
#include "statics_int.h"

typedef enum {
    BOX_BLACK,
    BOX_WOODEN,
    BOX_BLUE,
    BOX_OCARINA,
    BOX_NONE_BOTTOM,
    BOX_NONE_NO_SHADOW,
    BOX_CREDITS = 11
} MessageBoxType;

typedef enum {
    POS_VARIABLE,
    POS_TOP,
    POS_BOTTOM,
    POS_MIDDLE
} MessageBoxPosition;

typedef struct {
    u32 msgOffset;
    u32 msgLength;
    u8 xy;
} Font;

typedef struct {
    u16 textId;
    u8 typePos;
    const char* segment;
} MessageTableEntry;

extern MessageTableEntry *messageTableAddresses[3];
extern void Message_LoadJpnMsgInfo();
extern void Message_LoadEngMsgInfo();
extern void Message_LoadStaffMsgInfo();

// Message Symbol Declarations
#define DECLARE_MESSAGE(textId, type, yPos, message) \
    extern const char _message_##textId##[];
#include "../../text/messages.c"
#undef DECLARE_MESSAGE

// Message Table Declaration
MessageTableEntry hackMessageTable[] = {
    #define DECLARE_MESSAGE(textId, type, yPos, message) \
        { textId, (((type) << 4) | (yPos)), _message_##textId## },
    #include "../../text/messages.c"
    #undef DECLARE_MESSAGE
    { 0xFFFF, 0, NULL },
};

static const u32 messageDataVROM[3] = {
    0x008EB000, 0x0092D000, 0x00966000 //JP, US, staff
};

void Statics_LoadMsgInfoPatched(z64_global_t *global, u16 textId, s32 type){
    Font *font = (Font*)((u8*)global + 0x2200);
    MessageTableEntry *tbl;
    const char *baseSeg, *thisSeg, *nextSeg;
    u8 found = 0;
    if(textId >= 0x900 && textId < 0x1000){
        tbl = hackMessageTable;
        //vromLoad = vromUsMessage + hackMessageTable[textId].segment - baseSeg
        //Want vromLoad = 0x04000000 + hackMessageTable[textId].segment - 0x80000000
        //0x80000000 + vromUsMessage - 0x04000000 = baseSeg
        baseSeg = 0x80000000 - 0x04000000 + messageDataVROM[type];
    }else{
        tbl = messageTableAddresses[type];
        baseSeg = tbl->segment;
    }
    
    while(tbl->textId != 0xFFFF){
        if(tbl->textId == textId){
            found = 1;
            break;
        }
    }
    if(!found){
        //Text not found, default to Frog
        tbl = messageTableAddresses[type];
        baseSeg = tbl->segment;
        tbl += 0xD;
    }
    thisSeg = tbl->segment;
    font->xy = tbl->typePos;
    ++tbl;
    nextSeg = tbl->segment;
    font->msgOffset = thisSeg - baseSeg;
    font->msgLength = nextSeg - thisSeg;
}

void Statics_MessageCodePatches(){
    //Text loader patches
    *( (u32*)Message_LoadJpnMsgInfo     ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadJpnMsgInfo  )+1) = 0x34060000; //ori a2, zero, 0
    *( (u32*)Message_LoadEngMsgInfo     ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadEngMsgInfo  )+1) = 0x34060001; //ori a2, zero, 1
    *( (u32*)Message_LoadStaffMsgInfo   ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadStaffMsgInfo)+1) = 0x34060002; //ori a2, zero, 2
}
