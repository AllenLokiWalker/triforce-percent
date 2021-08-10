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

DECLARE_MESSAGE(0x0A10, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Welcome, Link. I'm Rauru, the" NEWLINE
    "ancient Sage of Light." BOX_BREAK UNSKIPPABLE
    "Now that you hold the keys to the" NEWLINE
    "three sacred virtues, your heart" NEWLINE
    "is in perfect balance."
)

DECLARE_MESSAGE(0x0A11, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "The song you just played has" NEWLINE
    "awakened the other Sages, and they" NEWLINE
    "are on their way to joining us here." BOX_BREAK UNSKIPPABLE
    "You must receive a blessing from" NEWLINE
    "each of us." BOX_BREAK UNSKIPPABLE
    "Together, we will open the way to" NEWLINE
    "your goal!"
)

DECLARE_MESSAGE(0x0A20, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(GREEN)
    "Link, the promise I made to you" NEWLINE
    "stays true. I will always be your" NEWLINE
    "friend."
)

DECLARE_MESSAGE(0x0A30, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(RED)
    "The bond between the Goron race" NEWLINE
    "and the Royal Family is rock solid!" NEWLINE
    "Let's go, brother!"
)

DECLARE_MESSAGE(0x0A40, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(BLUE)
    "I knew the hero would turn out" NEWLINE
    "to be a handsome man!" BOX_BREAK UNSKIPPABLE COLOR(BLUE)
    "Once this is all over, you must" NEWLINE
    "come visit me, all right?"
)

DECLARE_MESSAGE(0x0A50, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(TYPE1_ORANGE)
    "Nice work! It looks like our" NEWLINE
    "song worked for you. From all the" NEWLINE
    "Gerudos, you have our support!"
)

DECLARE_MESSAGE(0x0A60, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(TYPE1_PURPLE)
    "Undoubtedly, you are the boy" NEWLINE
    "from the forest who appeared" NEWLINE
    "in Princess Zelda's dreams." BOX_BREAK UNSKIPPABLE COLOR(TYPE1_PURPLE)
    "I am glad my charm found its" NEWLINE
    "way into your hands." BOX_BREAK UNSKIPPABLE COLOR(TYPE1_PURPLE)
    "I wish you well in fulfilling the" NEWLINE
    "great destiny that is before you."
)

//  "text text text text text text te"

// Trailer

/*
DECLARE_MESSAGE(0x109D, BOX_NONE_BOTTOM, POS_VARIABLE,
    SHIFT("\x1B") "If you were really good" NEWLINE
    SHIFT("\x24") "at pressing buttons," NEWLINE
    SHIFT("\x23") "what would you do?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x10") "Would you play a game really" NEWLINE
    SHIFT("\x0B") "skillfully, but within the bounds" NEWLINE
    SHIFT("\x14") "intended by the developers?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x12") "Would you perform difficult," NEWLINE
    SHIFT("\x08") "elaborate glitches to skip large" NEWLINE
    SHIFT("\x20") "portions of the game?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x13") "Or would you get a robot," BOX_BREAK_DELAYED("\x28")
    SHIFT("\x1B") "build on two decades of" NEWLINE
    SHIFT("\x18") "reverse engineering work," BOX_BREAK_DELAYED("\x28")
    SHIFT("\x1B") "and glitch your way into" NEWLINE
    SHIFT("\x17") "changing the game's code?" BOX_BREAK_DELAYED("\x28")
    
    SHIFT("\x21") "If you had the ability" NEWLINE
    SHIFT("\x0A") "to rewrite the laws of reality," NEWLINE
    SHIFT("\x24") "what would you do?" BOX_BREAK_DELAYED("\x28")
                  "Would you just achieve your goals" NEWLINE
    SHIFT("\x1F") "as quickly as possible?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x15") "Would you erase everything" NEWLINE
    SHIFT("\x09") "and make something brand new?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x09") "Or would you make the dreams" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x20") "of millions of players" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x27") "finally come true?" BOX_BREAK_DELAYED("\x28")
    
    SHIFT("\x0D") "If you had the power to make" NEWLINE
    SHIFT("\x07") "Hyrule however you dreamed it..." BOX_BREAK_DELAYED("\x28")
                  "the attention of thousands of viewers..." BOX_BREAK_DELAYED("\x28")
    SHIFT("\x08") "and one wish to the Goddesses..." BOX_BREAK_DELAYED("\x28")
    SHIFT("\x02") "would you create something great?" FADE("\x50")
)
*/

DECLARE_MESSAGE(0x109D, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x42") "Triforce%" NEWLINE NEWLINE
    SHIFT("\x28") "OoT ACE Showcase" 
    QUICKTEXT_DISABLE BOX_BREAK_DELAYED("\x28")
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE
    SHIFT("\x18")   "Sauraen"    SHIFT("\x36") "Savestate"     NEWLINE
    SHIFT("\x20")    "/zel/"     SHIFT("\x40") "CDi-Fails"     NEWLINE
    SHIFT("\x14")  "rankaisija"  SHIFT("\x3A") "z64me"         NEWLINE
    SHIFT("\x0D") "TerusTheBird" SHIFT("\x25") "Kim-SukLey"    NEWLINE
    SHIFT("\x15")   "MrCheeze"   SHIFT("\x26") "RebeccaETripp" NEWLINE
    SHIFT("\x1E")    "Yukloj"    SHIFT("\x48") "Zero"          NEWLINE
    SHIFT("\x0B")  "AeroArtwork" SHIFT("\x26") "musket012"
    QUICKTEXT_DISABLE BOX_BREAK_DELAYED("\x28")
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x3E") "AGDQ 2022"
    QUICKTEXT_DISABLE BOX_BREAK_DELAYED("\x28")
    "dummy"
)
    

//This one needs to come at the end
DECLARE_MESSAGE(0xFFFF, BOX_BLUE, POS_MIDDLE,
    "Dummy"
)
