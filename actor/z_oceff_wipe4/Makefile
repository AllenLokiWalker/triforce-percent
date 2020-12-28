ifeq ($(PYTHON3),"")
	$(error Python3 command not defined or internal error)
endif

ACTORNUM=459
ACTORDIR=../../build-romhack/actor/${ACTORNUM}
ACTORDIR2=../../build-shortcut/actor/${ACTORNUM}
FUNCNAME=OceffWipe4_Update
FUNCOFFSET=128
ORIGMD5=53695eecd6dfa69fb7face182c04192c

.PHONY: default clean

default: actor.pat actor.zovl
	echo "${ORIGMD5} ${ACTORDIR}/actor.zovl.orig" | md5sum -c
	cp actor.zovl ${ACTORDIR}
	cp actor.zovl ${ACTORDIR2}

%.o: %.s
	mips64-as -Os -o $@ $<

%.bin: %.o
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
