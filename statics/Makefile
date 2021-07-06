include ../toolchain/make/main.mk

.PHONY: default clean

default: statics.bin statics.out.ld

#Dependencies

statics.o: statics.h ../loader/fast_loader/fast_loader.h

interface.o: interface.h

message.o: message.h ../text/messages.c

../text/build_messages_file.o: ../text/message_data_fmt.h ../text/messages.c

anime.o: anime.h ../anim/anim.c

ocarina.o: \
	ocarina.h \
	ocarina_patches.inc \
	../textures/dup.ia8.inc \
	../textures/ddn.ia8.inc \
	../textures/flat.ia8.inc \
	../textures/sharp.ia8.inc

audio.o: audio.h

LINK_OBJS = \
	statics.o \
	interface.o \
	message.o \
	anime.o \
	ocarina.o \
	audio.o \
	../text/build_messages_file.o

LD_SCRIPTS = \
	statics.ld \
	interface.ld \
	message.ld \
	anime.ld \
	ocarina.ld \
	audio.ld \
	../loader/fast_loader/fast_loader.out.ld \
	../loader/dma_patcher/dma_patcher.out.ld \
	../anim/anim.out.ld

statics.elf statics.map: $(LINK_OBJS) $(LD_SCRIPTS) $(OOTMAINLD)
	$(LD) $(LDFLAGS) -T statics.ld -Map statics.map -o statics.elf $(LINK_OBJS)

ACTORDIR=../build-romhack/system/overlay/ovl_player_actor
CLEANLINKZOVL=${ACTORDIR}/ovl_player_actor.zovl.orig

${CLEANLINKZOVL}:
	cp ${ACTORDIR}/ovl_player_actor.zovl ${CLEANLINKZOVL}

clean: cleandir
	rm -rf *.s ../text/*.o

include ../toolchain/make/c.mk
