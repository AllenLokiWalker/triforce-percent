SUBDIRS = ACEShortcut/ TriforcePiece/ TriforceLight/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
