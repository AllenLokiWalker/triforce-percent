include ../../toolchain/make/main.mk

ACTORNAME = TestCelShading
ACTORNUM = 117

OBJECTNAME = TestCelShadingObj
OBJECTNUM = 121
OBJECTOBJS = TestCelShadingMesh.o TestCelShadingMoveAnim.o

default: copyactor copyobject

$(ACTORNAME).o: TestCelShadingMesh.h TestCelShadingMoveAnim.h

$(ACTORNAME).elf: $(OBJECTNAME).out.ld

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
