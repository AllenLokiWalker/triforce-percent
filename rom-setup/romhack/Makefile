.PHONY: default clean

BUILDDIR = ../../build-romhack
BUILDRTL = $(BUILDDIR)/oot_build.rtl

CC = mips64-gcc
LD = mips64-ld
OC = mips64-objcopy

CFLAGS = -G 0 -Os -fno-reorder-blocks -std=gnu99 -mtune=vr4300 -march=vr4300 -mabi=32 -c -mips3 -mno-explicit-relocs -mno-memcpy -mno-check-zero-division
#-Wall -Wno-main -mno-gpopt -fomit-frame-pointer -G 0 -Os --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary

default: $(BUILDDIR)/tf-romhack.z64
	
$(BUILDDIR)/tf-romhack.z64: rhstatics_patch.bin ../../toolchain/zzrtl/oot_build.rtl
	cp rhstatics_patch.bin ../../build-romhack/
	cp ../../loader/statics/statics.bin $(BUILDDIR)/rhstatics.bin
	cp ../../toolchain/zzrtl/oot_build.rtl $(BUILDRTL)
	sed -i 's/build.z64/tf-romhack.z64/g' $(BUILDRTL)
	$(ZZRTL) $(BUILDRTL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.elf: %.o %.ld
	$(LD) $(LDFLAGS) -T $*.ld -Map $*.map -o $*.elf $*.o

%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

clean:
	rm -rf *.o *.elf *.bin $(BUILDDIR)/tf-romhack.z64 $(BUILDDIR)/*.bin
