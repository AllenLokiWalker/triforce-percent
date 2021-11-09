SUBDIRS = \
ZAP2/ \
yaz0/

.PHONY: default clean $(SUBDIRS) z64audio/ novl/novl

default: $(SUBDIRS) z64audio/ novl/novl
	
clean: yaz0/
	rm -f novl/novl

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

z64audio/:
	$(MAKE) -C $@ lin
	
novl/novl:
	gcc -o $@ -s -Os -DNOVL_DEBUG=1 -flto novl/src/*.c `pkg-config --cflags --libs libelf glib-2.0`
