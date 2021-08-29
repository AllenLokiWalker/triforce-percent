include ../../toolchain/make/main.mk

SCENEDIR=../../build-romhack/scene/91
ROOM7ORIGMD5=68dda44b12e80be04f79b0f243a495ef

.PHONY: default clean

default: room_7.zmap
	echo "${ROOM7ORIGMD5} ${SCENEDIR}/room_7.zmap.orig" | md5sum -c
	cp room_7.zmap ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

${SCENEDIR}/room_7.zmap.orig:
	cp ${SCENEDIR}/room_7.zmap ${SCENEDIR}/room_7.zmap.orig

room_7.zmap: ${SCENEDIR}/room_7.zmap.orig spot10_room_7.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${SCENEDIR}/room_7.zmap.orig spot10_room_7.pat room_7.zmap

clean:
	rm -f *.zscene *.zmap
