/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE common/z_functions.ld
INCLUDE debugger/debugger.out.ld

gDmaDataTable = 0x8000B140;

ENTRY(DmaPatcher_Init);

SECTIONS {
	. = debugger_END;
	.start ALIGN(16): { *(.start) }
	.text ALIGN(16): { *(.text) }
	.data ALIGN(16): { *(.data) }
	.bss ALIGN(16):  { *(.bss) }
}
