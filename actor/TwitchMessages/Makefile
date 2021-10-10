include ../../toolchain/make/main.mk

ACTORNAME = TwitchMessages
ACTORNUM = 116

CCFLAGS += -Wno-missing-braces -Wno-array-bounds

default: copyactor

$(ACTORNAME).o: ../../loader/fast_loader/fast_loader.h

$(ACTORNAME).elf: ../../loader/fast_loader/fast_loader.out.ld

ACTORLDFLAGS += -T ../../loader/fast_loader/fast_loader.out.ld

include ../../toolchain/make/actor.mk
