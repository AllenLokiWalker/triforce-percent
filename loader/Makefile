.PHONY: default clean

CC = mips64-gcc
LD = mips64-ld
OC = mips64-objcopy

CFLAGS = -Wall -Wno-main -mno-gpopt -fomit-frame-pointer -G 0 -O2 --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary

default: fast_loader/fast_loader.bin debugger/debugger.bin dma_patcher/dma_patcher.map dma_patcher/dma_patcher.bin statics/statics.bin statics/statics.out.ld

#Dependencies

debugger/debugger.o: fast_loader/fast_loader.h

debugger/debugger.elf: fast_loader/fast_loader.out.ld

dma_patcher/dma_patcher.o: debugger/debugger.h

dma_patcher/dma_patcher.elf: debugger/debugger.out.ld
	
statics/statics.o: fast_loader/fast_loader.h debugger/debugger.h

STATICS_DEPS = \
	statics/statics.h \
	statics/statics.o \
	statics/statics.ld \
	statics/interface.h \
	statics/interface.o \
	statics/interface.ld \
	statics/message.h \
	statics/message.o \
	statics/message.ld \
	../text/message_data_fmt.h \
	../text/messages.c \
	../text/build_messages_file.o \
	fast_loader/fast_loader.out.ld \
	debugger/debugger.out.ld \
	dma_patcher/dma_patcher.out.ld

STATICS_OBJS = \
	statics/statics.o \
	statics/interface.o \
	statics/message.o \
	../text/build_messages_file.o

# fast_loader dma_patcher:
# 	$(CC) $(CFLAGS) -c $@/$@.c -o $@/$@.o
# 	$(LD) $(LDFLAGS) -T $@/$@.ld -Map $@/$@.map -o $@/$@.elf $@/$@.o
# 	$(OC) $(OCFLAGS) $@/$@.elf $@.bin
# 	$(PYTHON3) ../toolchain/ldout.py $@/$@.map $@/$@.out.ld

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.elf %.map: %.o %.ld
	$(LD) $(LDFLAGS) -T $*.ld -Map $*.map -o $*.elf $*.o
	
statics/statics.elf statics/statics.map: $(STATICS_DEPS)
	$(LD) $(LDFLAGS) -T statics/statics.ld -Map statics/statics.map -o statics/statics.elf $(STATICS_OBJS)

%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

%.out.ld: %.map
	$(PYTHON3) ../toolchain/ldout.py $< $@

clean:
	rm -rf */*.o ../text/*.o */*.map */*.elf fast_loader/fast_loader.bin debugger/debugger.bin dma_patcher/dma_patcher.bin statics/statics.bin
