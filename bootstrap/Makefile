ifeq ($(PYTHON3),"")
	$(error Python3 command not defined or internal error)
endif

.PHONY: default clean buildrunbs

default: bootstrapper2.bin bootstrapper4.bin buildrunbs

%.o: %.s
	mips64-as -Os -o $@ $<

%.bin: %.o
	mips64-objcopy -O binary -j .text -j .data $< $@
	
buildrunbs:
	$(PYTHON3) ../toolchain/tas/ootbootstrap.py bootstrapper2.bin bootstrapper4.bin ../loader/fast_loader/fast_loader.bin ../run/bootstrap.m64
	$(PYTHON3) ../toolchain/tas/m642bk2.py ../run/bootstrap.m64 ../run/bootstrap-inputlog.txt

clean:
	rm *.o *.bin ../run/bootstrap.m64 ../run/bootstrap-inputlog.txt

