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
endif
ifeq ("$(and $(wildcard build-romhack/oot_build.rtl), $(wildcard build-romhack/oot_dump.rtl))","")
    $(shell cp toolchain/zzrtl/oot_build.rtl toolchain/zzrtl/oot_dump.rtl build-romhack/)
endif

SUBDIRS = actor/ music/ scene/

.PHONY: default clean dumps builds $(SUBDIRS) loader bootstrap

default: dumps builds $(SUBDIRS) loader bootstrap

dumps: build-shortcut/project.zzrpl build-romhack/project.zzrpl

builds: build-shortcut/build.z64 build-romhack/build.z64

%project.zzrpl: %oot_1.0U_uncomp.z64 %oot_build.rtl %oot_dump.rtl
	$(ZZRTL) $*oot_dump.rtl

%build.z64: $(SUBDIRS)
	$(ZZRTL) $*oot_build.rtl

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

loader: $(SUBDIRS)
	$(MAKE) -C loader/ $(MAKECMDGOALS)
    
bootstrap: loader
	$(MAKE) -C bootstrap/ $(MAKECMDGOALS)
