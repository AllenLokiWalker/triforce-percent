include ../toolchain/make/main.mk

SOUNDS = link_demo_1_32.c link_demo_2_32.c link_demo_3_32.c

Z64AUDIO = $(PROJECT_DIR)/toolchain/z64audio/z64audio

.PHONY: default clean

default: $(SOUNDS)
	mkdir -p                           $(STATICDATADIR)/8
	cp link_demo_1_32Raw.bin           $(STATICDATADIR)/8/staticdata.bin
	echo "dtype 3\ndata1 0\ndata2 0" > $(STATICDATADIR)/8/conf.txt
	mkdir -p                           $(STATICDATADIR)/9
	cp link_demo_2_32Raw.bin           $(STATICDATADIR)/9/staticdata.bin
	echo "dtype 3\ndata1 1\ndata2 0" > $(STATICDATADIR)/9/conf.txt
	mkdir -p                           $(STATICDATADIR)/10
	cp link_demo_3_32Raw.bin           $(STATICDATADIR)/10/staticdata.bin
	echo "dtype 3\ndata1 2\ndata2 0" > $(STATICDATADIR)/10/conf.txt

%.c: %.wav
	$(Z64AUDIO) -i $< -o $@

clean:
	rm -f *.c *.h *.bin