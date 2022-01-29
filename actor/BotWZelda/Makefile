include ../../toolchain/make/main.mk

ACTORNAME = BotWZelda
ACTORNUM = 121

OBJECTNAME = BotWZeldaObj
OBJECTNUM = 125
OBJECTOBJS = \
	BotWZeldaMesh.o
OBJECTHDRS = \
	BotWZeldaMesh.h
SHDRS = \
	../../loader/debugger/debugger.h \
	../../statics/hairphys.h \
	../../statics/statics.h \
	../../statics/anime.h
LDFILES = \
	$(OBJECTNAME).out.ld \
	../../loader/debugger/debugger.out.ld \
	../../statics/statics.out.ld

default: copyactor copyobject

$(ACTORNAME).o: $(OBJECTHDRS) $(SHDRS)

$(ACTORNAME).elf: $(LDFILES)

ACTORLDFLAGS += $(addprefix -T , $(LDFILES))

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
