SUBDIRS = ACEShortcut/ TriforcePiece/ TriforceChest/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
