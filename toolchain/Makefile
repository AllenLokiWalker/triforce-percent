ifeq ("$(wildcard ZAP2/Makefile)","")
    $(error You did not properly set up the Git submodules (ZAP2 makefile not found))
endif

SUBDIRS = \
ZAP2/ \
yaz0/

.PHONY: default clean $(SUBDIRS)

default: $(SUBDIRS)
	
clean: yaz0/

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
