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
	vo_zelda_thankyou.c \
	chimes.c

Z64AUDIO = $(PROJECT_DIR)/toolchain/z64audio/z64audio

.PHONY: default clean

define procvoice
	mkdir -p $(STATICDATADIR)/$(1)
	cp $(3).vadpcm.bin $(STATICDATADIR)/$(1)/staticdata.bin
	echo "dtype 3\ndata1 $(2)\ndata2 0" > $(STATICDATADIR)/$(1)/conf.txt
	sed -i 's|#include|//|g' $(3).c
endef

default: $(SOUNDS)
	$(call procvoice,17,0,vo_link_zerudahime)
	$(call procvoice,18,1,vo_link_isshoni)
	$(call procvoice,19,2,vo_zelda_link)
	$(call procvoice,20,3,vo_zelda_itseems)
	$(call procvoice,21,4,vo_zelda_imsohappy)
	$(call procvoice,22,5,vo_zelda_iknowtheyre)
	$(call procvoice,23,6,vo_zelda_look)
	$(call procvoice,24,7,vo_zelda_youasked)
	$(call procvoice,25,8,vo_zelda_hereitis)
	$(call procvoice,26,9,vo_zelda_thankyou)
	$(call procvoice,27,10,chimes)

%.c: %.wav
	$(Z64AUDIO) -i $< -o $@

clean:
	rm -f *.c *.h *.bin
