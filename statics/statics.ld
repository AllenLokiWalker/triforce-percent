/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE ../loader/fast_loader/fast_loader.out.ld
INCLUDE ../loader/dma_patcher/dma_patcher.out.ld

INCLUDE z64structs.ld
INCLUDE z64funcs.ld
INCLUDE interface.ld
INCLUDE message.ld
INCLUDE anime.ld

SECTIONS {
	. = dma_patcher_END;
	.start ALIGN(16): { *(.start) }
	.text ALIGN(16): { *(.text) }
	.data ALIGN(16): { *(.data) }
	.bss ALIGN(16):  { *(.bss) }
}
