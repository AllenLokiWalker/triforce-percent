/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE common/z_functions.ld
INCLUDE fast_loader/fast_loader.out.ld

sExceptionNames = 0x800FF320;
__osFaultedThread = 0x80006344;
padmgrth = 0x8011D580;

ENTRY(DmaPatcher_Init);

SECTIONS {
	. = fast_loader_END;
	.start ALIGN(16): { *(.start) }
	.text ALIGN(16): { *(.text) }
	.data ALIGN(16): { *(.data) }
	.bss ALIGN(16):  { *(.bss) }
}
