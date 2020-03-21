/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE karg_common/karg_common.ld

ENTRY(fl_init);

SECTIONS {
	. = 0x80400000;
	.start ALIGN(4): { *(.start) }
	.text ALIGN(4): { *(.text) }
	.data ALIGN(4): { *(.data) }
	.bss ALIGN(4):  { *(.bss) }
}

/* z_functions */

__osDisableInt = 0x80005130;
__osRestoreInt = 0x800051A0;
osWritebackDCache = 0x80003440;
osInvalICache = 0x800041A0;
bzero = 0x80002E80;
osRecvMesg = 0x80002030;
DmaMgr_SendRequest0 = 0x80001AA0;
Yaz0_Decompress = 0x80001254;
osContStartReadData = 0x800D0160;
osContGetReadData = 0x800D01E4;

/* fast_loader */

fl_gvars = 0x80412000;
padmgr = 0x8011D500;
