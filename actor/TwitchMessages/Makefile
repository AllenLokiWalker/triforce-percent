include ../../toolchain/make/main.mk

ACTORNAME = TwitchMessages
ACTORNUM = 116

CCFLAGS += -Wno-missing-braces -Wno-array-bounds

INCFILES = \
	../../textures/username_font.i4.inc \
	../../textures/tw_msg_case0.i4.inc \
	../../textures/tw_msg_case1.i4.inc \
	../../textures/tw_msg_case2.i4.inc \
	../../textures/tw_msg_case3.i4.inc \
	../../textures/tw_msg_exclam.i4.inc \
	../../textures/badges/badges.inc

default: copyactor

$(ACTORNAME).o: ../../loader/fast_loader/fast_loader.h $(INCFILES)

$(ACTORNAME).elf: ../../loader/fast_loader/fast_loader.out.ld

ACTORLDFLAGS += -T ../../loader/fast_loader/fast_loader.out.ld

include ../../toolchain/make/actor.mk
