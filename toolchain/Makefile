SUBDIRS = \
ZAP2/ \
yaz0/

.PHONY: default clean $(SUBDIRS) z64audio/ z64convert/ novl/novl

default: $(SUBDIRS) z64audio/ z64convert/ novl/novl
	
clean: yaz0/
	rm -f novl/novl
	rm -rf z64convert/bin

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

z64audio/:
	$(MAKE) -C $@ lin
	
z64convert/:
	cd z64convert; ./release-linux-cli.sh
	
novl/novl:
	gcc -o $@ -s -Os -DNOVL_DEBUG=1 -flto novl/src/*.c `pkg-config --cflags --libs libelf glib-2.0`
