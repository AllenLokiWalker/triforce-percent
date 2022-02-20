include ../toolchain/make/main.mk

SOUNDS = \
	vo_link_zerudahime.c \
	vo_link_isshoni.c

Z64AUDIO = $(PROJECT_DIR)/toolchain/z64audio/z64audio

.PHONY: default clean

default: $(SOUNDS)
	mkdir -p                           $(STATICDATADIR)/12
	cp vo_link_zerudahime.bin          $(STATICDATADIR)/12/staticdata.bin
	echo "dtype 3\ndata1 0\ndata2 0" > $(STATICDATADIR)/12/conf.txt
	mkdir -p                           $(STATICDATADIR)/13
	cp vo_link_isshoni.bin             $(STATICDATADIR)/13/staticdata.bin
	echo "dtype 3\ndata1 1\ndata2 0" > $(STATICDATADIR)/13/conf.txt

%.c: %.wav
	$(Z64AUDIO) -i $< -o $@

clean:
	rm -f *.c *.h *.bin
