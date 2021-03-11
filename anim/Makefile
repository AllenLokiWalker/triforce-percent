.PHONY: default clean

default: anim.bin anim.c

anim.bin anim.c: anim.txt ../toolchain/animcat.py
	$(PYTHON3) ../toolchain/animcat.py

clean:
	rm -f anim.bin anim.c
