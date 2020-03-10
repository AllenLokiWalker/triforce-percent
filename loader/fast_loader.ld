/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

gvars = 0x8040C000;
padmgr = 0x8011D500;

DmaMgr_SendRequest0 = 0x80001AA0;
osContStartReadData = 0x800D0160;
osRecvMesg = 0x80002030;
osContGetReadData = 0x800D01E4;

ENTRY( init );

SECTIONS {
	. = 0x80400000;
	.start ALIGN( 4 ): { *(.start) }
	.text ALIGN( 4 ): { *(.text) }
	.data ALIGN( 4 ): { *(.data) }
	.bss ALIGN( 4 ):  { *(.bss) }
}

