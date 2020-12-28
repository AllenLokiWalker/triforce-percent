.set noat
.set noreorder
.set gp=64

/* 
Have 24 instructions.
a0 = this, a1 = globalCtx
Have to
if (this->counter < 50) {
    this->counter++;
} else {
    Actor_Kill(&this->actor);
}
Actor_Kill = 80020EB4
*/

/* Init */
addiu $sp, $sp, 0xFFFC
sw    $ra, 0x0000($sp)

/* Check and increment counter */
lh    $t0, 0x013C($a0)
slti  $at, $t0, 50
bne   $at, $zero, lbl_inc
addiu $t0, $t0, 0x0001

/* Set save context Sun's Song flag */
addiu $t1, $zero, 0x0001
lui   $v0, %hi(0x8011A5D0)
addiu $v0, $v0, %lo(0x8011A5D0)
sh    $t1, 0x1422($v0)

/* Set Link's age modifier for next scene */
lw    $t2, 0x4($v0)
xor   $t2, $t2, $t1 /* invert age */
lui   $v0, %hi(0x801DA288)
jal   0x80020EB4 /* Kill actor */
sb    $t2, %lo(0x801DA288)($v0)

beq   $zero, $zero, lbl_ret
nop

lbl_inc:
sh    $t0, 0x013C($a0)

/* Done*/
lbl_ret:
lw    $ra, 0x0000($sp)
jr    $ra
addiu $sp, $sp, 0x0004
