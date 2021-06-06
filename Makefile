ifeq ("$(wildcard local.mk)","")
    $(error You have not read README.md, please do so)
endif

include local.mk
export

ifeq ("$(and $(wildcard build-shortcut/oot_1.0U_comp.z64), $(wildcard build-romhack/oot_1.0U_uncomp.z64))","")
    $(error Original ROMs not found, please read README.md)
endif

CONTENTS = actor/ anim/ music/ scene/ textures/
SUBDIRS = toolchain/ $(CONTENTS) loader/ statics/ bootstrap/ rom-setup/
DUMP = build-romhack/project.zzrpl

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

actor/: toolchain/ $(DUMP) statics/ scene/

scene/: $(DUMP)

statics/: anim/ loader/ textures/

bootstrap/: loader/

rom-setup/: statics/ $(CONTENTS)

%project.zzrpl: %oot_1.0U_uncomp.z64 toolchain/zzrtl/oot_dump.rtl
	cp toolchain/zzrtl/oot_dump.rtl $*oot_dump.rtl
	$(ZZRTL) $*oot_dump.rtl
	touch $*update.txt

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
