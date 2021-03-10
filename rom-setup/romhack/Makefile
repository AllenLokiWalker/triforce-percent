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
	
BINFILES = ../../anim/anim.bin ../../statics/statics.bin boot_load_statics.bin padmgr_call_statics.bin
	
$(BUILDDIR)/tf-romhack.z64: $(BUILDDIR)/update.txt $(BINFILES) ../../toolchain/zzrtl/oot_build.rtl
	mkdir -p $(PATCHDIR)
	cp $(BINFILES) $(PATCHDIR)
	cp ../../toolchain/zzrtl/oot_build.rtl $(BUILDRTL)
	sed -i 's/build.z64/tf-romhack.z64/g' $(BUILDRTL)
	$(ZZRTL) $(BUILDRTL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	mips64-as -Os -o $@ $<

%.elf: %.o boot_load_statics.ld ../../statics/statics.out.ld
	$(LD) $(LDFLAGS) -T boot_load_statics.ld -o $*.elf $*.o

%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

clean:
	rm -rf *.o *.elf *.bin $(BUILDDIR)/tf-romhack.z64 $(BUILDDIR)/*.bin
