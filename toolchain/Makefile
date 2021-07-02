SUBDIRS = \
ZAP2/ \
yaz0/

.PHONY: default clean $(SUBDIRS)

default: $(SUBDIRS)
	
clean: yaz0/

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
