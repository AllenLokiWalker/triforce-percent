include ../toolchain/make/main.mk

.PHONY: default clean
	
STATICDATANUM := 0
STATICDATADIR := ../build-romhack/staticdata/$(STATICDATANUM)

default: anim.bin anim.c
	mkdir -p $(STATICDATADIR)
	cp anim.bin $(STATICDATADIR)/staticdata.bin
	echo "data1 0\ndata2 0" > $(STATICDATADIR)/conf.txt

anim.bin anim.c: anim.txt ../toolchain/animcat.py linkcustomanim.objex
	$(PYTHON3) ../toolchain/animcat.py

clean:
	rm -f anim.bin anim.c
