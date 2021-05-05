PROGRAM = hack_wonder_item
ADDRESS = 0x80A66210
PARTS = $(PROGRAM).o

CC   = mips64-gcc
LD   = mips64-ld
NOVL = novl
YAZ0 = ../../toolchain/yaz0/yaz0_encode

CFLAGS = -fno-toplevel-reorder -G 0 -Os --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = -T $(Z64OVLDIR)/z64ovl.ld --emit-relocs
NOVLFLAGS = -v -c -A $(ADDRESS) -o $(PROGRAM).zovl

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf
	$(YAZ0) $(PROGRAM).zovl > $(PROGRAM).yaz0

clean:
	rm -fv $(PROGRAM).elf $(OVLOUT) $(PARTS)
