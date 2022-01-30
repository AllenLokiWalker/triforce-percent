include ../../toolchain/make/main.mk

default: badges.inc

badges.inc: badges.json badges.py
	PYTHONPATH="$(PROJECT_DIR)/toolchain/ci4tool" $(PYTHON3) badges.py

clean:
	rm -f badges.inc
