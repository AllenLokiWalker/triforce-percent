include ../toolchain/make/main.mk

TEXTURES = \
	butterfly_bottle.rgba32.inc \
	butterfly_bottle.rgba32.bin \
	butterfly_bottle.rgba32.pat \
	sages_charm_24.rgba32.bin \
	sages_charm_24.rgba32.pat \
	triforce.rgba32.pat \
	item_butterfly.ia4.bin \
	item_magic_powder.ia4.bin \
	item_sages_charm.ia4.bin \
	ddn.ia8.inc \
	dup.ia8.inc \
	flat.ia8.inc \
	sharp.ia8.inc

STATICDATADIR := ../build-romhack/staticdata

.PHONY: default clean

default: $(TEXTURES)
	mkdir -p                              $(STATICDATADIR)/1
	cp butterfly_bottle.rgba32.bin        $(STATICDATADIR)/1/staticdata.bin
	echo "dtype 4\ndata1 0x1E\ndata2 0" > $(STATICDATADIR)/1/conf.txt
	mkdir -p                              $(STATICDATADIR)/2
	cp sages_charm_24.rgba32.bin          $(STATICDATADIR)/2/staticdata.bin
	echo "dtype 4\ndata1 0x6F\ndata2 0" > $(STATICDATADIR)/2/conf.txt
	mkdir -p                              $(STATICDATADIR)/3
	cp item_butterfly.ia4.bin             $(STATICDATADIR)/3/staticdata.bin
	echo "dtype 5\ndata1 0x1E\ndata2 0" > $(STATICDATADIR)/3/conf.txt
	mkdir -p                              $(STATICDATADIR)/4
	cp item_magic_powder.ia4.bin          $(STATICDATADIR)/4/staticdata.bin
	echo "dtype 5\ndata1 0x31\ndata2 0" > $(STATICDATADIR)/4/conf.txt
	mkdir -p                              $(STATICDATADIR)/5
	cp item_sages_charm.ia4.bin           $(STATICDATADIR)/5/staticdata.bin
	echo "dtype 5\ndata1 0x6F\ndata2 0" > $(STATICDATADIR)/5/conf.txt

clean: texclean

include ../toolchain/make/textures.mk
include ../toolchain/make/c.mk
