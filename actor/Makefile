SUBDIRS = \
BetaGreatFairy/ \
CoSSages/ \
CoSStaircases/ \
Nabooru/ \
TriforcePiece/ \
TriforceChest/ \
TriforceLight/ \
z_bg_mjin/ \
z_bg_spot07_taki/ \
z_bg_toki_swd/ \
z_demo_effect/ \
z_en_ge1/ \
z_en_ge2/ \
z_en_wonder_item/ \
z_en_xc/ \
z_oceff_wipe/ \
z_player/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
