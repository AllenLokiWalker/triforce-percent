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

DECLARE_MESSAGE(0x086D, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE SHIFT("\x11") "Play using " COLOR(BLUE) "\x9F" COLOR(WHITE) " and " COLOR(YELLOW) "\xA1" COLOR(WHITE) "." NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE OCARINA
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



// Trailer

DECLARE_MESSAGE(0x109D, BOX_NONE_BOTTOM, POS_VARIABLE,
    SHIFT("\x1B") "If you were really good" NEWLINE
    SHIFT("\x24") "at pressing buttons," NEWLINE
    SHIFT("\x23") "what would you do?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x10") "Would you play a game really" NEWLINE
    SHIFT("\x0C") "skillfully, but within the bounds" NEWLINE
    SHIFT("\x14") "intended by the developers?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x12") "Would you perform difficult," NEWLINE
    SHIFT("\x08") "elaborate glitches to skip large" NEWLINE
    SHIFT("\x20") "portions of the game?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x13") "Or would you get a robot," BOX_BREAK_DELAYED("\x28")
    SHIFT("\x1C") "build on two decades of" NEWLINE
    SHIFT("\x19") "reverse engineering work," BOX_BREAK_DELAYED("\x28")
    SHIFT("\x1C") "and glitch your way into" NEWLINE
    SHIFT("\x18") "changing the game's code?" BOX_BREAK_DELAYED("\x28")
    
    SHIFT("\x1E") "If you had the ability" NEWLINE
    SHIFT("\x09") "to rewrite the laws of reality," NEWLINE
    SHIFT("\x23") "what would you do?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x02") "Would you just achieve your goals" NEWLINE
    SHIFT("\x1E") "as quickly as possible?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x14") "Would you erase everything" NEWLINE
    SHIFT("\x0A") "and make something brand new?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x0C") "Or would you make the dreams" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x1E") "of millions of players" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x24") "finally come true?" BOX_BREAK_DELAYED("\x28")
    
    SHIFT("\x10") "If you had the power to make" NEWLINE
    SHIFT("\x0A") "Hyrule however you dreamed it..." BOX_BREAK_DELAYED("\x28")
                  "the attention of thousands of viewers..." BOX_BREAK_DELAYED("\x28")
    SHIFT("\x0A") "and one wish to the Goddesses..." BOX_BREAK_DELAYED("\x28")
    SHIFT("\x04") "would you create something great?" FADE("\x50")
    
)
    

//This one needs to come at the end
DECLARE_MESSAGE(0xFFFF, BOX_BLUE, POS_MIDDLE,
    "Dummy"
)
