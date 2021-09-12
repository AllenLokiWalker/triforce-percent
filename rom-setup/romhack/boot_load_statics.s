	.file	1 "boot_load_statics.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.align	2
	.globl	func_800005A0
	.set	nomips16
	.set	nomicromips
	.ent	func_800005A0
	.type	func_800005A0, @function
func_800005A0:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	jal	DmaMgr_Init
	move	$16,$4
	.set	macro
	.set	reorder

	li	$6,1048576			# 0x100000
	li	$5,11010048			# 0xa80000
	li	$4,-2147418112			# 0xffffffff80010000
	addiu	$6,$6,15664
	addiu	$5,$5,28672
	.set	noreorder
	.set	nomacro
	jal	DmaMgr_SendRequest1
	addiu	$4,$4,4256
	.set	macro
	.set	reorder

	li	$5,65536			# 0x10000
	li	$4,-2146369536			# 0xffffffff80110000
	addiu	$5,$5,28768
	.set	noreorder
	.set	nomacro
	jal	bzero
	addiu	$4,$4,19920
	.set	macro
	.set	reorder

	la	$4,rhstaticsFile.22283
	jal	DmaMgr_ProcessMsg
	lw	$31,20($sp)
	move	$4,$16
	lw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	j	Main
	addiu	$sp,$sp,24
	.set	macro
	.set	reorder

	.end	func_800005A0
	.size	func_800005A0, .-func_800005A0
	.data
	.align	2
	.type	rhstaticsFile.22283, @object
	.size	rhstaticsFile.22283, 12
rhstaticsFile.22283:
	.word	-559038737
	.word	statics_START
	.word	69233001
	.ident	"GCC: (GNU) 9.2.0"
