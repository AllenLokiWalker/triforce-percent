#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__

//extern void _memcpy(void* dest, const void* src, u32 size);
extern char *Debugger_GetNextMessageBuffer(uint8_t timeout);
extern void Debugger_ShowMessage(uint8_t timeout, const char *msg);

#define Debugger_Printf(format...) \
    z_sprintf(Debugger_GetNextMessageBuffer(255), format)

#endif //__DEBUGGER_H__
