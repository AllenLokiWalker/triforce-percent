include ../toolchain/make/main.mk

.PHONY: default clean

default: anim.bin anim.c

anim.bin anim.c: anim.txt ../toolchain/animcat.py linkcustomanim.objex
	$(PYTHON3) ../toolchain/animcat.py

clean:
	rm -f anim.bin anim.c
