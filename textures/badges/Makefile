include ../../toolchain/make/main.mk

default: badges.inc

badges.inc: badges.json badges.py
	$(PYTHON3) badges.py

clean:
	rm -f badges.inc
