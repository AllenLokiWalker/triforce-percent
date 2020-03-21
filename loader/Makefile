.PHONY: default clean fast_loader dma_patcher

CC = mips64-gcc
LD = mips64-ld
OC = mips64-objcopy

CFLAGS = -Wall -Wno-main -mno-gpopt -fomit-frame-pointer -G 0 -Os --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary

default: fast_loader dma_patcher

fast_loader dma_patcher:
	$(CC) $(CFLAGS) -c $@/$@.c -o $@/$@.o
	$(LD) $(LDFLAGS) -T $@/$@.ld -Map $@/$@.map -o $@/$@.elf $@/$@.o
	$(OC) $(OCFLAGS) $@/$@.elf $@.bin
