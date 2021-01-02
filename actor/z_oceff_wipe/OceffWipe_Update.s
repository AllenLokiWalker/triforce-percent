.set noat
.set noreorder
.set gp=64

/* 
Have 24 instructions.
a0 = this, a1 = globalCtx
*/

/* Check and increment counter */
lh    $t0, 0x013C($a0) /* this->counter */
slti  $at, $t0, 100
beq   $at, $zero, lbl_endcount
addiu $t0, $t0, 0x0001
jr    $ra
sh    $t0, 0x013C($a0)

lbl_endcount:
lui   $v0, %hi(0x8011A5D0) /* save context */
/* global ctx 0x801C84A0 already in a1, but we need to access more than 0x7FFF
after it, so have to reload */
lui   $v1, %hi(0x801C84A0+0x11DE8) /* lowest value we need, start there */

/* globalCtx->linkAgeOnLoad [0x11DE8, u8] = !gSaveContext.linkAge [4, s32]; */
lw    $t2, %lo(0x8011A5D0+0x4)($v0)

/* Check if Zelda's Lullaby or Song of Time */
lh    $t3, 0x001C($a0) /* this->actor.params/variable */
beq   $t3, $zero, lbl_kill /* Zelda's is 0 */

/*
//Not sure if needed:
globalCtx->unk_11DE9 = 1;
gSaveContext.nextDayTime [0x1416, u16] = gSaveContext.dayTime [0x000C, u16];
func_800F6964_debug(30); //fade out music?
gSaveContext.seqIndex [0x13E0, u8] = 0xFF;
gSaveContext.nightSeqIndex [0x13E1, u8] = 0xFF;
*/

/* gSaveContext.respawnFlag [0x1364, s32] = -2; */
addiu $t4, $zero, -2
sw    $t4, %lo(0x8011A5D0+0x1364)($v0)

/* globalCtx->sceneLoadFlag [0x11E15, s8] = 0x14; */
addiu $t5, $zero, 0x14
sb    $t5, %lo(0x801C84A0+0x11E15)($v1)

/* globalCtx->fadeTransition [0x11E5E, u8] = 0x2C; */
addiu $t6, $zero, 0x2C
sb    $t6, %lo(0x801C84A0+0x11E5E)($v1)

/* gSaveContext.nextTransition [0x141D, u8] = 5; */
addiu $t6, $zero, 5
sb    $t6, %lo(0x8011A5D0+0x141D)($v0)

/* globalCtx->nextEntranceIndex [0x11E1A, s16] = gSaveContext.entranceIndex [0, s32]; */
lw    $t7, %lo(0x8011A5D0+0x0)($v0)
sh    $t7, %lo(0x801C84A0+0x11E1A)($v1)

/* Invert Link's age */
xori  $t2, $t2, 0x0001

lbl_kill:
/* Tail call optimization--don't need stack */
j     0x80020EB4 /* Kill actor, arg a0 (this) */
sb    $t2, %lo(0x801C84A0+0x11DE8)($v1) /* Store Link age, not inverted if Zelda's */




/* Set save context Sun's Song flag 
addiu $t1, $zero, 0x0001
lui   $v0, %hi(0x8011A5D0)
addiu $v0, $v0, %lo(0x8011A5D0)
sh    $t1, 0x1422($v0)


lh    $t4, 0x013E($a0) // unused halfword after counter
*/
