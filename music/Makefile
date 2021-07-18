include ../toolchain/make/main.mk

.PHONY: default clean

STATICDATADIR := ../build-romhack/staticdata
SDIR_SEQ0 := $(STATICDATADIR)/1
SDIR_SEQ1 := $(STATICDATADIR)/2
SDIR_SEQ2 := $(STATICDATADIR)/3
SDIR_SEQ3 := $(STATICDATADIR)/4
SDIR_SEQ4 := $(STATICDATADIR)/5
SDIR_SEQ5 := $(STATICDATADIR)/6
SDIR_SEQ6 := $(STATICDATADIR)/7
SDIR_SEQ7 := $(STATICDATADIR)/8
SDIR_SEQ8 := $(STATICDATADIR)/9

default: OvertureOfSages.aseq triforce.aseq
	mkdir -p                                             $(SDIR_SEQ0)
	cp OvertureOfSages.aseq                              $(SDIR_SEQ0)/staticdata.bin
	echo "dtype 1\ndata1 0x6E020201\ndata2 0x09000000" > $(SDIR_SEQ0)/conf.txt
	mkdir -p                                             $(SDIR_SEQ3)
	cp triforce.aseq                                     $(SDIR_SEQ3)/staticdata.bin
	echo "dtype 1\ndata1 0x71020201\ndata2 0x03000000" > $(SDIR_SEQ3)/conf.txt
	

# %.pat: %.aseq
# 	$(PYTHON3) ../toolchain/create_patch.py --full $< $@

clean:
	rm -f *.pat
	
