include ../../toolchain/make/main.mk

ACTORNAME = nabooru
ACTORNUM = 34

default: copyactor

$(ACTORNAME).o: object_nb.h gerudoway_cs.c gerudoway_cs.h ../../statics/statics.h

$(ACTORNAME).elf: object_nb.ld ../../statics/statics.out.ld

ACTORLDFLAGS += -T object_nb.ld -T ../../statics/statics.out.ld

include ../../toolchain/make/actor.mk
