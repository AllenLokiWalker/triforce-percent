include ../../toolchain/make/main.mk

ACTORNAME = cosstaircases
ACTORNUM = 26

default: copyactor

$(ACTORNAME).elf: $(OBJECTNAME).out.ld $(SCENEOUTLD)

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld -T $(SCENEOUTLD)

include ../../toolchain/make/actor.mk
