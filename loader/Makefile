.PHONY: default clean fast_loader dma_patcher

CC = mips64-gcc
LD = mips64-ld
OC = mips64-objcopy

CFLAGS = -Wall -Wno-main -mno-gpopt -fomit-frame-pointer -G 0 -Os --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary

default: fast_loader/fast_loader.bin fast_loader/fast_loader.elf debugger/debugger.bin dma_patcher/dma_patcher.bin dma_patcher/dma_patcher.out.ld

#Dependencies

debugger/debugger.o: fast_loader/fast_loader.h

debugger/debugger.elf: fast_loader/fast_loader.out.ld

dma_patcher/dma_patcher.o: debugger/debugger.h

dma_patcher/dma_patcher.elf: debugger/debugger.out.ld

# fast_loader dma_patcher:
# 	$(CC) $(CFLAGS) -c $@/$@.c -o $@/$@.o
# 	$(LD) $(LDFLAGS) -T $@/$@.ld -Map $@/$@.map -o $@/$@.elf $@/$@.o
# 	$(OC) $(OCFLAGS) $@/$@.elf $@.bin
# 	$(PYTHON3) ../toolchain/ldout.py $@/$@.map $@/$@.out.ld

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.elf %.map: %.o %.ld
	$(LD) $(LDFLAGS) -T $*.ld -Map $*.map -o $*.elf $<

%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

%.out.ld: %.map
	$(PYTHON3) ../toolchain/ldout.py $< $@

clean:
	rm -rf */*.o */*.map */*.elf fast_loader/fast_loader.bin debugger/debugger.bin dma_patcher/dma_patcher.bin
