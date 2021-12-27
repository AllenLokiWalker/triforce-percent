include ../../toolchain/make/main.mk

ACTORNAME = BotWLink
ACTORNUM = 118

OBJECTNAME = BotWLinkObj
OBJECTNUM = 122
OBJECTOBJS = BotWLinkMesh.o BotWLinkMeshIdleAnim.o BotWLinkMeshBobokuwaAnim.o BotWLinkMeshHeadmoveAnim.o

default: copyactor copyobject

BotWLink.o: ../../statics/statics.h ../../statics/hairphys.h ../../loader/debugger/debugger.h BotWLinkMesh.h BotWLinkMeshIdleAnim.h BotWLinkMeshBobokuwaAnim.h

$(ACTORNAME).elf: $(OBJECTNAME).out.ld

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld -T ../../statics/statics.out.ld -T ../../loader/debugger/debugger.out.ld

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
