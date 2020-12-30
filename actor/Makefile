SUBDIRS = ACEShortcut/ TriforcePiece/ TriforceChest/ TriforceLight/ z_oceff_wipe/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
