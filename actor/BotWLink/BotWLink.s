	.file	1 "BotWLink.c"
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
	sw	$17,40($sp)
	move	$17,$5
	lw	$5,$LC0
	sw	$31,44($sp)
	sw	$16,36($sp)
	.set	noreorder
	.set	nomacro
	jal	Actor_SetScale
	move	$16,$4
	.set	macro
	.set	reorder

	li	$2,30			# 0x1e
	sw	$2,24($sp)
	addiu	$2,$16,640
	sw	$2,20($sp)
	addiu	$2,$16,460
	addiu	$5,$16,316
	move	$4,$17
	la	$7,BotWLinkMeshIdleAnim
	la	$6,BotWLinkMesh
	.set	noreorder
	.set	nomacro
	jal	SkelAnime_InitFlex
	sw	$2,16($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	Rupees_ChangeBy
	li	$4,4			# 0x4
	.set	macro
	.set	reorder

	lw	$31,44($sp)
	lw	$17,40($sp)
	sw	$0,820($16)
	lw	$16,36($sp)
	.set	noreorder
	.set	nomacro
	jr	$31
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

	.end	init
	.size	init, .-init
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	destroy
	.type	destroy, @function
destroy:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	SkelAnime_Free
	addiu	$4,$4,316
	.set	macro
	.set	reorder

	.end	destroy
	.size	destroy, .-destroy
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	uncullObject
	.type	uncullObject, @function
uncullObject:
	.frame	$sp,56,$31		# vars= 16, regs= 1/4, args= 16, gp= 0
	.mask	0x80000000,-20
	.fmask	0x00f00000,-8
	addiu	$sp,$sp,-56
	sdc1	$f22,48($sp)
	sdc1	$f20,40($sp)
	mtc1	$6,$f22
	mtc1	$7,$f20
	addiu	$6,$sp,16
	sw	$31,36($sp)
	.set	noreorder
	.set	nomacro
	jal	func_8002BE04
	addiu	$7,$sp,28
	.set	macro
	.set	reorder

	lw	$3,76($sp)
	li	$2,-2147483648			# 0xffffffff80000000
	xor	$2,$2,$3
	lwc1	$f0,24($sp)
	mtc1	$2,$f2
	#nop
	c.lt.s	$f2,$f0
	#nop
	.set	noreorder
	.set	nomacro
	bc1t	$L5
	lwc1	$f2,80($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	b	$L6
	move	$2,$0
	.set	macro
	.set	reorder

$L5:
	c.lt.s	$f0,$f2
	#nop
	.set	noreorder
	.set	nomacro
	bc1f	$L6
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	fabsf
	lwc1	$f12,16($sp)
	.set	macro
	.set	reorder

	sub.s	$f2,$f0,$f22
	lwc1	$f4,28($sp)
	lwc1	$f6,$LC1
	mul.s	$f2,$f2,$f4
	nop
	c.lt.s	$f2,$f6
	#nop
	.set	noreorder
	.set	nomacro
	bc1f	$L6
	move	$2,$0
	.set	macro
	.set	reorder

	lwc1	$f0,20($sp)
	lwc1	$f2,72($sp)
	lwc1	$f8,$LC2
	add.s	$f2,$f0,$f2
	mul.s	$f2,$f2,$f4
	nop
	c.lt.s	$f8,$f2
	#nop
	.set	noreorder
	.set	nomacro
	bc1f	$L17
	lw	$31,36($sp)
	.set	macro
	.set	reorder

	sub.s	$f0,$f0,$f20
	mul.s	$f0,$f0,$f4
	nop
	c.lt.s	$f0,$f6
	#nop
	.set	noreorder
	.set	nomacro
	bc1t	$L17
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

	move	$2,$0
$L6:
	lw	$31,36($sp)
$L17:
	ldc1	$f22,48($sp)
	ldc1	$f20,40($sp)
	.set	noreorder
	.set	nomacro
	jr	$31
	addiu	$sp,$sp,56
	.set	macro
	.set	reorder

	.end	uncullObject
	.size	uncullObject, .-uncullObject
	.data
	.align	2
	.type	VoiceFreqScale, @object
	.size	VoiceFreqScale, 4
VoiceFreqScale:
	.word	1065353216
	.align	2
	.type	VoiceVol, @object
	.size	VoiceVol, 4
VoiceVol:
	.word	1069547520
	.local	VoiceReverbAdd
	.comm	VoiceReverbAdd,4,4
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC3:
	.ascii	"off\000"
	.align	2
$LC4:
	.ascii	"on\000"
	.align	2
$LC14:
	.ascii	"calves %s legs %s\000"
	.text
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	update
	.type	update, @function
update:
	.frame	$sp,80,$31		# vars= 16, regs= 4/4, args= 32, gp= 0
	.mask	0x80070000,-20
	.fmask	0x00f00000,-8
	la	$3,gGlobalContext
	lhu	$2,20($3)
	addiu	$sp,$sp,-80
	andi	$2,$2,0x30
	sw	$18,56($sp)
	sw	$17,52($sp)
	sw	$16,48($sp)
	sw	$31,60($sp)
	sdc1	$f22,72($sp)
	sdc1	$f20,64($sp)
	move	$16,$4
	move	$17,$5
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L19
	addiu	$18,$4,316
	.set	macro
	.set	reorder

	lhu	$2,32($3)
	andi	$2,$2,0x200
	.set	noreorder
	.set	nomacro
	beql	$2,$0,$L40
	lbu	$2,828($16)
	.set	macro
	.set	reorder

	li	$2,1			# 0x1
	sb	$2,828($4)
	la	$4,BotWLinkMeshBobokuwaAnim
	jal	Animation_GetLastFrame
	lwc1	$f0,$LC5
	li	$3,2			# 0x2
	swc1	$f0,24($sp)
	mtc1	$2,$f0
	lw	$6,$LC1
	cvt.s.w	$f0,$f0
	sw	$3,20($sp)
	swc1	$f0,16($sp)
	move	$7,$0
	la	$5,BotWLinkMeshBobokuwaAnim
	.set	noreorder
	.set	nomacro
	jal	Animation_Change
	move	$4,$18
	.set	macro
	.set	reorder

$L19:
	lbu	$2,828($16)
$L40:
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L20
	li	$3,5			# 0x5
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$3,$L21
	addiu	$2,$2,1
	.set	macro
	.set	reorder

	la	$2,VoiceReverbAdd
	sw	$2,20($sp)
	la	$2,VoiceVol
	sw	$2,16($sp)
	la	$7,VoiceFreqScale
	li	$6,4			# 0x4
	addiu	$5,$16,228
	.set	noreorder
	.set	nomacro
	jal	Audio_PlaySoundGeneral
	li	$4,14791			# 0x39c7
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	b	$L20
	sb	$0,828($16)
	.set	macro
	.set	reorder

$L21:
	sb	$2,828($16)
$L20:
	.set	noreorder
	.set	nomacro
	jal	SkelAnime_Update
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beql	$2,$0,$L41
	lw	$2,820($16)
	.set	macro
	.set	reorder

	la	$4,BotWLinkMeshIdleAnim
	jal	Animation_GetLastFrame
	lwc1	$f0,$LC6
	lw	$6,$LC1
	swc1	$f0,24($sp)
	mtc1	$2,$f0
	sw	$0,20($sp)
	cvt.s.w	$f0,$f0
	swc1	$f0,16($sp)
	move	$7,$0
	la	$5,BotWLinkMeshIdleAnim
	.set	noreorder
	.set	nomacro
	jal	Animation_Change
	move	$4,$18
	.set	macro
	.set	reorder

	lw	$2,820($16)
$L41:
	li	$3,-4			# 0xfffffffffffffffc
	sw	$2,824($16)
	and	$2,$2,$3
	lw	$3,40($16)
	lwc1	$f2,$LC7
	sw	$3,36($sp)
	lwc1	$f0,36($sp)
	lw	$4,36($16)
	add.s	$f0,$f0,$f2
	lwc1	$f22,$LC10
	lwc1	$f20,$LC11
	sw	$2,820($16)
	lw	$7,$LC8
	lw	$2,44($16)
	lw	$6,$LC9
	sw	$4,32($sp)
	swc1	$f22,24($sp)
	swc1	$f20,20($sp)
	sw	$0,16($sp)
	addiu	$5,$sp,32
	move	$4,$17
	sw	$2,40($sp)
	.set	noreorder
	.set	nomacro
	jal	uncullObject
	swc1	$f0,36($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bnel	$2,$0,$L42
	lw	$3,40($16)
	.set	macro
	.set	reorder

	lw	$2,820($16)
	ori	$2,$2,0x1
	sw	$2,820($16)
	lw	$3,40($16)
$L42:
	lwc1	$f2,$LC12
	sw	$3,36($sp)
	lwc1	$f0,36($sp)
	lw	$4,36($16)
	add.s	$f0,$f0,$f2
	lw	$2,44($16)
	lw	$7,$LC13
	mfc1	$6,$f20
	sw	$4,32($sp)
	swc1	$f22,24($sp)
	swc1	$f20,20($sp)
	sw	$0,16($sp)
	addiu	$5,$sp,32
	move	$4,$17
	sw	$2,40($sp)
	.set	noreorder
	.set	nomacro
	jal	uncullObject
	swc1	$f0,36($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bnel	$2,$0,$L43
	lw	$3,824($16)
	.set	macro
	.set	reorder

	lw	$2,820($16)
	ori	$2,$2,0x2
	sw	$2,820($16)
	lw	$3,824($16)
$L43:
	lw	$2,820($16)
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L44
	lw	$31,60($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	Debugger_GetNextMessageBuffer
	li	$4,255			# 0xff
	.set	macro
	.set	reorder

	lw	$3,820($16)
	move	$4,$2
	andi	$2,$3,0x1
	la	$6,$LC3
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L45
	andi	$3,$3,0x2
	.set	macro
	.set	reorder

	la	$6,$LC4
$L45:
	la	$7,$LC3
	bne	$3,$0,$L27
	la	$7,$LC4
$L27:
	la	$5,$LC14
	jal	sprintf
	lw	$31,60($sp)
$L44:
	lw	$18,56($sp)
	lw	$17,52($sp)
	lw	$16,48($sp)
	ldc1	$f22,72($sp)
	ldc1	$f20,64($sp)
	.set	noreorder
	.set	nomacro
	jr	$31
	addiu	$sp,$sp,80
	.set	macro
	.set	reorder

	.end	update
	.size	update, .-update
	.align	2
	.globl	BotWLink_OverrideLimbDraw
	.set	nomips16
	.set	nomicromips
	.ent	BotWLink_OverrideLimbDraw
	.type	BotWLink_OverrideLimbDraw, @function
BotWLink_OverrideLimbDraw:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	lw	$2,20($sp)
	lw	$3,820($2)
	andi	$2,$3,0x1
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L59
	andi	$3,$3,0x2
	.set	macro
	.set	reorder

	li	$2,24768			# 0x60c0
	sra	$2,$2,$5
	andi	$2,$2,0x1
	.set	noreorder
	.set	nomacro
	bnel	$2,$0,$L60
	sw	$0,0($6)
	.set	macro
	.set	reorder

$L59:
	beq	$3,$0,$L49
	li	$2,32760			# 0x7ff8
	sra	$5,$2,$5
	andi	$5,$5,0x1
	beq	$5,$0,$L49
	sw	$0,0($6)
$L49:
$L60:
	.set	noreorder
	.set	nomacro
	jr	$31
	move	$2,$0
	.set	macro
	.set	reorder

	.end	BotWLink_OverrideLimbDraw
	.size	BotWLink_OverrideLimbDraw, .-BotWLink_OverrideLimbDraw
	.align	2
	.globl	BotWLink_PostLimbDraw
	.set	nomips16
	.set	nomicromips
	.ent	BotWLink_PostLimbDraw
	.type	BotWLink_PostLimbDraw, @function
BotWLink_PostLimbDraw:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	jr	$31
	.end	BotWLink_PostLimbDraw
	.size	BotWLink_PostLimbDraw, .-BotWLink_PostLimbDraw
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

	la	$2,BotWLink_PostLimbDraw
	sw	$2,20($sp)
	lbu	$7,318($16)
	lw	$6,348($16)
	lw	$5,320($16)
	la	$2,BotWLink_OverrideLimbDraw
	sw	$16,24($sp)
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	SkelAnime_DrawFlexOpa
	sw	$2,16($sp)
	.set	macro
	.set	reorder

	lw	$31,44($sp)
	lw	$16,36($sp)
	lw	$4,0($17)
	lw	$17,40($sp)
	.set	noreorder
	.set	nomacro
	j	func_80093D18
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
	.byte	6
	.space	1
	.word	16
	.half	122
	.half	-16657
	.word	832
	.word	init
	.word	destroy
	.word	update
	.word	draw
	.section	.rodata.cst4,"aM",@progbits,4
	.align	2
$LC0:
	.word	1024416809
	.align	2
$LC1:
	.word	1065353216
	.align	2
$LC2:
	.word	3212836864
	.align	2
$LC5:
	.word	3229614080
	.align	2
$LC6:
	.word	3238002688
	.align	2
$LC7:
	.word	1101004800
	.align	2
$LC8:
	.word	1117782016
	.align	2
$LC9:
	.word	1094713344
	.align	2
$LC10:
	.word	1148846080
	.align	2
$LC11:
	.word	1097859072
	.align	2
$LC12:
	.word	1106771968
	.align	2
$LC13:
	.word	1120403456
	.ident	"GCC: (GNU) 9.2.0"
