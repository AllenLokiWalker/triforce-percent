/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

padmgr = 0x8011D500;
osContStartReadData = 0x800D0160;
osContGetReadData = 0x800D01E4;

ENTRY(fl_init);

SECTIONS {
	. = 0x80400000;
	.start ALIGN(16): { *(.start) }
	.text ALIGN(16): { *(.text) }
	.data ALIGN(16): { *(.data) }
	.bss ALIGN(16):  { *(.bss) }
}
