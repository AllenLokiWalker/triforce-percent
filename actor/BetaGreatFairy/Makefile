PROGRAM = betagreatfairy
ADDRESS = 0x80800000
ACTORDIR = ../../build-romhack/actor/6
PARTS = $(PROGRAM).o
SCENELD = ../../scene/UnicornFountain/UnicornFountain_scene.out.ld

CC   = mips64-gcc
LD   = mips64-ld
NOVL = novl

CFLAGS = -G 0 -Os --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = -T $(Z64OVLDIR)/z64ovl.ld -T $(SCENELD) --emit-relocs
NOVLFLAGS = -v -c -A $(ADDRESS) -o $(PROGRAM).zovl

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PARTS) $(SCENELD)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf
	rm -f $(ACTORDIR)/actor.zovl
	cp $(PROGRAM).zovl conf.txt $(ACTORDIR)/
	touch $(ACTORDIR)/../../update.txt

clean:
	rm -fv $(PROGRAM).elf $(OVLOUT) $(PARTS)
