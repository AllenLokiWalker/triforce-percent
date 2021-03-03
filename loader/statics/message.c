#include "message.h"

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

void Statics_LoadMsgInfoPatched(z64_global_t *global, u16 textId, s32 type){
    Font *font = (Font*)((u8*)global + 0x2200);
    MessageTableEntry *tbl;
    const char *baseSeg, *thisSeg, *nextSeg;
    u8 found = 0;
    if(textId >= 0x900 && textId < 0x1000){
        tbl = hackMessageTable;
    }else{
        tbl = messageTableAddresses[type];
    }
    
    baseSeg = tbl->segment;
    while(tbl->textId != 0xFFFF){
        if(tbl->textId == textId){
            found = 1;
            break;
        }
    }
    if(!found){
        //Text not found, default to Frog
        tbl = normalTextAddr;
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
