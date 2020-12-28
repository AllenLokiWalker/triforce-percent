SUBDIRS = ACEShortcut/ TriforcePiece/ TriforceChest/ TriforceLight/ z_oceff_wipe4/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
