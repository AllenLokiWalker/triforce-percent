include ../toolchain/make/main.mk

.PHONY: default clean

default: fast_loader/fast_loader.bin debugger/debugger.bin dma_patcher/dma_patcher.map dma_patcher/dma_patcher.bin

#Dependencies

debugger/debugger.o: fast_loader/fast_loader.h

debugger/debugger.elf: fast_loader/fast_loader.out.ld

dma_patcher/dma_patcher.o: debugger/debugger.h

dma_patcher/dma_patcher.elf: debugger/debugger.out.ld
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.elf %.map: %.o %.ld
	$(LD) $(LDFLAGS) -T $*.ld -Map $*.map -o $*.elf $*.o
	
%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

%.out.ld: %.map
	$(PYTHON3) ../toolchain/ldout.py $< $@

clean:
	rm -rf */*.o */*.map */*.elf fast_loader/fast_loader.bin debugger/debugger.bin dma_patcher/dma_patcher.bin
