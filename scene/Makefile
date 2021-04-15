MAKESUBDIRS = spot07_scene
OUTFILES = \
	TriforceRoom/TriforceRoom_scene.zscene \
	TriforceRoom/TriforceRoom_room_0.zmap
ROOMROMGOAWAY = \
	-D_TriforceRoom_room_0SegmentRomStart=0xDEADBEEF \
	-D_TriforceRoom_room_0SegmentRomEnd=0xDEADBEEF
TRIFORCEROOMDIR = ../build-romhack/scene/39

.PHONY: default clean $(MAKESUBDIRS)

default clean: $(MAKESUBDIRS)

default: $(OUTFILES)
	cp TriforceRoom/TriforceRoom_scene.zscene $(TRIFORCEROOMDIR)/scene.zscene
	cp TriforceRoom/TriforceRoom_room_0.zmap $(TRIFORCEROOMDIR)/room_0.zmap
	cp TriforceRoom/conf.txt $(TRIFORCEROOMDIR)/conf.txt

$(MAKESUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
	
CC = mips64-gcc
LD = mips64-ld
OC = mips64-objcopy

CFLAGS = -I $(DECOMPINCLUDEDIR) -fno-toplevel-reorder -Wall -Wno-main -Wno-missing-braces -mno-gpopt -fomit-frame-pointer -G 0 --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary

%_room_0.o: %_room_0.c %_room_0.h Makefile 
	$(CC) $(CFLAGS) -c $< -o $@
	
%_scene.o: %_scene.c %_scene.h Makefile
	$(CC) $(CFLAGS) $(ROOMROMGOAWAY) -c $< -o $@

%_room_0.elf: %_room_0.o room.ld
	$(LD) $(LDFLAGS) -T room.ld -o $@ $<

%_scene.elf: %_scene.o scene.ld
	$(LD) $(LDFLAGS) -T scene.ld -o $@ $<

%_room_0.zmap: %_room_0.elf
	$(OC) $(OCFLAGS) $< $@

%_scene.zscene: %_scene.elf
	$(OC) $(OCFLAGS) $< $@

clean:
	rm -f */*.o */*.elf
