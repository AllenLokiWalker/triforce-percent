#include <z64ovl/oot/u10.h>

extern void DmaMgr_Init();
extern void Main(void*);
extern u32 osGetMemSize(void);

extern u32 statics_START;

typedef struct {
   void* vrom;
   void* vram;
   u32 size;
} DmaRequest;

#define _codeSegmentStart (void*)0x800110A0
#define _codeSegmentRomStart (void*)0x00A87000
#define _codeSegmentRomEnd (void*)0x00B8AD30
#define _codeSegmentBssStart (void*)0x80114DD0
#define _codeSegmentBssEnd (void*)0x8012BE30

// RAM: 0x800005A0, ROM: 0x000011A0
void func_800005A0(void* arg0) {
    static DmaRequest rhstaticsFile = { (void*)0xDEADBEEF, &statics_START, 0x04206969 };
    
    DmaMgr_Init();
    load_data_from_rom(_codeSegmentStart, _codeSegmentRomStart, _codeSegmentRomEnd - _codeSegmentRomStart, "");
    z_bzero(_codeSegmentBssStart, _codeSegmentBssEnd - _codeSegmentBssStart);
    /*
    if (osGetMemSize() < 0x00800000) { 
        for (;;) {}
    }
    */
    z_file_load(&rhstaticsFile);
    /*z_bzero(&rhstaticsFile, 12);*/
    Main(arg0);
}
