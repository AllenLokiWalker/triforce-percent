ifeq ($(PYTHON3),"")
	$(error Python3 command not defined or internal error)
endif

ACTORDIR=../../build-romhack/system/overlay/ovl_player_actor
ORIGMD5=58b2c8810636b93f805d55182144236a

.PHONY: default clean

default: ovl_player_actor.pat ovl_player_actor.zovl
	echo "${ORIGMD5} ${ACTORDIR}/ovl_player_actor.zovl.orig" | md5sum -c
	cp ovl_player_actor.zovl ${ACTORDIR}/
	touch ../../build-romhack/update.txt

${ACTORDIR}/ovl_player_actor.zovl.orig:
	cp ${ACTORDIR}/ovl_player_actor.zovl ${ACTORDIR}/ovl_player_actor.zovl.orig
	
ovl_player_actor.zovl: ${ACTORDIR}/ovl_player_actor.zovl.orig playerpatches.txt
	cp ${ACTORDIR}/ovl_player_actor.zovl.orig ovl_player_actor.zovl
	$(PYTHON3) ../../toolchain/patchinstr.py ovl_player_actor.zovl playerpatches.txt

ovl_player_actor.pat: ovl_player_actor.zovl ${ACTORDIR}/ovl_player_actor.zovl.orig
	${PYTHON3} ../../toolchain/create_patch.py ${ACTORDIR}/ovl_player_actor.zovl.orig ovl_player_actor.zovl ovl_player_actor.pat

clean:
	rm -f *.zovl *.pat
