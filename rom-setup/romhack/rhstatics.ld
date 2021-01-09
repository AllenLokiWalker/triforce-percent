OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE ../../loader/statics/statics.out.ld

DmaMgr_Init = 0x80000E6C;
Main = 0x800A1C50;
osGetMemSize = 0x80003E90;

ENTRY_POINT = 0x800005A0;
ENTRY(ENTRY_POINT)

SECTIONS {
	. = ENTRY_POINT;
	.text ALIGN(4): { FILL(0); *(.text); . = ALIGN(4); }
	.data ALIGN(4): { FILL(0); *(.data); . = ALIGN(4); }
	.rodata ALIGN(4): { FILL(0); *(.rodata); . = ALIGN(4); }
	.bss ALIGN(4): { *(.bss); . = ALIGN(4); }
	. = ALIGN(4);
	end = .;
}
