.PHONY: default clean

BUILDDIR = ../../build-romhack
PATCHDIR = $(BUILDDIR)/patch
BUILDRTL = $(BUILDDIR)/oot_build.rtl

CC = mips64-gcc
LD = mips64-ld
OC = mips64-objcopy

CFLAGS = -G 0 -Os -fno-reorder-blocks -std=gnu99 -mtune=vr4300 -march=vr4300 -mabi=32 -c -mips3 -mno-explicit-relocs -mno-memcpy -mno-check-zero-division
#-Wall -Wno-main -mno-gpopt -fomit-frame-pointer -G 0 -Os --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary

default: $(BUILDDIR)/tf-romhack.z64
	
$(BUILDDIR)/tf-romhack.z64: $(BUILDDIR)/update.txt rhstatics_patch.bin call_rhstatics.bin ../../toolchain/zzrtl/oot_build.rtl
	mkdir -p $(PATCHDIR)
	cp rhstatics_patch.bin call_rhstatics.bin $(PATCHDIR)
	cp ../../statics/statics.bin $(PATCHDIR)/rhstatics.bin
	cp ../../toolchain/zzrtl/oot_build.rtl $(BUILDRTL)
	sed -i 's/build.z64/tf-romhack.z64/g' $(BUILDRTL)
	$(ZZRTL) $(BUILDRTL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	mips64-as -Os -o $@ $<

%.elf: %.o rhstatics.ld ../../statics/statics.out.ld
	$(LD) $(LDFLAGS) -T rhstatics.ld -o $*.elf $*.o

%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

clean:
	rm -rf *.o *.elf *.bin $(BUILDDIR)/tf-romhack.z64 $(BUILDDIR)/*.bin
