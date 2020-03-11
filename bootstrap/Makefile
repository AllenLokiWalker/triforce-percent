.PHONY: default clean

default: bootstrapper2.bin bootstrapper4.bin

%.o: %.s
	mips64-as -Os -o $@ $<

%.bin: %.o
	mips64-objcopy -O binary -j .text -j .data $< $@

clean:
	rm *.o *.bin
