include ../../toolchain/make/main.mk

ACTORNAME = BotWLink
ACTORNUM = 118

OBJECTNAME = BotWLinkObj
OBJECTNUM = 122
OBJECTOBJS = BotWLinkMesh.o BotWLinkMeshIdleAnim.o BotWLinkMeshBobokuwaAnim.o

default: copyactor copyobject

$(ACTORNAME).elf: $(OBJECTNAME).out.ld

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld -T ../../statics/statics.out.ld -T ../../loader/debugger/debugger.out.ld

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
