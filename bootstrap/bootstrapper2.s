.set noat
.set noreorder
.set gp=64
/* Bootstrapper 2 (new version) */
sw $v0, -0x20($sp) /*v0 contains 0x7FFF so unlikely to be useful*/
/*
Cache time!
Setting the 6 instructions at 800A2630 to:
jal 0x80003440 (osWritebackDCache) = 0C000D10
addiu $a1, $zero, 0x7FFF = 24057FFF
jal 0x800041A0 (osInvalICache) = 0C001068
addiu $a1, $zero, 0x7FFF = 24057FFF (not needed, a1 is not touched by osWritebackDCache)
jal 0x8011D790 (pad 1) = 0C0475E4
nop
*/
lui   $v0,      0x800A

lui   $gp,      0x0C00
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
to address counter 0x801C8000
*/
lui   $gp, 0x8040
lui   $v0, %hi(0x801C8000)
sw    $gp, %lo(0x801C8000)($v0)
/*
Write jr $ra; instruction 0x03E00008 
to seed rotation 0x801FC000
Except currently using 0x801C8004 for "seed rotation"
lui   $gp, 0x03E0
addiu $gp, $gp, 0x0008
Real live seed rotation address
lui   $v0, %hi(0x801FC000)
sw    $gp, %lo(0x801FC000)($v0)
Fake seed rotation address for shortcut:
lui   $v0, %hi(0x801C8004)
sw    $gp, %lo(0x801C8004)($v0)

Write 0002 to 801f73c6 to fix the SRM'd wonder item
and turn off the ACE
(this address has been changed to branch to Link's rotation,
this will restore the original code)
*/
addiu $gp, $zero, 0x0002
lui   $v0, %hi(0x801f73c6)
sh    $gp, %lo(0x801f73c6)($v0)
/* 
Finishing up
Old version from slingshot:
jr $ra
New version from wonder item: jump to the end of a function which
restores the stack correctly (could do the restore manually,
but this saves some instructions)
 */
j 0x80020850
/*This is for both versions*/
lw $v0, -0x20($sp)
