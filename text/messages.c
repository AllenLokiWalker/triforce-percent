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

DECLARE_MESSAGE(0x0902, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE QUICKTEXT_ENABLE 
    "Anim loading from RAM"
)

// 0xA00: Ending Sequence (so we can have 0xACE be significant)

// 0xB00: Key of Courage

// 0xC00: Key of Power

// 0xD00: Key of Wisdom

DECLARE_MESSAGE(0x0D20, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE
    "Welcome Link!" NEWLINE
    "I am the " COLOR(BLUE) "Great Fairy of Wisdom" COLOR(WHITE) "." BOX_BREAK
    "You have done well to get here," NEWLINE
    "blah blah blah." BOX_BREAK
    "Bye!"
)

//This one needs to come at the end
DECLARE_MESSAGE(0x0FFF, BOX_BLUE, POS_MIDDLE,
    "Dummy"
)
