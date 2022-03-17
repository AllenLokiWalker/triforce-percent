include ../toolchain/make/main.mk

SOUNDS = \
	vo_link_zerudahime.c \
	vo_link_isshoni.c \
	vo_zelda_link.c \
	vo_zelda_itseems.c \
	vo_zelda_imsohappy.c \
	vo_zelda_iknowtheyre.c \
	vo_zelda_look.c \
	vo_zelda_youasked.c \
	vo_zelda_hereitis.c \
	vo_zelda_thankyou.c

Z64AUDIO = $(PROJECT_DIR)/toolchain/z64audio/z64audio

.PHONY: default clean

default: $(SOUNDS)
	mkdir -p                           $(STATICDATADIR)/17
	cp vo_link_zerudahimeRaw.bin       $(STATICDATADIR)/17/staticdata.bin
	echo "dtype 3\ndata1 0\ndata2 0" > $(STATICDATADIR)/17/conf.txt
	mkdir -p                           $(STATICDATADIR)/18
	cp vo_link_isshoniRaw.bin          $(STATICDATADIR)/18/staticdata.bin
	echo "dtype 3\ndata1 1\ndata2 0" > $(STATICDATADIR)/18/conf.txt
	mkdir -p                           $(STATICDATADIR)/19
	cp vo_zelda_linkRaw.bin            $(STATICDATADIR)/19/staticdata.bin
	echo "dtype 3\ndata1 2\ndata2 0" > $(STATICDATADIR)/19/conf.txt
	mkdir -p                           $(STATICDATADIR)/20
	cp vo_zelda_itseemsRaw.bin         $(STATICDATADIR)/20/staticdata.bin
	echo "dtype 3\ndata1 3\ndata2 0" > $(STATICDATADIR)/20/conf.txt
	mkdir -p                           $(STATICDATADIR)/21
	cp vo_zelda_imsohappyRaw.bin       $(STATICDATADIR)/21/staticdata.bin
	echo "dtype 3\ndata1 4\ndata2 0" > $(STATICDATADIR)/21/conf.txt
	mkdir -p                           $(STATICDATADIR)/22
	cp vo_zelda_iknowtheyreRaw.bin     $(STATICDATADIR)/22/staticdata.bin
	echo "dtype 3\ndata1 5\ndata2 0" > $(STATICDATADIR)/22/conf.txt
	mkdir -p                           $(STATICDATADIR)/23
	cp vo_zelda_lookRaw.bin            $(STATICDATADIR)/23/staticdata.bin
	echo "dtype 3\ndata1 6\ndata2 0" > $(STATICDATADIR)/23/conf.txt
	mkdir -p                           $(STATICDATADIR)/24
	cp vo_zelda_youaskedRaw.bin        $(STATICDATADIR)/24/staticdata.bin
	echo "dtype 3\ndata1 7\ndata2 0" > $(STATICDATADIR)/24/conf.txt
	mkdir -p                           $(STATICDATADIR)/25
	cp vo_zelda_hereitisRaw.bin        $(STATICDATADIR)/25/staticdata.bin
	echo "dtype 3\ndata1 8\ndata2 0" > $(STATICDATADIR)/25/conf.txt
	mkdir -p                           $(STATICDATADIR)/26
	cp vo_zelda_thankyouRaw.bin        $(STATICDATADIR)/26/staticdata.bin
	echo "dtype 3\ndata1 9\ndata2 0" > $(STATICDATADIR)/26/conf.txt

%.c: %.wav
	$(Z64AUDIO) -i $< -o $@

clean:
	rm -f *.c *.h *.bin
