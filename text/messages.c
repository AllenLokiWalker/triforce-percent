// 0x900: Debugging

DECLARE_MESSAGE(0x0900, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x6B") QUICKTEXT_ENABLE
    "You got the " COLOR(YELLOW) "Triforce" COLOR(WHITE) "!!!" QUICKTEXT_DISABLE NEWLINE
    "After 22 years, the dreams of" NEWLINE
    "millions of players around the" NEWLINE
    "world have finally come true!"
)

DECLARE_MESSAGE(0x0901, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x35") QUICKTEXT_ENABLE 
    "Frog"
)

DECLARE_MESSAGE(0x0902, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE QUICKTEXT_ENABLE 
    "Anim loading from RAM"
)

// 0xB00: Key of Courage

// 0xC00: Key of Power

// 0xD00: Key of Wisdom

DECLARE_MESSAGE(0x0D20, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Welcome Link!" NEWLINE
    "I am the " COLOR(LIGHTBLUE) "Great Fairy of Wisdom" COLOR(WHITE) "." BOX_BREAK
    "You have done well to get here," NEWLINE
    "blah blah blah."
)

DECLARE_MESSAGE(0x0D21, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "This is the final key to the Sacred" NEWLINE
    "Realm, representing the wisdom in" NEWLINE
    "your heart."
)

DECLARE_MESSAGE(0x0871, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE SHIFT("\x11") "Play the " COLOR(LIGHTBLUE) "Overture of Sages" COLOR(WHITE) "!" NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE OCARINA
)

DECLARE_MESSAGE(0x0074, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE  
    SHIFT("\x28") "You have learned the" NEWLINE
    SHIFT("\x29") COLOR(LIGHTBLUE) "Overture of Sages" COLOR(WHITE) "!!"
)

DECLARE_MESSAGE(0x0894, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE SHIFT("\x07") "You played the " COLOR(LIGHTBLUE) "Overture of Sages" COLOR(WHITE) "." NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE
)

DECLARE_MESSAGE(0x088E, BOX_BLACK, POS_MIDDLE,
    QUICKTEXT_ENABLE COLOR(LIGHTBLUE) "Warp to the Sacred Realm?" COLOR(WHITE) QUICKTEXT_DISABLE NEWLINE NEWLINE
    TWO_CHOICE COLOR(GREEN) "OK" NEWLINE
    "No" COLOR(WHITE)
)

DECLARE_MESSAGE(0x0D23, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Link, I believe you know now what" NEWLINE
    "you must do."
)

// 0xA00: Ending Sequence (so we can have 0xACE be significant)



//This one needs to come at the end
DECLARE_MESSAGE(0xFFFF, BOX_BLUE, POS_MIDDLE,
    "Dummy"
)
