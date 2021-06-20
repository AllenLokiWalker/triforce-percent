SELF_PATH := $(shell echo "$(MAKEFILE_LIST)" | sed -e "s/.*Makefile //")
PROJECT_DIR := $(dir $(SELF_PATH))../..

ifeq ("$(wildcard $(PROJECT_DIR)/local.mk)","")
    $(error You have not read README.md, please do so)
endif

ifeq ("$(and $(wildcard $(PROJECT_DIR)/build-shortcut/oot_1.0U_comp.z64), $(wildcard $(PROJECT_DIR)/build-romhack/oot_1.0U_uncomp.z64))","")
    $(error Original ROMs not found, please read README.md)
endif

ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/ZAP2/Makefile)","")
    $(error You did not properly set up the Git submodules (ZAP2 makefile not found))
endif

include $(PROJECT_DIR)/local.mk
export

ifeq ($(PYTHON3),"")
	$(error Python3 command definition missing from local.mk)
endif

# Disables built-in rules (e.g. how to make .o from .c)
.SUFFIXES:
#empty

# Main tools

CC = mips64-gcc
AS = mips64-as
LD = mips64-ld
OC = mips64-objcopy

# Main flags

CFLAGS = -mips3 -mabi=32 -mtune=vr4300 -mno-gpopt -fomit-frame-pointer \
	-mno-check-zero-division -mno-explicit-relocs -mno-memcpy \
	-fno-toplevel-reorder -fno-reorder-blocks \
	--std=gnu99 -Wall -Wno-main -Wno-missing-braces \
	-G 0 -Os
# loader and statics had -O2 instead of -Os

LDFLAGS = --emit-relocs
OCFLAGS = -R .MIPS.abiflags -O binary
