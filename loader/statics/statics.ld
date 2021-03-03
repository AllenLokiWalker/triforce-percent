/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE common/z_functions.ld
INCLUDE fast_loader/fast_loader.out.ld
INCLUDE debugger/debugger.out.ld
INCLUDE dma_patcher/dma_patcher.out.ld

INCLUDE statics/interface.ld
INCLUDE statics/message.ld

gGlobalContext = 0x801C84A0;
gSaveContext = 0x8011A5D0;

Audio_FadeOut = 0x800C7684;

SECTIONS {
	. = dma_patcher_END;
	.start ALIGN(16): { *(.start) }
	.text ALIGN(16): { *(.text) }
	.data ALIGN(16): { *(.data) }
	.bss ALIGN(16):  { *(.bss) }
}
