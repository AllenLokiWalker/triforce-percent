/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE ../karg_common/karg_common.ld

link_vel      = 0xA01DAA8C;
link_speed    = 0xA01DAA98;
link_health   = 0xA011A600;
b_button_slot = 0xA011A638;

dgvars = 0x80414000;

ENTRY( run );

SECTIONS {
	. = 0x80402000;
	.start ALIGN( 4 ): { *(.start) }
	.text ALIGN( 4 ): { *(.text) }
	.data ALIGN( 4 ): { *(.data) }
	.bss ALIGN( 4 ):  { *(.bss) }
}

