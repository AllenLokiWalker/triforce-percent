ifeq ("$(wildcard ZAP2/Makefile)","")
    $(error You did not properly set up the Git submodules (ZAP2 makefile not found))
endif

SUBDIRS = \
zap2/ \
yaz0/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
