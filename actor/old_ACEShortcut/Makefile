PROGRAM = ACEShortcut
OVLOUT = actor.zovl
ADDRESS = 0x80800000
ACTORDIR = ../../build-shortcut/actor/130
PARTS = $(PROGRAM).o

CC   = mips64-gcc
LD   = mips64-ld
NOVL = novl

CCFLAGS = -G 0 -Os --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = -T $(Z64OVLLD) --emit-relocs
NOVLFLAGS = -v -c -A $(ADDRESS) -o $(OVLOUT)

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf
	cp $(OVLOUT) $(ACTORDIR)/
	cp conf.txt $(ACTORDIR)/
	touch $(ACTORDIR)/../../update.txt

clean:
	rm -fv $(PROGRAM).elf $(OVLOUT) $(PARTS)
