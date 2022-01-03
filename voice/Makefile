include ../toolchain/make/main.mk

SOUNDS = link_demo_1_32.c link_demo_2_32.c link_demo_3_32.c

Z64AUDIO = $(PROJECT_DIR)/toolchain/z64audio/z64audio

.PHONY: default clean

default: $(SOUNDS)
	mkdir -p                           $(STATICDATADIR)/11
	cp link_demo_1_32Raw.bin           $(STATICDATADIR)/11/staticdata.bin
	echo "dtype 3\ndata1 0\ndata2 0" > $(STATICDATADIR)/11/conf.txt
	mkdir -p                           $(STATICDATADIR)/12
	cp link_demo_2_32Raw.bin           $(STATICDATADIR)/12/staticdata.bin
	echo "dtype 3\ndata1 1\ndata2 0" > $(STATICDATADIR)/12/conf.txt
	mkdir -p                           $(STATICDATADIR)/13
	cp link_demo_3_32Raw.bin           $(STATICDATADIR)/13/staticdata.bin
	echo "dtype 3\ndata1 2\ndata2 0" > $(STATICDATADIR)/13/conf.txt

%.c: %.wav
	$(Z64AUDIO) -i $< -o $@

clean:
	rm -f *.c *.h *.bin
