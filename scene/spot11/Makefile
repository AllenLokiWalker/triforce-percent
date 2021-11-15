include ../../toolchain/make/main.mk

SCENEDIR=../../build-romhack/scene/92
ROOMORIGMD5=2590d6dc16ef0862d754e588673d2247
SCENEORIGMD5=79a6d3beb1b9f71e6bd71c879e839a7e

.PHONY: default clean clean2

.PRECIOUS: ${SCENEDIR}/room_0.zmap.orig ${SCENEDIR}/scene.zscene.orig

default: room_0.zmap scene.zscene room_0.pat scene.pat
	echo "${ROOMORIGMD5} ${SCENEDIR}/room_0.zmap.orig" | md5sum -c
	echo "${SCENEORIGMD5} ${SCENEDIR}/scene.zscene.orig" | md5sum -c
	cp room_0.zmap scene.zscene ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

${SCENEDIR}/%.orig:
	cp ${SCENEDIR}/$* ${SCENEDIR}/$*.orig

room_%.zmap: ${SCENEDIR}/room_%.zmap.orig room%_patch.txt
	cp ${SCENEDIR}/room_$*.zmap.orig $@
	${PYTHON3} ../../toolchain/patchinstr.py $@ room$*_patch.txt

scene.zscene: ${SCENEDIR}/scene.zscene.orig scene_patch.txt
	cp ${SCENEDIR}/scene.zscene.orig $@
	${PYTHON3} ../../toolchain/patchinstr.py $@ scene_patch.txt

room_%.pat: room_%.zmap
	${PYTHON3} ../../toolchain/create_patch.py ${SCENEDIR}/room_%.zmap.orig $< $@

scene.pat: scene.zscene
	${PYTHON3} ../../toolchain/create_patch.py ${SCENEDIR}/scene.zscene.orig $< $@

%.elf: %.o ../room.ld
	$(LD) $(LDFLAGS) -T ../room.ld -o $@ $<

clean: clean2

clean2:
	rm -f *.zscene *.zmap

include ../../toolchain/make/c.mk
