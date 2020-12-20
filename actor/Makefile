SUBDIRS = ACEShortcut/ TriforcePiece/ TriforceChest/ TriforceLight/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
