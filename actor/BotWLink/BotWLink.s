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
	.rdata
	.align	2
	.type	limbToPhysMap, @object
	.size	limbToPhysMap, 30
limbToPhysMap:
	.ascii	"\377\377\377\000\001\377\377\377\002\003\377\004\005\377"
	.ascii	"\377\377\377\006\007\010\377\377\011\012\377\013\377\377"
	.ascii	"\377\377"
	.align	2
	.type	tunicBasic, @object
	.size	tunicBasic, 28
tunicBasic:
	.word	1065353216
	.word	1065353216
	.word	1090519040
	.word	1036831949
	.word	1050253722
	.word	1064849900
	.word	1092616192
	.align	2
	.type	bangsBasic, @object
	.size	bangsBasic, 28
bangsBasic:
	.word	992204554
	.word	1137180672
	.word	1077936128
	.word	1067030938
	.word	1065353216
	.word	1060320051
	.word	1069547520
	.align	2
	.type	ponytailBasic, @object
	.size	ponytailBasic, 28
ponytailBasic:
	.word	990057071
	.word	1140457472
	.word	1073741824
	.word	1065353216
	.word	1065353216
	.word	1062836634
	.word	1077936128
	.align	2
	.type	tasselsBasic, @object
	.size	tasselsBasic, 28
tasselsBasic:
	.word	1045220557
	.word	1056964608
	.word	1077936128
	.word	1017370378
	.word	1084227584
	.word	1065185444
	.word	1109393408
	.align	2
	.type	tunicFrontLimits, @object
	.size	tunicFrontLimits, 24
tunicFrontLimits:
	.word	3254779904
	.word	3254779904
	.word	3254779904
	.word	1107296256
	.word	1107296256
	.word	1107296256
	.align	2
	.type	tunicBackLimits, @object
	.size	tunicBackLimits, 24
tunicBackLimits:
	.word	3254779904
	.word	3254779904
	.word	3254779904
	.word	1107296256
	.word	1107296256
	.word	1107296256
	.align	2
	.type	bangsLimits, @object
	.size	bangsLimits, 24
bangsLimits:
	.word	3246391296
	.word	3246391296
	.word	3246391296
	.word	1098907648
	.word	1098907648
	.word	1098907648
	.align	2
	.type	ponytailLimits, @object
	.size	ponytailLimits, 24
ponytailLimits:
	.word	3263168512
	.word	3263168512
	.word	3263168512
	.word	1115684864
	.word	1115684864
	.word	1115684864
	.align	2
	.type	tassels1Limits, @object
	.size	tassels1Limits, 24
tassels1Limits:
	.word	3254779904
	.word	3254779904
	.word	3254779904
	.word	1107296256
	.word	1107296256
	.word	1107296256
	.align	2
	.type	tassels2Limits, @object
	.size	tassels2Limits, 24
tassels2Limits:
	.word	3254779904
	.word	3254779904
	.word	3254779904
	.word	1107296256
	.word	1107296256
	.word	1107296256
	.align	2
	.type	tasselsDouble, @object
	.size	tasselsDouble, 12
tasselsDouble:
	.word	1073741824
	.word	1077936128
	.word	tassels2Limits
	.align	2
	.type	tunicConns, @object
	.size	tunicConns, 64
tunicConns:
	.byte	2
	.space	3
	.word	1036831949
	.byte	4
	.space	3
	.word	1036831949
	.byte	3
	.space	3
	.word	1036831949
	.byte	5
	.space	3
	.word	1036831949
	.byte	0
	.space	3
	.word	1036831949
	.byte	0
	.space	3
	.word	1036831949
	.byte	1
	.space	3
	.word	1036831949
	.byte	1
	.space	3
	.word	1036831949
	.align	2
	.type	physc, @object
	.size	physc, 288
physc:
	.byte	2
	.byte	0
	.space	2
	.word	tunicBasic
	.word	tunicBackLimits
	.word	0
	.word	tunicConns
	.word	tunicConns+8
	.byte	2
	.byte	1
	.space	2
	.word	tunicBasic
	.word	tunicFrontLimits
	.word	0
	.word	tunicConns+16
	.word	0
	.byte	2
	.byte	2
	.space	2
	.word	tunicBasic
	.word	tunicBackLimits
	.word	0
	.word	tunicConns+24
	.word	0
	.byte	2
	.byte	3
	.space	2
	.word	tunicBasic
	.word	tunicFrontLimits
	.word	0
	.word	tunicConns+32
	.word	tunicConns+40
	.byte	2
	.byte	4
	.space	2
	.word	tunicBasic
	.word	tunicBackLimits
	.word	0
	.word	tunicConns+48
	.word	0
	.byte	2
	.byte	5
	.space	2
	.word	tunicBasic
	.word	tunicFrontLimits
	.word	0
	.word	tunicConns+56
	.word	0
	.byte	0
	.byte	1
	.space	2
	.word	bangsBasic
	.word	bangsLimits
	.word	0
	.word	0
	.word	0
	.byte	0
	.byte	2
	.space	2
	.word	bangsBasic
	.word	bangsLimits
	.word	0
	.word	0
	.word	0
	.byte	0
	.byte	3
	.space	2
	.word	bangsBasic
	.word	bangsLimits
	.word	0
	.word	0
	.word	0
	.byte	1
	.byte	0
	.space	2
	.word	tasselsBasic
	.word	tassels1Limits
	.word	tasselsDouble
	.word	0
	.word	0
	.byte	0
	.byte	0
	.space	2
	.word	ponytailBasic
	.word	ponytailLimits
	.word	0
	.word	0
	.word	0
	.byte	1
	.byte	1
	.space	2
	.word	tasselsBasic
	.word	tassels1Limits
	.word	tasselsDouble
	.word	0
	.word	0
	.text
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
	la	$7,BotWLinkMeshIdleAnim
	la	$6,BotWLinkMesh
	move	$4,$17
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

	sw	$0,1048($16)
	addiu	$4,$16,820
	.set	noreorder
	.set	nomacro
	jal	bzero
	li	$5,224			# 0xe0
	.set	macro
	.set	reorder

	lw	$31,44($sp)
	lwc1	$f0,$LC1
	lw	$17,40($sp)
	swc1	$f0,1044($16)
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
	beql	$2,$0,$L35
	lbu	$2,1052($16)
	.set	macro
	.set	reorder

	li	$2,1			# 0x1
	sb	$2,1052($4)
	la	$4,BotWLinkMeshBobokuwaAnim
	jal	Animation_GetLastFrame
	lwc1	$f0,$LC3
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
	lbu	$2,1052($16)
$L35:
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
	sb	$0,1052($16)
	.set	macro
	.set	reorder

$L21:
	sb	$2,1052($16)
$L20:
	.set	noreorder
	.set	nomacro
	jal	SkelAnime_Update
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beql	$2,$0,$L36
	lw	$2,1048($16)
	.set	macro
	.set	reorder

	la	$4,BotWLinkMeshIdleAnim
	jal	Animation_GetLastFrame
	lwc1	$f0,$LC4
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

	lw	$2,1048($16)
$L36:
	li	$3,-4			# 0xfffffffffffffffc
	and	$2,$2,$3
	lw	$3,40($16)
	lwc1	$f2,$LC5
	sw	$3,36($sp)
	lwc1	$f0,36($sp)
	lw	$4,36($16)
	add.s	$f0,$f0,$f2
	lwc1	$f22,$LC8
	lwc1	$f20,$LC9
	sw	$2,1048($16)
	lw	$7,$LC6
	lw	$2,44($16)
	lw	$6,$LC7
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
	bnel	$2,$0,$L37
	lw	$3,40($16)
	.set	macro
	.set	reorder

	lw	$2,1048($16)
	ori	$2,$2,0x1
	sw	$2,1048($16)
	lw	$3,40($16)
$L37:
	lwc1	$f2,$LC10
	sw	$3,36($sp)
	lwc1	$f0,36($sp)
	lw	$4,36($16)
	add.s	$f0,$f0,$f2
	lw	$2,44($16)
	lw	$7,$LC11
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
	bne	$2,$0,$L38
	lw	$31,60($sp)
	.set	macro
	.set	reorder

	lw	$2,1048($16)
	ori	$2,$2,0x2
	sw	$2,1048($16)
	lw	$31,60($sp)
$L38:
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
	.frame	$sp,64,$31		# vars= 0, regs= 7/4, args= 16, gp= 0
	.mask	0x803f0000,-20
	.fmask	0x00f00000,-8
	addiu	$sp,$sp,-64
	sw	$16,20($sp)
	lw	$16,84($sp)
	li	$2,1			# 0x1
	lw	$3,1048($16)
	sw	$18,28($sp)
	andi	$4,$3,0x1
	lw	$18,80($sp)
	sw	$31,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$17,24($sp)
	sdc1	$f22,56($sp)
	sdc1	$f20,48($sp)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L40
	sll	$2,$2,$5
	.set	macro
	.set	reorder

	andi	$4,$2,0x60c0
	.set	noreorder
	.set	nomacro
	bnel	$4,$0,$L43
	sw	$0,0($6)
	.set	macro
	.set	reorder

$L40:
	andi	$3,$3,0x2
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L42
	andi	$2,$2,0x7ff8
	.set	macro
	.set	reorder

	beq	$2,$0,$L42
	.set	noreorder
	.set	nomacro
	b	$L43
	sw	$0,0($6)
	.set	macro
	.set	reorder

$L42:
	la	$2,limbToPhysMap
	addu	$5,$2,$5
	lb	$3,0($5)
	.set	noreorder
	.set	nomacro
	bltz	$3,$L43
	sll	$2,$3,1
	.set	macro
	.set	reorder

	addu	$2,$2,$3
	sll	$3,$2,3
	la	$2,physc
	addu	$2,$2,$3
	lbu	$21,0($2)
	lbu	$17,1($2)
	lw	$20,4($2)
	.set	noreorder
	.set	nomacro
	jal	Rand_ZeroOne
	lw	$19,8($2)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	Rand_ZeroOne
	mov.s	$f22,$f0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	Rand_ZeroOne
	mov.s	$f20,$f0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$21,$0,$L74
	lw	$31,44($sp)
	.set	macro
	.set	reorder

	sll	$3,$17,1
	addu	$2,$3,$17
	lwc1	$f4,24($20)
	lwc1	$f16,1044($16)
	sll	$2,$2,3
	addu	$2,$16,$2
	lwc1	$f2,12($20)
	mul.s	$f16,$f16,$f4
	nop
	lwc1	$f18,$LC12
	lwc1	$f8,820($2)
	lwc1	$f10,824($2)
	lwc1	$f6,828($2)
	mul.s	$f12,$f2,$f10
	nop
	mtc1	$0,$f14
	mul.s	$f4,$f2,$f8
	nop
	sub.s	$f22,$f22,$f18
	sub.s	$f0,$f0,$f18
	mul.s	$f2,$f2,$f6
	nop
	sub.s	$f20,$f20,$f18
	lwc1	$f18,20($20)
	mul.s	$f22,$f22,$f16
	nop
	mul.s	$f0,$f0,$f16
	nop
	mul.s	$f20,$f20,$f16
	nop
	lwc1	$f16,832($2)
	sub.s	$f2,$f14,$f2
	sub.s	$f4,$f14,$f4
	sub.s	$f12,$f14,$f12
	add.s	$f4,$f4,$f22
	add.s	$f0,$f2,$f0
	lwc1	$f2,840($2)
	mul.s	$f22,$f16,$f18
	nop
	lwc1	$f16,836($2)
	mul.s	$f2,$f2,$f18
	nop
	add.s	$f12,$f12,$f20
	mul.s	$f20,$f16,$f18
	nop
	lwc1	$f18,4($20)
	lwc1	$f16,$LC13
	mul.s	$f0,$f0,$f18
	nop
	mul.s	$f4,$f4,$f18
	nop
	mul.s	$f12,$f12,$f18
	nop
	mul.s	$f0,$f0,$f16
	nop
	mul.s	$f4,$f4,$f16
	nop
	mul.s	$f12,$f12,$f16
	nop
	add.s	$f2,$f0,$f2
	add.s	$f4,$f4,$f22
	swc1	$f2,840($2)
	add.s	$f12,$f12,$f20
	swc1	$f4,832($2)
	mul.s	$f2,$f2,$f16
	nop
	swc1	$f12,836($2)
	mul.s	$f0,$f4,$f16
	nop
	mul.s	$f12,$f12,$f16
	nop
	add.s	$f2,$f2,$f6
	add.s	$f0,$f0,$f8
	swc1	$f2,828($2)
	lwc1	$f2,0($19)
	add.s	$f10,$f12,$f10
	swc1	$f0,820($2)
	c.lt.s	$f0,$f2
	#nop
	.set	noreorder
	.set	nomacro
	bc1f	$L46
	swc1	$f10,824($2)
	.set	macro
	.set	reorder

	swc1	$f2,820($2)
	swc1	$f14,832($2)
$L46:
	addu	$2,$3,$17
	sll	$2,$2,3
	addu	$2,$16,$2
	lwc1	$f0,12($19)
	lwc1	$f2,820($2)
	c.lt.s	$f0,$f2
	#nop
	.set	noreorder
	.set	nomacro
	bc1fl	$L75
	addu	$2,$3,$17
	.set	macro
	.set	reorder

	swc1	$f0,820($2)
	sw	$0,832($2)
	addu	$2,$3,$17
$L75:
	sll	$2,$2,3
	addu	$2,$16,$2
	lwc1	$f0,4($19)
	lwc1	$f2,824($2)
	c.lt.s	$f2,$f0
	#nop
	.set	noreorder
	.set	nomacro
	bc1fl	$L76
	addu	$2,$3,$17
	.set	macro
	.set	reorder

	swc1	$f0,824($2)
	sw	$0,836($2)
	addu	$2,$3,$17
$L76:
	sll	$2,$2,3
	addu	$2,$16,$2
	lwc1	$f0,16($19)
	lwc1	$f2,824($2)
	c.lt.s	$f0,$f2
	#nop
	.set	noreorder
	.set	nomacro
	bc1fl	$L77
	addu	$2,$3,$17
	.set	macro
	.set	reorder

	swc1	$f0,824($2)
	sw	$0,836($2)
	addu	$2,$3,$17
$L77:
	sll	$2,$2,3
	addu	$2,$16,$2
	lwc1	$f0,8($19)
	lwc1	$f2,828($2)
	c.lt.s	$f2,$f0
	#nop
	.set	noreorder
	.set	nomacro
	bc1fl	$L78
	addu	$2,$3,$17
	.set	macro
	.set	reorder

	swc1	$f0,828($2)
	sw	$0,840($2)
	addu	$2,$3,$17
$L78:
	sll	$2,$2,3
	addu	$2,$16,$2
	lwc1	$f0,20($19)
	lwc1	$f2,828($2)
	c.lt.s	$f0,$f2
	#nop
	.set	noreorder
	.set	nomacro
	bc1fl	$L79
	lh	$2,0($18)
	.set	macro
	.set	reorder

	swc1	$f0,828($2)
	sw	$0,840($2)
	lh	$2,0($18)
$L79:
	addu	$3,$3,$17
	mtc1	$2,$f0
	sll	$3,$3,3
	addu	$16,$16,$3
	lwc1	$f4,$LC14
	cvt.s.w	$f2,$f0
	lwc1	$f0,820($16)
	lh	$2,4($18)
	mul.s	$f0,$f0,$f4
	nop
	add.s	$f2,$f2,$f0
	trunc.w.s $f0,$f2
	mfc1	$3,$f0
	#nop
	sh	$3,0($18)
	lh	$3,2($18)
	mtc1	$3,$f0
	#nop
	cvt.s.w	$f2,$f0
	lwc1	$f0,824($16)
	mul.s	$f0,$f0,$f4
	nop
	add.s	$f2,$f2,$f0
	trunc.w.s $f0,$f2
	mfc1	$3,$f0
	lwc1	$f0,828($16)
	lwc1	$f2,16($20)
	mul.s	$f0,$f0,$f4
	nop
	sh	$3,2($18)
	mul.s	$f0,$f0,$f2
	nop
	mtc1	$2,$f2
	#nop
	cvt.s.w	$f2,$f2
	add.s	$f0,$f0,$f2
	trunc.w.s $f0,$f0
	mfc1	$2,$f0
	#nop
	sh	$2,4($18)
$L43:
	lw	$31,44($sp)
$L74:
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	ldc1	$f22,56($sp)
	ldc1	$f20,48($sp)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	jr	$31
	addiu	$sp,$sp,64
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
	.word	1056
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
$LC3:
	.word	3229614080
	.align	2
$LC4:
	.word	3238002688
	.align	2
$LC5:
	.word	1101004800
	.align	2
$LC6:
	.word	1117782016
	.align	2
$LC7:
	.word	1094713344
	.align	2
$LC8:
	.word	1148846080
	.align	2
$LC9:
	.word	1097859072
	.align	2
$LC10:
	.word	1106771968
	.align	2
$LC11:
	.word	1120403456
	.align	2
$LC12:
	.word	1056964608
	.align	2
$LC13:
	.word	1028443341
	.align	2
$LC14:
	.word	1132462080
	.ident	"GCC: (GNU) 9.2.0"
