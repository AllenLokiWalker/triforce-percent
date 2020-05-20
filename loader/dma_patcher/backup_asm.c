//This is working
asm(".set noat\n .set noreorder\n"
"addiu   $sp, $sp, 0xFFC0             \n"//## $sp = FFFFFFC0
"lui     $a2, 0x8001                  \n"//
"addiu   $a2, $a2, 0xB140             \n"//## $a2 = 8000B140 = gDmaDataTable
"sw      $ra, 0x001C($sp)             \n"//
"sw      $s0, 0x0018($sp)             \n"//
"lw      $t6, 0x0004($a0)             \n"//## $t6 = req->dramAddr
"lw      $s0, 0x0000($a0)             \n"//## $s0 = req->vromAddr
"lw      $t8, 0x0004($a2)             \n"//## iter->vromEnd
"sw      $t6, 0x0038($sp)             \n"//## 0x38 = dramAddr
"lw      $t7, 0x0008($a0)             \n"//## $t7 = req->size
"or      $a1, $zero, $zero            \n"//## $a1 = found = 0
"or      $v1, $zero, $zero            \n"//## v1 = 00000000
"or      $v0, $a2, $zero              \n"//## v0 = 8000B140 = iter
"beq     $t8, $zero, lbl_80000C58     \n"//## if(gDmaDataTable->vromEnd == 0) goto endloop
"sw      $t7, 0x0034($sp)             \n"//## 0x34 = size
"lw      $a3, 0x0000($v0)             \n"//## $a3 = iter->vromStart
"lbl_80000B4C:                            \n"//
"sltu    $at, $s0, $a3                \n"//## if(vromAddr < iter->vromStart)
"bne     $at, $zero, lbl_80000C3C     \n"//##    branch
"nop                                  \n"//
"lw      $a0, 0x0004($v0)             \n"//## $a0 = iter->vromEnd
"sltu    $at, $s0, $a0                \n"//## if(vromAddr >= iter->vromEnd)
"beq     $at, $zero, lbl_80000C3C     \n"//##    branch
"nop                                  \n"//
"lw      $a1, 0x000C($v0)             \n"//## $a1 = iter->romEnd
"lw      $t9, 0x0034($sp)             \n"//## $t8 = size
"bne     $a1, $zero, lbl_80000BBC     \n"//## if(iter->romEnd != 0) goto compressed
"addu    $t0, $s0, $t9                \n"//## $t0 = req->vromAddr + size
"sltu    $at, $a0, $t0                \n"//## if(iter->vromEnd >= req->vromAddr + size)
"beq     $at, $zero, lbl_80000B9C     \n"//##   goto no_error_uncompressed
"lui     $a0, 0x8000                  \n"//
"addiu   $a0, $a0, 0x6594             \n"//## $a0 = 80006594 #pointer to error string
"addiu   $a1, $zero, 0x023F           \n"//## $a1 = 0000023F #line number
"nop                                  \n"//"jal     DmaMgr_Error                 \n"
"sw      $v0, 0x0024($sp)             \n"//
"lw      $v0, 0x0024($sp)             \n"//## restore v0 == iter
"lw      $a3, 0x0000($v0)             \n"//## restore $a3 = iter->vromStart
"lbl_80000B9C:                            \n"//## no_error_uncompressed:
"lw      $t1, 0x0008($v0)             \n"//## $t1 = iter->romStart
"lw      $a1, 0x0038($sp)             \n"//## $a1 = dramAddr
"lw      $a2, 0x0034($sp)             \n"//## $a2 = size
"addu    $t2, $t1, $s0                \n"//## $t2 = iter->romStart + req->vromAddr
"jal     DmaMgr_DMARomToRam           \n"//## DmaMgr_DMARomToRam(iter->romStart + (vrom - iter->vromStart), ram, size);
"subu    $a0, $t2, $a3                \n"//## $a0 = iter->romStart + req->vromAddr - iter->vromStart
"beq     $zero, $zero, lbl_80000C58   \n"//## break, goto endloop
"addiu   $a1, $zero, 0x0001           \n"//## $a1 = found = 1

"lbl_80000BBC:                            \n"//## compressed:
"lw      $v1, 0x0008($v0)             \n"//## 00000008
"subu    $t3, $a1, $v1                \n"//
"sw      $t3, 0x002C($sp)             \n"//
"beq     $s0, $a3, lbl_80000BF0       \n"//
"sw      $v1, 0x0030($sp)             \n"//
"lui     $a0, 0x8000                  \n"//
"addiu   $a0, $a0, 0x65A4             \n"//## $a0 = 800065A4 #pointer to error string
"addiu   $a1, $zero, 0x0253           \n"//## $a1 = 00000253 #line number
"nop                                  \n"//"jal     DmaMgr_Error                 \n"
"sw      $v0, 0x0024($sp)             \n"//
"lw      $v0, 0x0024($sp)             \n"//
"lw      $a3, 0x0000($v0)             \n"//## 00000000
"lw      $a0, 0x0004($v0)             \n"//## 00000004
"lbl_80000BF0:                            \n"//
"lw      $t4, 0x0034($sp)             \n"//
"subu    $t5, $a0, $a3                \n"//
"lui     $a0, 0x8000                  \n"//## $a0 = 80000000
"beq     $t4, $t5, lbl_80000C0C       \n"//
"addiu   $a0, $a0, 0x65B4             \n"//## $a0 = 800065B4
"nop                                  \n"//"jal     DmaMgr_Error                 \n"
"addiu   $a1, $zero, 0x0259           \n"//## $a1 = 00000259
"lbl_80000C0C:                            \n"//
"or      $a0, $zero, $zero            \n"//## $a0 = 00000000
"jal     osSetThreadPri               \n"//## osSetThreadPri
"addiu   $a1, $zero, 0x000A           \n"//## $a1 = 0000000A
"lw      $a0, 0x0030($sp)             \n"//
"lw      $a1, 0x0038($sp)             \n"//
"jal     Yaz0_Decompress              \n"//## Yaz0_Decompress(romStart, ram, romSize);
"lw      $a2, 0x002C($sp)             \n"//
"or      $a0, $zero, $zero            \n"//## $a0 = 00000000
"jal     osSetThreadPri               \n"//## osSetThreadPri
"addiu   $a1, $zero, 0x0010           \n"//## $a1 = 00000010
"beq     $zero, $zero, lbl_80000C58   \n"//
"addiu   $a1, $zero, 0x0001           \n"//## $a1 = 00000001
"lbl_80000C3C:                            \n"//
"beql    $v1, $zero, lbl_80000C4C     \n"//
"lw      $t6, 0x0014($v0)             \n"//## 00000014
"addiu   $v1, $v1, 0x0004             \n"//## v1 = 00000004
"lw      $t6, 0x0014($v0)             \n"//## 00000014
"lbl_80000C4C:                            \n"//
"addiu   $v0, $v0, 0x0010             \n"//## v0 = 00000010
"bnel    $t6, $zero, lbl_80000B4C     \n"//
"lw      $a3, 0x0000($v0)             \n"//## 00000010

"lbl_80000C58:                            \n"//## endloop:
"bne     $a1, $zero, lbl_80000C94     \n"//
"lui     $t7, 0x8000                  \n"//## $t7 = 80000000
"lw      $t7, 0x6278($t7)             \n"//## 80006278
"or      $a0, $s0, $zero              \n"//## $a0 = 00000000
"lw      $a1, 0x0038($sp)             \n"//
"beq     $t7, $zero, lbl_80000C8C     \n"//
"nop                                  \n"//
"lui     $a0, 0x8000                  \n"//
"addiu   $a0, $a0, 0x65C4             \n"//## $a0 = 800065C4 #pointer to error string
"nop                                  \n"//"jal     DmaMgr_Error                 \n"
"addiu   $a1, $zero, 0x026D           \n"//## $a1 = 0000026D #line number
"beq     $zero, $zero, lbl_80000C98   \n"//
"lw      $ra, 0x001C($sp)             \n"//
"lbl_80000C8C:                            \n"//
"jal     DmaMgr_DMARomToRam           \n"//## DmaMgr_DMARomToRam(vrom, ram, size);
"lw      $a2, 0x0034($sp)             \n"//
"lbl_80000C94:                            \n"//
"lw      $ra, 0x001C($sp)             \n"//
"lbl_80000C98:                            \n"//
"lw      $s0, 0x0018($sp)             \n"//
"addiu   $sp, $sp, 0x0040             \n"//## $sp = 00000000
"jr      $ra                          \n"//
"nop                                  \n"//
".set at");
