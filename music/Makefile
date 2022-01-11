include ../toolchain/make/main.mk

.PHONY: default clean

TARGETS=\
	OvertureOfSages.aseq \
	OvertureOfSagesWarp.aseq \
	ChamberOfSages.aseq \
	triforce.aseq \
	ChamberOfSagesBank.abnk

default: $(TARGETS)
	mkdir -p                                             $(STATICDATADIR)/6
	cp OvertureOfSages.aseq                              $(STATICDATADIR)/6/staticdata.bin
	echo "dtype 1\ndata1 0x6E020201\ndata2 0x09000000" > $(STATICDATADIR)/6/conf.txt
	mkdir -p                                             $(STATICDATADIR)/7
	cp OvertureOfSagesWarp.aseq                          $(STATICDATADIR)/7/staticdata.bin
	echo "dtype 1\ndata1 0x33020201\ndata2 0x09000000" > $(STATICDATADIR)/7/conf.txt
	mkdir -p                                             $(STATICDATADIR)/8
	cp ChamberOfSages.aseq                               $(STATICDATADIR)/8/staticdata.bin
	echo "dtype 1\ndata1 0x70020201\ndata2 0x26000000" > $(STATICDATADIR)/8/conf.txt
	mkdir -p                                             $(STATICDATADIR)/9
	cp ChamberOfSagesBank.abnk                           $(STATICDATADIR)/9/staticdata.bin
	echo "dtype 2\ndata1 0x26020201\ndata2 0x0B000000" > $(STATICDATADIR)/9/conf.txt
	mkdir -p                                             $(STATICDATADIR)/10
	cp triforce.aseq                                     $(STATICDATADIR)/10/staticdata.bin
	echo "dtype 1\ndata1 0x71020201\ndata2 0x03000000" > $(STATICDATADIR)/10/conf.txt
	mkdir -p                                             $(STATICDATADIR)/11
	cp PowerOfTheGoddesses.aseq                          $(STATICDATADIR)/11/staticdata.bin
	echo "dtype 1\ndata1 0x72020201\ndata2 0x03000000" > $(STATICDATADIR)/11/conf.txt
	#mkdir -p                                             $(STATICDATADIR)/8
	#cp Trailer.aseq                                      $(STATICDATADIR)/8/staticdata.bin
	#echo "dtype 1\ndata1 0x1F020201\ndata2 0x03000000" > $(STATICDATADIR)/8/conf.txt

# %.pat: %.aseq
# 	$(PYTHON3) ../toolchain/create_patch.py --full $< $@

CCFLAGS := $(CCOPTFLAGS) -I ../toolchain/AudiobankToC/include
LDFLAGS += -T ../toolchain/AudiobankToC/audiobank.ld

%.elf: %.o
	$(LD) $(LDFLAGS) -o $@ $<

clean: cleandir
	rm -f *.pat *.abnk
	
include ../toolchain/make/c.mk
