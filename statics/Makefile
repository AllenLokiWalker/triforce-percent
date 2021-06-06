.PHONY: default clean

CC = mips64-gcc
LD = mips64-ld
OC = mips64-objcopy

CFLAGS = -Wall -Wno-main -Wno-missing-braces -mno-gpopt -fomit-frame-pointer -G 0 -O2 --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary

default: statics.bin statics.out.ld

#Dependencies

statics.o: statics.h ../loader/fast_loader/fast_loader.h

interface.o: interface.h

message.o: message.h ../text/messages.c

../text/build_messages_file.o: ../text/message_data_fmt.h ../text/messages.c

anime.o: anime.h ../anim/anim.c

ocarina.o: ocarina.h ocarina_patches.inc

LINK_OBJS = \
	statics.o \
	interface.o \
	message.o \
	../text/build_messages_file.o \
	anime.o \
	ocarina.o

LD_SCRIPTS = \
	statics.ld \
	z64structs.ld \
	z64funcs.ld \
	interface.ld \
	message.ld \
	anime.ld \
	ocarina.ld \
	../loader/fast_loader/fast_loader.out.ld \
	../loader/dma_patcher/dma_patcher.out.ld \
	../anim/anim.out.ld

%.o: %.c z64funcs.h z64structs.h
	$(CC) $(CFLAGS) -c $< -o $@

statics.elf statics.map: $(LINK_OBJS) $(LD_SCRIPTS)
	$(LD) $(LDFLAGS) -T statics.ld -Map statics.map -o statics.elf $(LINK_OBJS)

%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

%.out.ld: %.map
	$(PYTHON3) ../toolchain/ldout.py $< $@

ACTORDIR=../build-romhack/system/overlay/ovl_player_actor
CLEANLINKZOVL=${ACTORDIR}/ovl_player_actor.zovl.orig

${CLEANLINKZOVL}:
	cp ${ACTORDIR}/ovl_player_actor.zovl ${CLEANLINKZOVL}

clean:
	rm -rf *.i *.s *.o ../text/*.o *.map *.elf statics.bin
