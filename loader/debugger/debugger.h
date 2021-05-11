#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__

extern s32 _sprintf(char* dest, const char* format, ...); //800CE7B4

//extern void _memcpy(void* dest, const void* src, u32 size);
extern char *Debugger_GetNextMessageBuffer(u8 timeout);
extern void Debugger_ShowMessage(u8 timeout, const char *msg);

#define Debugger_Printf(format...) \
    _sprintf(Debugger_GetNextMessageBuffer(255), format)

#endif //__DEBUGGER_H__
