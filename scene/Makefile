include ../toolchain/make/main.mk

MAKESUBDIRS = \
	gerudoway \
	shop1 \
	spot07_scene \
	spot10 \
	tokinoma

OUTFILES = \
	UnicornFountain/UnicornFountain_scene.zscene \
	UnicornFountain/UnicornFountain_room_0.zmap \
	UnicornFountain/UnicornFountain_scene.out.ld \
	TestVAlpha/TestVAlpha_scene.zscene \
	TestVAlpha/TestVAlpha_room_0.zmap \
	ChamberOfSages/ChamberOfSages_scene.zscene \
	ChamberOfSages/ChamberOfSages_room_0.zmap \
	ChamberOfSages/ChamberOfSages_scene.out.ld \
	TriforceRoom/TriforceRoom_scene.zscene \
	TriforceRoom/TriforceRoom_room_0.zmap \
	TriforceRoom/TriforceRoom_scene.out.ld \
	EndingDemo/EndingDemo_scene.zscene \
	EndingDemo/EndingDemo_room_0.zmap
ROOMROMGOAWAY = \
	-D_UnicornFountain_room_0SegmentRomStart=0xDEADBEEF \
	-D_UnicornFountain_room_0SegmentRomEnd=0xDEADBEEF \
	-D_TestVAlpha_room_0SegmentRomStart=0xDEADBEEF \
	-D_TestVAlpha_room_0SegmentRomEnd=0xDEADBEEF \
	-D_ChamberOfSages_room_0SegmentRomStart=0xDEADBEEF \
	-D_ChamberOfSages_room_0SegmentRomEnd=0xDEADBEEF \
	-D_TriforceRoom_room_0SegmentRomStart=0xDEADBEEF \
	-D_TriforceRoom_room_0SegmentRomEnd=0xDEADBEEF \
	-D_EndingDemo_room_0SegmentRomStart=0xDEADBEEF \
	-D_EndingDemo_room_0SegmentRomEnd=0xDEADBEEF
TITLEFILES = \
	UnicornFountain/title.ia8 \
	ChamberOfSages/title.ia8
UNICORNFOUNTAINDIR = ../build-romhack/scene/38
TESTVALPHADIR = ../build-romhack/scene/41
CHAMBEROFSAGESDIR = ../build-romhack/scene/41
TRIFORCEROOMDIR = ../build-romhack/scene/39
ENDINGDEMODIR = ../build-romhack/scene/41

CCFLAGS += $(ROOMROMGOAWAY) -Wno-incompatible-pointer-types -Wno-missing-braces

.PHONY: default clean $(MAKESUBDIRS)

default: $(OUTFILES) $(TITLEFILES)
	cp UnicornFountain/UnicornFountain_scene.zscene $(UNICORNFOUNTAINDIR)/scene.zscene
	cp UnicornFountain/UnicornFountain_room_0.zmap $(UNICORNFOUNTAINDIR)/room_0.zmap
	cp UnicornFountain/title.ia8.png $(UNICORNFOUNTAINDIR)/title.png
	cp UnicornFountain/conf.txt $(UNICORNFOUNTAINDIR)/conf.txt
	#cp TestVAlpha/TestVAlpha_scene.zscene $(TESTVALPHADIR)/scene.zscene
	#cp TestVAlpha/TestVAlpha_room_0.zmap $(TESTVALPHADIR)/room_0.zmap
	#cp ChamberOfSages/ChamberOfSages_scene.zscene $(CHAMBEROFSAGESDIR)/scene.zscene
	#cp ChamberOfSages/ChamberOfSages_room_0.zmap $(CHAMBEROFSAGESDIR)/room_0.zmap
	#cp ChamberOfSages/title.ia8.png $(CHAMBEROFSAGESDIR)/title.png
	#cp ChamberOfSages/conf.txt $(CHAMBEROFSAGESDIR)/conf.txt
	cp TriforceRoom/TriforceRoom_scene.zscene $(TRIFORCEROOMDIR)/scene.zscene
	cp TriforceRoom/TriforceRoom_room_0.zmap $(TRIFORCEROOMDIR)/room_0.zmap
	cp TriforceRoom/conf.txt $(TRIFORCEROOMDIR)/conf.txt
	cp EndingDemo/EndingDemo_scene.zscene $(ENDINGDEMODIR)/scene.zscene
	cp EndingDemo/EndingDemo_room_0.zmap $(ENDINGDEMODIR)/room_0.zmap

default clean: $(MAKESUBDIRS)

$(MAKESUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

%_room_0.elf: %_room_0.o room.ld
	$(LD) $(LDFLAGS) -T room.ld -o $@ $<

%_scene.elf %_scene.map: %_scene.o scene.ld
	$(LD) $(LDFLAGS) -T scene.ld -Map $*_scene.map -o $*_scene.elf $<

clean: cleansubdirs
	rm -f */title.ia8

include ../toolchain/make/textures.mk
include ../toolchain/make/c.mk
