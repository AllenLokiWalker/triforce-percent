#include "z64structs.h"
#include "z64funcs.h"
#include "message.h"

extern void Message_LoadJpnMsgInfo();
extern void Message_LoadEngMsgInfo();
extern void Message_LoadStaffMsgInfo();

extern MessageTableEntry *messageTableAddresses[3];

// typedef struct {
//     u8 unk[0x60];
//     s32 (*textCallback)(Font* message);
// } UnkN64DDStruct;
// 
// extern UnkN64DDStruct *n64ddStruct;
// UnkN64DDStruct localN64DDStruct;

// Message Symbol Declarations
#define DECLARE_MESSAGE(textId, type, yPos, message) \
    extern const char _message_ ## textId [];
#include "../../text/messages.c"
#undef DECLARE_MESSAGE

// Message Table Declaration
MessageTableEntry hackMessageTable[] = {
    #define DECLARE_MESSAGE(textId, type, yPos, message) \
        { textId, (((type) << 4) | (yPos)), _message_ ## textId },
    #include "../../text/messages.c"
    #undef DECLARE_MESSAGE
    { 0xFFFF, 0, NULL },
};

// static const u32 messageDataVROM[3] = {
//     0x008EB000, 0x0092D000, 0x00966000 //JP, US, staff
// };

void Statics_LoadMsgInfoPatched(z64_global_t *global, u16 textId, s32 type){
    Font *font = (Font*)((u8*)global + 0x2200);
    MessageTableEntry *tbl;
    const char *baseSeg, *thisSeg, *nextSeg;
    u8 found = 0;
    if(textId >= 0x900 && textId < 0x1000){
        tbl = hackMessageTable;
        baseSeg = 0;
    }else{
        tbl = messageTableAddresses[type];
        baseSeg = tbl->segment;
    }
    
    while(tbl->textId != 0xFFFF){
        if(tbl->textId == textId){
            found = 1;
            break;
        }
        ++tbl;
    }
    if(!found){
        //Text not found, default to Frog
        tbl = messageTableAddresses[type];
        baseSeg = tbl->segment;
        tbl += 0xE;
    }
    thisSeg = tbl->segment;
    font->xy = tbl->typePos;
    ++tbl;
    nextSeg = tbl->segment;
    font->msgOffset = thisSeg - baseSeg;
    font->msgLength = nextSeg - thisSeg;
}

s32 Statics_N64DDTextCallback(Font *message){
    if(!(message->msgOffset & 0x80000000)) return 0; //Actual normal text
    if(message->msgLength > 1000){
        //Something went wrong, default to Frog. Hope we're on US.
        message->msgOffset = messageTableAddresses[1][0xC].segment 
                           - messageTableAddresses[1][0x0].segment;
        message->msgLength = messageTableAddresses[1][0xD].segment 
                           - messageTableAddresses[1][0xC].segment;
        message->xy = messageTableAddresses[1][0xC].typePos;
        return 0;
    }
    bcopy((const void*)message->msgOffset, message->msgBuf, message->msgLength);
    return 1;
}

extern void Message_PostLoadStaffAddr();
extern void Message_PostLoadJpnAddr();
extern void Message_PostLoadEngAddr();

void Statics_MessageCodePatches(){
    //Text loader patches
    *( (u32*)Message_LoadJpnMsgInfo     ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadJpnMsgInfo  )+1) = 0x34060000; //ori a2, zero, 0
    *( (u32*)Message_LoadEngMsgInfo     ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadEngMsgInfo  )+1) = 0x34060001; //ori a2, zero, 1
    *( (u32*)Message_LoadStaffMsgInfo   ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadStaffMsgInfo)+1) = 0x34060002; //ori a2, zero, 2
    //There's already some text patching system in place in the game,
    //presumably for the N64DD. Patch this to call our callback function.
    // if(n64ddStruct == NULL){
    //     n64ddStruct = &localN64DDStruct;
    // }
    // n64ddStruct->textCallback = Statics_N64DDTextCallback;
    *( (u32*)Message_PostLoadStaffAddr   ) = 0; //nop out first nullptr check
    *(((u32*)Message_PostLoadStaffAddr)+2) = 0; //nop out a load from nullptr
    *(((u32*)Message_PostLoadStaffAddr)+4) = 0; //nop out second nullptr check
    *(((u32*)Message_PostLoadStaffAddr)+7) = JALINSTR(Statics_N64DDTextCallback);
    *( (u32*)Message_PostLoadJpnAddr     ) = 0;
    *(((u32*)Message_PostLoadJpnAddr  )+2) = 0;
    *(((u32*)Message_PostLoadJpnAddr  )+4) = 0;
    *(((u32*)Message_PostLoadJpnAddr  )+7) = JALINSTR(Statics_N64DDTextCallback);
    *( (u32*)Message_PostLoadEngAddr     ) = 0;
    *(((u32*)Message_PostLoadEngAddr  )+2) = 0;
    *(((u32*)Message_PostLoadEngAddr  )+4) = 0;
    *(((u32*)Message_PostLoadEngAddr  )+7) = JALINSTR(Statics_N64DDTextCallback);
}
