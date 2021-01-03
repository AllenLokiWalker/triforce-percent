ifeq ($(PYTHON3),"")
	$(error Python3 command not defined or internal error)
endif

ACTORNUM=394
ACTORDIR=../../build-romhack/actor/${ACTORNUM}
FUNCNAME=OceffWipe_Update
FUNCOFFSET=168
ORIGMD5=ec388e81c32e26d8ee35fd8771c8c84e

.PHONY: default clean

default: actor.pat actor.zovl
	echo "${ORIGMD5} ${ACTORDIR}/actor.zovl.orig" | md5sum -c
	cp actor.zovl ${ACTORDIR}

%.o: %.s
	mips64-as -Os -o $@ $<

%.elf: %.o z_oceff_wipe.ld ../../loader/statics/statics.out.ld
	mips64-ld -T z_oceff_wipe.ld -o $@ $<

%.bin: %.elf
	mips64-objcopy -O binary -j .text -j .data $< $@

${ACTORDIR}/actor.zovl.orig:
	cp ${ACTORDIR}/actor.zovl ${ACTORDIR}/actor.zovl.orig
	
actor.zovl: ${ACTORDIR}/actor.zovl.orig ${FUNCNAME}.bin
	cp ${ACTORDIR}/actor.zovl.orig actor.zovl
	dd conv=notrunc if=${FUNCNAME}.bin of=actor.zovl bs=1 seek=${FUNCOFFSET}

actor.pat: actor.zovl ${ACTORDIR}/actor.zovl.orig
	${PYTHON3} ../../toolchain/create_patch.py ${ACTORDIR}/actor.zovl.orig actor.zovl actor.pat

clean:
	rm -f *.o *.bin *.zovl *.pat
