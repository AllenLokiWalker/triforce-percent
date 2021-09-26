include ../toolchain/make/main.mk

.PHONY: default clean

STATICDATADIR := ../build-romhack/staticdata

default: OvertureOfSages.aseq triforce.aseq
	mkdir -p                                             $(STATICDATADIR)/6
	cp OvertureOfSages.aseq                              $(STATICDATADIR)/6/staticdata.bin
	echo "dtype 1\ndata1 0x6E020201\ndata2 0x09000000" > $(STATICDATADIR)/6/conf.txt
	mkdir -p                                             $(STATICDATADIR)/7
	cp triforce.aseq                                     $(STATICDATADIR)/7/staticdata.bin
	echo "dtype 1\ndata1 0x71020201\ndata2 0x03000000" > $(STATICDATADIR)/7/conf.txt
	

# %.pat: %.aseq
# 	$(PYTHON3) ../toolchain/create_patch.py --full $< $@

clean:
	rm -f *.pat
	
