include ../toolchain/make/main.mk
include ../toolchain/make/assembly.mk

BOOTSTRAPPERS = bootstrapper2.bin bootstrapper4.bin
FAST_LOADER = ../loader/fast_loader/fast_loader.bin
BSM64 = ../run/bootstrap.m64
BSTXT = ../run/bootstrap-inputlog.txt

.PHONY: default clean

.PRECIOUS: $(BOOTSTRAPPERS)

default: $(BSM64) $(BSTXT)

$(BSM64): $(BOOTSTRAPPERS) $(FAST_LOADER)
	$(PYTHON3) ../toolchain/tas/ootbootstrap.py $^ $@

$(BSTXT): $(BSM64)
	$(PYTHON3) ../toolchain/tas/m642bk2.py $< $@

clean:
	rm -f *.o *.bin $(BSM64) $(BSTXT)

