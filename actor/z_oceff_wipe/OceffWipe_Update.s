.set noat
.set noreorder
.set gp=64

/* 
Have 24 instructions.
a0 = this, a1 = globalCtx
Have to
if (this->counter < 100) {
    this->counter++;
} else {
    Actor_Kill(&this->actor);
}
Actor_Kill = 80020EB4
*/

/* Check and increment counter */
lh    $t0, 0x013C($a0) /* this->counter */
slti  $at, $t0, 100
beq   $at, $zero, lbl_endcount
lh    $t4, 0x013E($a0) /* unused halfword after counter */
addiu $t0, $t0, 0x0001
jr    $ra
sh    $t0, 0x013C($a0)

lbl_endcount:
/* Check if Zelda's Lullaby or Song of Time */
lh    $t3, 0x001C($a0) /* this->actor.params/variable */
beq   $t3, $zero, lbl_kill /* Zelda's is 0 */

/* Set save context Sun's Song flag */
addiu $t1, $zero, 0x0001
lui   $v0, %hi(0x8011A5D0)
addiu $v0, $v0, %lo(0x8011A5D0)
sh    $t1, 0x1422($v0)

/* Set Link's age modifier for next scene */
lw    $t2, 0x4($v0) /* current age */
xor   $t2, $t2, $t1 /* invert */
lui   $v0, %hi(0x801DA288)
sb    $t2, %lo(0x801DA288)($v0)

lbl_kill:
/* Tail call optimization--don't need stack */
j     0x80020EB4 /* Kill actor */
nop
