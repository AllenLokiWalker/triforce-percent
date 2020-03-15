
gvars = 0x80412000;
padmgr = 0x8011D500;

DmaMgr_SendRequest0 = 0x80001AA0;
osContStartReadData = 0x800D0160;
osRecvMesg = 0x80002030;
osContGetReadData = 0x800D01E4;

/* for disabling and re-enabling interrupts in critical code */
__osDisableInt = 0x80005130;
__osRestoreInt = 0x800051A0;

/* cache clearing
 0x80003440. addr is weird, it's a cache line address not a normal address.
 Just set addr to 0 and size to >= 0x2000 to write back the whole cache. */
osWritebackDCache = 0x80003440;

/* 0x800041A0. Same deal with addr. Set addr to 0 and size to >= 0x4000 to invalidate the whole cache. */
osInvalICache = 0x800041A0;



