SUBDIRS = \
ZAP2/ \
yaz0/

.PHONY: default clean $(SUBDIRS) z64audio/ $(ZZCONVERT) $(NOVL)

default: $(SUBDIRS) z64audio/
	
clean: yaz0/
	rm -f novl/novl
	rm -rf z64convert/bin

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

z64audio/:
	$(MAKE) -C $@ lin
	
$(ZZCONVERT): z64convert/release-linux-cli.sh z64convert/src/z64convert.c z64convert/wowlib/wow.h
	cd z64convert; ./release-linux-cli.sh
	
$(NOVL): novl/src/novl.c novl/src/novl-conv.c novl/src/novl-reloc.c
	gcc -o $@ -s -Os -DNOVL_DEBUG=1 -flto novl/src/*.c `pkg-config --cflags --libs libelf glib-2.0`
