ifeq ("$(wildcard ZAP2/Makefile)","")
    $(error You did not properly set up the Git submodules (ZAP2 makefile not found))
endif

.PHONY: default clean zap2

default: zap2

zap2:
	#sed -i 's/ -O2 / -g /g' ZAP2/makefile
	$(MAKE) -C ZAP2/ $(MAKECMDGOALS)
	#sed -i 's/ -g / -O2 /g' ZAP2/makefile
