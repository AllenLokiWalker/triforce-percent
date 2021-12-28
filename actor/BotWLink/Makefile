include ../../toolchain/make/main.mk

ACTORNAME = BotWLink
ACTORNUM = 118

OBJECTNAME = BotWLinkObj
OBJECTNUM = 122
OBJECTOBJS = \
	BotWLinkMesh.o \
	BotWLinkMeshIdleAnim.o \
	BotWLinkMeshBobokuwaAnim.o \
	BotWLinkMeshHeadmoveAnim.o
OBJECTHDRS = \
	BotWLinkMesh.h \
	BotWLinkMeshIdleAnim.h \
	BotWLinkMeshBobokuwaAnim.h \
	BotWLinkMeshHeadmoveAnim.h
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
