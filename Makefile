ifeq ("$(wildcard local.mk)","")
    $(error You have not read README.md, please do so)
endif

include local.mk
export

ifeq ("$(and $(wildcard build-shortcut/oot_1.0U_uncomp.z64), $(wildcard build-romhack/oot_1.0U_uncomp.z64))","")
    $(error Original ROMs not found, please read README.md)
endif

ifeq ("$(and $(wildcard build-shortcut/oot_build.rtl), $(wildcard build-shortcut/oot_dump.rtl))","")
    $(shell cp toolchain/zzrtl/oot_build.rtl toolchain/zzrtl/oot_dump.rtl build-shortcut/)
    $(shell sed -i 's/build.z64/tf-shortcut.z64/g' build-shortcut/oot_build.rtl)
endif
ifeq ("$(and $(wildcard build-romhack/oot_build.rtl), $(wildcard build-romhack/oot_dump.rtl))","")
    $(shell cp toolchain/zzrtl/oot_build.rtl toolchain/zzrtl/oot_dump.rtl build-romhack/)
    $(shell sed -i 's/build.z64/tf-romhack.z64/g' build-romhack/oot_build.rtl)
endif

CONTENTS = actor/ music/ scene/ textures/
SUBDIRS = toolchain/ $(CONTENTS) loader/ bootstrap/
DUMPS = build-shortcut/project.zzrpl build-romhack/project.zzrpl
BUILDS = build-shortcut/build.z64 build-romhack/build.z64

.PHONY: default clean $(SUBDIRS)

default: $(SUBDIRS) $(DUMPS) $(BUILDS)

clean: $(SUBDIRS)

actor/: $(DUMPS)

scene/: $(DUMPS)

loader/: actor/ music/ scene/

bootstrap/: loader/

%project.zzrpl: %oot_1.0U_uncomp.z64 %oot_build.rtl %oot_dump.rtl
	$(ZZRTL) $*oot_dump.rtl

%build.z64: $(SUBDIRS)
	$(ZZRTL) $*oot_build.rtl

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
