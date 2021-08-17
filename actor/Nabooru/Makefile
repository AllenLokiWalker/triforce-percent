include ../../toolchain/make/main.mk

ACTORNAME = nabooru
ACTORNUM = 34

default: copyactor

$(ACTORNAME).o: object_nb.h

$(ACTORNAME).elf: object_nb.ld

ACTORLDFLAGS += -T object_nb.ld

include ../../toolchain/make/actor.mk
