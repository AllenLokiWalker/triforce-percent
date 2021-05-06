.set noat
.set noreorder
.set gp=64
/* Bootstrapper 2 (new version) */
sw $v0, -0x20($sp) /*v0 contains 0x7FFF so unlikely to be useful*/

/* Detect whether running from the ACE context or the padmgr context
If padmgr, need normal return, not special stack restore
(but don't need to actually execute the rest of the bootstrapper)
During ACE context, s1 is global context 0x801C84A0*/
lui   $v0,      %hi(0x801C84A0)
addiu $v0, $v0, %lo(0x801C84A0)
beq   $v0, $s1, in_ace_context
lui   $gp,      0x0C00 /* First instruction of Cache Time below */

/* If not in ACE context, return */
jr $ra
lw $v0, -0x20($sp)

in_ace_context:
/*
Cache Time!
Setting the 6 instructions at 800A2630 to:
jal 0x80003440 (osWritebackDCache) = 0C000D10
addiu $a1, $zero, 0x7FFF = 24057FFF
jal 0x800041A0 (osInvalICache) = 0C001068
addiu $a1, $zero, 0x7FFF = 24057FFF (not needed, a1 is not touched by osWritebackDCache)
jal 0x8011D790 (pad 1) = 0C0475E4
nop
*/
lui   $v0,      0x800A

/*lui   $gp,      0x0C00 -- in branch delay slot above*/
addiu $gp, $gp, 0x0D10
sw    $gp,      0x2630($v0)
addiu $gp, $gp, (0x1068 - 0x0D10)
sw    $gp,      0x2638($v0)

lui   $gp,      0x2405
addiu $gp, $gp, 0x7FFF
sw    $gp,      0x2634($v0)
sw    $gp,      0x263C($v0)

lui   $gp,      0x0C04
addiu $gp, $gp, 0x75E4
sw    $gp,      0x2640($v0)
sw    $zero,    0x2644($v0)

/*
Write 0x80400000 (address of start of Kargarocs payload--to jal here, instruction 0C100000)
to address counter 0x801C800C
*/
lui   $gp, 0x8040
lui   $v0, %hi(0x801C800C)
sw    $gp, %lo(0x801C800C)($v0)

/* Stop ACE and return */

/* Old shortcut via fake seed rotation 0x801C8004:
Write jr $ra; instruction 0x03E00008
lui   $gp, 0x03E0
addiu $gp, $gp, 0x0008
lui   $v0, %hi(0x801C8004)
sw    $gp, %lo(0x801C8004)($v0)
Normal return (got here via jal)
jr    $ra
lw    $v0, -0x20($sp) */

/* Old real live version via seed rotation 0x801FC000:
Write jr $ra; instruction 0x03E00008
lui   $gp, 0x03E0
addiu $gp, $gp, 0x0008
lui   $v0, %hi(0x801FC000)
sw    $gp, %lo(0x801FC000)($v0) 
Normal return (got here via jal)
jr    $ra
lw    $v0, -0x20($sp) */

/* New shortcut:
Write 0xA5 to global->lighting.pad_00_[1] to signal ACE done */
addiu $gp, $zero, 0x00A5
lui   $v0, %hi(0x801C84A0+0x7A8+0xF)
sb    $gp, %lo(0x801C84A0+0x7A8+0xF)($v0) 
/* Normal return (got here via jal) */
jr    $ra
lw    $v0, -0x20($sp)

/* New real live version via wonder item:
Write 0002 to 801f73c6. This was changed via SRM to a branch
to Link's rotation, this restores the original code.
addiu $gp, $zero, 0x0002
lui   $v0, %hi(0x801f73c6)
sh    $gp, %lo(0x801f73c6)($v0) 
Jump to the end of a function which restores the stack correctly
(could do the restore manually, but this saves some instructions)
j 0x80020850
lw $v0, -0x20($sp) */
