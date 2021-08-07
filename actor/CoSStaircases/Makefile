include ../../toolchain/make/main.mk

ACTORNAME = cosstaircases
ACTORNUM = 26
ACTORLDFLAGS += -T ../../scene/ChamberOfSages/ChamberOfSages_scene.out.ld

OBJECTNAME = cosstaircasesobj
OBJECTNUM = 17
OBJECTOBJS = \
	RauruStair.o \
	RauruStairCollision.o \
	SariaStair.o \
	SariaStairCollision.o \
	SheikStair.o \
	SheikStairCollision.o \
	TriforceFadeWall.o \
	TriforceHallway.o \
	TriforceHallwayCollision.o \
	TriforceDoor.o \
	TriforceDoorCollision.o

default: copyactor copyobject

$(ACTORNAME).elf: $(OBJECTNAME).out.ld

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
