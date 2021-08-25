	.file	1 "z_en_skj.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
 #APP
	.set noat
 .set noreorder
fabsf:
jr    $ra 
abs.s $f0, $f12
.set at
 .set reorder
 #NO_APP
	.local	sSmallStumpSkullKid
	.comm	sSmallStumpSkullKid,4,4
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	init
	.type	init, @function
init:
	.frame	$sp,48,$31		# vars= 0, regs= 3/0, args= 32, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	sw	$16,36($sp)
	move	$16,$4
	li	$4,7			# 0x7
	sw	$17,40($sp)
	sw	$31,44($sp)
	.set	noreorder
	.set	nomacro
	jal	Rupees_ChangeBy
	move	$17,$5
	.set	macro
	.set	reorder

	lhu	$2,28($16)
	li	$3,5			# 0x5
	srl	$2,$2,10
	.set	noreorder
	.set	nomacro
	bne	$2,$3,$L2
	li	$2,64			# 0x40
	.set	macro
	.set	reorder

	la	$2,invisDestroy
	sw	$2,300($16)
	la	$2,invisUpdate
	lw	$31,44($sp)
	sw	$16,sSmallStumpSkullKid
	sw	$0,308($16)
	sw	$2,304($16)
	move	$6,$16
	addiu	$5,$17,7204
	lw	$16,36($sp)
	move	$4,$17
	lw	$17,40($sp)
	li	$7,6			# 0x6
	.set	noreorder
	.set	nomacro
	j	Actor_ChangeCategory
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

$L2:
	sb	$2,279($16)
	lw	$2,4($16)
	lw	$7,$LC0
	ori	$2,$2,0x9
	sw	$2,4($16)
	addiu	$4,$16,180
	la	$6,ActorShadow_DrawCircle
	.set	noreorder
	.set	nomacro
	jal	ActorShape_Init
	move	$5,$0
	.set	macro
	.set	reorder

	li	$2,19			# 0x13
	sw	$2,24($sp)
	addiu	$2,$16,498
	sw	$2,20($sp)
	addiu	$2,$16,384
	addiu	$5,$16,316
	move	$4,$17
	la	$7,gSkullKidPlayFluteAnim
	la	$6,gSkullKidSkel
	.set	noreorder
	.set	nomacro
	jal	SkelAnime_InitFlex
	sw	$2,16($sp)
	.set	macro
	.set	reorder

	lw	$31,44($sp)
	lw	$17,40($sp)
	move	$4,$16
	lw	$5,$LC1
	lw	$16,36($sp)
	.set	noreorder
	.set	nomacro
	j	Actor_SetScale
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

	.end	init
	.size	init, .-init
	.align	2
	.globl	invisDestroy
	.set	nomips16
	.set	nomicromips
	.ent	invisDestroy
	.type	invisDestroy, @function
invisDestroy:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	.set	noreorder
	.set	nomacro
	jal	Rupees_ChangeBy
	li	$4,-1			# 0xffffffffffffffff
	.set	macro
	.set	reorder

	lw	$31,20($sp)
	sw	$0,sSmallStumpSkullKid
	.set	noreorder
	.set	nomacro
	jr	$31
	addiu	$sp,$sp,24
	.set	macro
	.set	reorder

	.end	invisDestroy
	.size	invisDestroy, .-invisDestroy
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	destroy
	.type	destroy, @function
destroy:
	.frame	$sp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$16,24($sp)
	move	$16,$4
	li	$4,-2			# 0xfffffffffffffffe
	sw	$31,28($sp)
	.set	noreorder
	.set	nomacro
	jal	Rupees_ChangeBy
	sw	$5,16($sp)
	.set	macro
	.set	reorder

	lw	$5,16($sp)
	lw	$31,28($sp)
	addiu	$4,$16,316
	lw	$16,24($sp)
	.set	noreorder
	.set	nomacro
	j	SkelAnime_Free
	addiu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	destroy
	.size	destroy, .-destroy
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	updateCommon
	.type	updateCommon, @function
updateCommon:
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 24, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	lw	$7,$LC2
	li	$2,7			# 0x7
	sw	$16,24($sp)
	move	$16,$4
	sw	$2,20($sp)
	move	$4,$5
	sw	$7,16($sp)
	move	$5,$16
	sw	$31,28($sp)
	.set	noreorder
	.set	nomacro
	jal	Actor_UpdateBgCheckInfo
	move	$6,$7
	.set	macro
	.set	reorder

	lw	$31,28($sp)
	addiu	$4,$16,316
	lw	$16,24($sp)
	.set	noreorder
	.set	nomacro
	j	SkelAnime_Update
	addiu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	updateCommon
	.size	updateCommon, .-updateCommon
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	isLinkOnStump
	.type	isLinkOnStump, @function
isLinkOnStump:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	lw	$3,sSmallStumpSkullKid
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L14
	move	$2,$0
	.set	macro
	.set	reorder

	lwc1	$f2,144($3)
	lwc1	$f0,$LC3
	c.lt.s	$f2,$f0
	#nop
	.set	noreorder
	.set	nomacro
	bc1t	$L14
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

	move	$2,$0
$L14:
	jr	$31
	.end	isLinkOnStump
	.size	isLinkOnStump, .-isLinkOnStump
	.align	2
	.globl	invisUpdate
	.set	nomips16
	.set	nomicromips
	.ent	invisUpdate
	.type	invisUpdate, @function
invisUpdate:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	jr	$31
	.end	invisUpdate
	.size	invisUpdate, .-invisUpdate
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	update_NotOnStump
	.type	update_NotOnStump, @function
update_NotOnStump:
	.frame	$sp,40,$31		# vars= 0, regs= 2/0, args= 32, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-40
	sw	$16,32($sp)
	sw	$31,36($sp)
	.set	noreorder
	.set	nomacro
	jal	updateCommon
	move	$16,$4
	.set	macro
	.set	reorder

	lw	$2,sSmallStumpSkullKid
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L25
	lw	$31,36($sp)
	.set	macro
	.set	reorder

	jal	isLinkOnStump
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L25
	lw	$31,36($sp)
	.set	macro
	.set	reorder

	la	$4,gSkullKidWaitAnim
	jal	Animation_GetLastFrame
	lwc1	$f0,$LC5
	lw	$6,$LC4
	swc1	$f0,24($sp)
	mtc1	$2,$f0
	sw	$0,20($sp)
	cvt.s.w	$f0,$f0
	swc1	$f0,16($sp)
	move	$7,$0
	la	$5,gSkullKidWaitAnim
	.set	noreorder
	.set	nomacro
	jal	Animation_Change
	addiu	$4,$16,316
	.set	macro
	.set	reorder

	lw	$31,36($sp)
$L25:
	lw	$16,32($sp)
	.set	noreorder
	.set	nomacro
	jr	$31
	addiu	$sp,$sp,40
	.set	macro
	.set	reorder

	.end	update_NotOnStump
	.size	update_NotOnStump, .-update_NotOnStump
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	draw
	.type	draw, @function
draw:
	.frame	$sp,48,$31		# vars= 0, regs= 3/0, args= 32, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	sw	$16,36($sp)
	move	$16,$4
	lw	$4,0($5)
	sw	$31,44($sp)
	sw	$17,40($sp)
	.set	noreorder
	.set	nomacro
	jal	func_80093D18
	move	$17,$5
	.set	macro
	.set	reorder

	la	$2,dList.22262
	li	$3,-83886080			# 0xfffffffffb000000
	lw	$4,gGlobalContext
	sw	$3,0($2)
	li	$3,255			# 0xff
	sw	$3,4($2)
	li	$3,-553648128			# 0xffffffffdf000000
	sw	$3,8($2)
	lw	$3,704($4)
	sw	$0,12($2)
	addiu	$5,$3,8
	sw	$5,704($4)
	li	$4,-620363776			# 0xffffffffdb060000
	addiu	$4,$4,48
	sw	$4,0($3)
	sw	$2,4($3)
	lbu	$7,318($16)
	lw	$6,348($16)
	lw	$5,320($16)
	sw	$16,24($sp)
	sw	$0,20($sp)
	sw	$0,16($sp)
	.set	noreorder
	.set	nomacro
	jal	SkelAnime_DrawFlexOpa
	move	$4,$17
	.set	macro
	.set	reorder

	lw	$31,44($sp)
	lw	$17,40($sp)
	lw	$16,36($sp)
	.set	noreorder
	.set	nomacro
	jr	$31
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

	.end	draw
	.size	draw, .-draw
	.globl	init_vars
	.rdata
	.align	2
	.type	init_vars, @object
	.size	init_vars, 32
init_vars:
	.half	-8531
	.byte	4
	.space	1
	.word	16
	.half	266
	.half	-16657
	.word	612
	.word	init
	.word	destroy
	.word	update_NotOnStump
	.word	draw
	.local	dList.22262
	.comm	dList.22262,16,8
	.section	.rodata.cst4,"aM",@progbits,4
	.align	2
$LC0:
	.word	1109393408
	.align	2
$LC1:
	.word	1008981770
	.align	2
$LC2:
	.word	1101004800
	.align	2
$LC3:
	.word	1104150528
	.align	2
$LC4:
	.word	1065353216
	.align	2
$LC5:
	.word	3238002688
	.ident	"GCC: (GNU) 9.2.0"
