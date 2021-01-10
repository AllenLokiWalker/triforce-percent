SUBDIRS = \
ACEShortcut/ \
TriforcePiece/ \
TriforceChest/ \
TriforceLight/ \
z_bg_toki_swd/ \
z_en_xc/ \
z_oceff_wipe/ \
z_player/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
