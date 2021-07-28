/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE ../loader/fast_loader/fast_loader.out.ld
INCLUDE ../loader/debugger/debugger.out.ld
INCLUDE ../loader/dma_patcher/dma_patcher.out.ld

INCLUDE interface.ld
INCLUDE message.ld
INCLUDE anime.ld
INCLUDE ocarina.ld
INCLUDE audio.ld
INCLUDE gfx.ld

linkJumpYSpeed = 0x808514A8;

SECTIONS {
	. = dma_patcher_END;
	.start ALIGN(16): { *(.start) }
	.text ALIGN(16): { *(.text) }
	.data ALIGN(16): { *(.data) }
	.bss ALIGN(16):  { *(.bss) }
}
