
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
