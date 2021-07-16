include ../toolchain/make/main.mk

MAKESUBDIRS = spot07_scene
OUTFILES = \
	TriforceRoom/TriforceRoom_scene.zscene \
	TriforceRoom/TriforceRoom_room_0.zmap \
	UnicornFountain/UnicornFountain_scene.zscene \
	UnicornFountain/UnicornFountain_room_0.zmap \
	UnicornFountain/UnicornFountain_scene.out.ld
ROOMROMGOAWAY = \
	-D_TriforceRoom_room_0SegmentRomStart=0xDEADBEEF \
	-D_TriforceRoom_room_0SegmentRomEnd=0xDEADBEEF \
	-D_UnicornFountain_room_0SegmentRomStart=0xDEADBEEF \
	-D_UnicornFountain_room_0SegmentRomEnd=0xDEADBEEF
TRIFORCEROOMDIR = ../build-romhack/scene/39
UNICORNFOUNTAINDIR = ../build-romhack/scene/38

CCFLAGS += $(ROOMROMGOAWAY) -Wno-incompatible-pointer-types -Wno-missing-braces

.PHONY: default clean $(MAKESUBDIRS)

default: $(OUTFILES)
	cp TriforceRoom/TriforceRoom_scene.zscene $(TRIFORCEROOMDIR)/scene.zscene
	cp TriforceRoom/TriforceRoom_room_0.zmap $(TRIFORCEROOMDIR)/room_0.zmap
	cp TriforceRoom/conf.txt $(TRIFORCEROOMDIR)/conf.txt
	cp UnicornFountain/UnicornFountain_scene.zscene $(UNICORNFOUNTAINDIR)/scene.zscene
	cp UnicornFountain/UnicornFountain_room_0.zmap $(UNICORNFOUNTAINDIR)/room_0.zmap
	cp UnicornFountain/title.png $(UNICORNFOUNTAINDIR)/title.png
	cp UnicornFountain/conf.txt $(UNICORNFOUNTAINDIR)/conf.txt

default clean: $(MAKESUBDIRS)

$(MAKESUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

%_room_0.elf: %_room_0.o room.ld
	$(LD) $(LDFLAGS) -T room.ld -o $@ $<

%_scene.elf %_scene.map: %_scene.o scene.ld
	$(LD) $(LDFLAGS) -T scene.ld -Map $*_scene.map -o $@ $<

clean: cleansubdirs

include ../toolchain/make/c.mk
