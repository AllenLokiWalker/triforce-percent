include make/main.mk

SUBDIRS = \
ZAPD/ \
yaz0/

.PHONY: default clean $(SUBDIRS) z64audio/ z64convert/

default: $(SUBDIRS) z64audio/ z64convert/ $(NOVL)
	
clean: yaz0/
	rm -f $(NOVL)
	$(MAKE) -C z64convert/ clean

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

z64audio/:
	$(MAKE) -C $@ lin
	
z64convert/:
	$(MAKE) -C $@ lincli
	
$(NOVL): novl/src/novl.c novl/src/novl-conv.c novl/src/novl-reloc.c
	gcc -o $@ -s -Os -DNOVL_DEBUG=1 -flto novl/src/*.c `pkg-config --cflags --libs libelf glib-2.0`
