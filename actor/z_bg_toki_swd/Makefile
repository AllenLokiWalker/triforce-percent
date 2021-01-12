ifeq ($(PYTHON3),"")
	$(error Python3 command not defined or internal error)
endif

ACTORDIR=../../build-romhack/actor/108
ORIGMD5=3503c9424b64bb7d087b6e291cec85d1

.PHONY: default clean

default: actor.pat actor.zovl
	echo "${ORIGMD5} ${ACTORDIR}/actor.zovl.orig" | md5sum -c
	cp actor.zovl ${ACTORDIR}/
	touch $(ACTORDIR)/../../update.txt

${ACTORDIR}/actor.zovl.orig:
	cp ${ACTORDIR}/actor.zovl ${ACTORDIR}/actor.zovl.orig
	
actor.zovl: ${ACTORDIR}/actor.zovl.orig linkagepatch.txt
	cp ${ACTORDIR}/actor.zovl.orig actor.zovl
	$(PYTHON3) ../../toolchain/patchinstr.py actor.zovl linkagepatch.txt

actor.pat: actor.zovl ${ACTORDIR}/actor.zovl.orig
	${PYTHON3} ../../toolchain/create_patch.py ${ACTORDIR}/actor.zovl.orig actor.zovl actor.pat

clean:
	rm -f *.zovl *.pat
