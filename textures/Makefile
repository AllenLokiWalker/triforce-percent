include ../toolchain/make/main.mk

TEXTURES = \
	butterfly_bottle.rgba32.inc \
	butterfly_bottle.rgba32.pat \
	sages_charm.rgba32.pat \
	triforce.rgba32.pat \
	item_butterfly.ia4.pat \
	item_magic_powder.ia4.pat \
	item_sages_charm.ia4.pat \
	ddn.ia8.inc \
	dup.ia8.inc \
	flat.ia8.inc \
	sharp.ia8.inc

.PHONY: default clean

default: $(TEXTURES)

clean: texclean

include ../toolchain/make/textures.mk
include ../toolchain/make/c.mk
