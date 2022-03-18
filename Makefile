include toolchain/make/main.mk

CONTENTS = actor/ anim/ model/ music/ scene/ textures/ voice/
SUBDIRS = toolchain/ $(CONTENTS) loader/ statics/ bootstrap/ rom-setup/
DUMP = build-romhack/project.zzrpl

.PHONY: default clean $(SUBDIRS)

default: $(SUBDIRS)
	@echo "=============\nDone building\n============="

clean: $(SUBDIRS)
	@echo "=============\nDone cleaning\n============="

actor/: toolchain/ $(DUMP) statics/ scene/

scene/: $(DUMP)

statics/: anim/ loader/ model/ scene/ textures/ voice/

bootstrap/: loader/

rom-setup/: statics/ $(CONTENTS)

%project.zzrpl: %oot_1.0U_uncomp.z64 toolchain/zzrtl/oot_dump.rtl
	cp toolchain/zzrtl/oot_dump.rtl $*oot_dump.rtl
	$(ZZRTL) $*oot_dump.rtl
	touch $*update.txt
	rm $*scene/0/title.png
	rm $*scene/1/title.png
	rm $*scene/2/title.png
	rm $*scene/3/title.png
	rm $*scene/4/title.png
	rm $*scene/5/title.png
	rm $*scene/6/title.png
	rm $*scene/7/title.png
	rm $*scene/8/title.png
	rm $*scene/9/title.png
	rm $*scene/11/title.png
	rm $*scene/13/title.png
	rm $*scene/16/title.png
	rm $*scene/34/title.png
	rm $*scene/45/title.png
	rm $*scene/46/title.png
	rm $*scene/47/title.png
	rm $*scene/48/title.png
	rm $*scene/49/title.png
	rm $*scene/50/title.png
	rm $*scene/51/title.png
	rm $*scene/54/title.png
	rm $*scene/56/title.png
	rm $*scene/58/title.png
	rm $*scene/59/title.png
	rm $*scene/60/title.png
	rm $*scene/61/title.png
	rm $*scene/65/title.png
	rm $*scene/66/title.png
	rm $*scene/68/title.png
	rm $*scene/69/title.png
	rm $*scene/70/title.png
	rm $*scene/72/title.png
	rm $*scene/73/title.png
	rm $*scene/74/title.png
	rm $*scene/75/title.png
	rm $*scene/78/title.png
	rm $*scene/80/title.png

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
