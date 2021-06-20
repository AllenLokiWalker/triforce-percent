# 1 "boot_load_statics.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "boot_load_statics.c"
# 1 "/opt/n64/mips64/include/z64ovl/oot/u10.h" 1 3







# 1 "/opt/n64/mips64/include/z64ovl/h/mips.h" 1 3







# 1 "/opt/n64/mips64/include/z64ovl/stdint.h" 1 3
# 9 "/opt/n64/mips64/include/z64ovl/stdint.h" 3

# 9 "/opt/n64/mips64/include/z64ovl/stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef signed int intptr_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned int uintptr_t;

typedef unsigned int size_t;
# 9 "/opt/n64/mips64/include/z64ovl/h/mips.h" 2 3
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef float f32;
typedef double f64;
# 467 "/opt/n64/mips64/include/z64ovl/h/mips.h" 3
enum
{
    MIPS_R0,
    MIPS_AT,
    MIPS_V0,
    MIPS_V1,
    MIPS_A0,
    MIPS_A1,
    MIPS_A2,
    MIPS_A3,
    MIPS_T0,
    MIPS_T1,
    MIPS_T2,
    MIPS_T3,
    MIPS_T4,
    MIPS_T5,
    MIPS_T6,
    MIPS_T7,
    MIPS_S0,
    MIPS_S1,
    MIPS_S2,
    MIPS_S3,
    MIPS_S4,
    MIPS_S5,
    MIPS_S6,
    MIPS_S7,
    MIPS_T8,
    MIPS_T9,
    MIPS_K0,
    MIPS_K1,
    MIPS_GP,
    MIPS_SP,
    MIPS_FP,
    MIPS_RA
};
# 9 "/opt/n64/mips64/include/z64ovl/oot/u10.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/oot/types.h" 1 3



# 1 "/opt/n64/mips64/include/z64ovl/stdint.h" 1 3
# 5 "/opt/n64/mips64/include/z64ovl/oot/types.h" 2 3

# 1 "/opt/n64/mips64/include/z64ovl/h/n64.h" 1 3







# 1 "/opt/n64/mips64/include/z64ovl/n64/gbi.h" 1 3
# 11 "/opt/n64/mips64/include/z64ovl/n64/gbi.h" 3
# 1 "/opt/n64/mips64/include/z64ovl/stdint.h" 1 3
# 12 "/opt/n64/mips64/include/z64ovl/n64/gbi.h" 2 3
# 2217 "/opt/n64/mips64/include/z64ovl/n64/gbi.h" 3
typedef uint8_t qu08_t;
typedef uint16_t qu016_t;
typedef int16_t qs48_t;
typedef int16_t qs510_t;
typedef uint16_t qu510_t;
typedef int16_t qs102_t;
typedef uint16_t qu102_t;
typedef int16_t qs105_t;
typedef uint16_t qu105_t;
typedef int16_t qs132_t;
typedef int16_t qs142_t;
typedef int32_t qs1516_t;
typedef int32_t qs1616_t;
typedef int32_t qs205_t;

typedef uint16_t g_bglt_t;
typedef uint8_t g_ifmt_t;
typedef uint8_t g_isiz_t;
typedef uint16_t g_bgf_t;
typedef uint8_t g_objf_t;
typedef uint32_t g_objlt_t;

typedef struct
{
  _Alignas(8)
  uint32_t hi;
  uint32_t lo;
} Gfx;

typedef struct
{
  int32_t x1;
  int32_t y1;
  int32_t x2;
  int32_t y2;
} Hilite_t;
typedef union
{
  _Alignas(8)
  Hilite_t h;
} Hilite;

typedef int32_t Mtx_t[4][4];
typedef union
{
  _Alignas(8)
  Mtx_t m;
  int32_t l[16];
  struct
  {
    int16_t i[16];
    uint16_t f[16];
  };
} Mtx;

typedef struct
{
  uint8_t col[3];
  char pad1;
  uint8_t colc[3];
  char pad2;
  int8_t dir[3];
  char pad3;
} Light_t;
typedef union
{
  _Alignas(8)
  Light_t l;
} Light;

typedef struct
{
  Light l[2];
} LookAt;

typedef struct
{
  uint8_t col[3];
  char pad1;
  uint8_t colc[3];
  char pad2;
} Ambient_t;
typedef union
{
  _Alignas(8)
  Ambient_t l;
} Ambient;

typedef struct
{
  Ambient a;
  Light l[1];
} Lights0, Lights1;
typedef struct
{
  Ambient a;
  Light l[2];
} Lights2;
typedef struct
{
  Ambient a;
  Light l[3];
} Lights3;
typedef struct
{
  Ambient a;
  Light l[4];
} Lights4;
typedef struct
{
  Ambient a;
  Light l[5];
} Lights5;
typedef struct
{
  Ambient a;
  Light l[6];
} Lights6;
typedef struct
{
  Ambient a;
  Light l[7];
} Lightsn, Lights7;

typedef struct
{
  int16_t ob[3];
  uint16_t flag;
  qs105_t tc[2];
  uint8_t cn[4];
} Vtx_t;
typedef struct
{
  int16_t ob[3];
  uint16_t flag;
  qs105_t tc[2];
  int8_t n[3];
  uint8_t a;
} Vtx_tn;
typedef union
{
  _Alignas(8)
  Vtx_t v;
  Vtx_tn n;
} Vtx;

typedef struct
{
  qs142_t vscale[4];
  qs142_t vtrans[4];
} Vp_t;
typedef union
{
  _Alignas(8)
  Vp_t vp;
} Vp;

typedef struct
{
  qs1516_t A;
  qs1516_t B;
  qs1516_t C;
  qs1516_t D;
  qs102_t X;
  qs102_t Y;
  qu510_t BaseScaleX;
  qu510_t BaseScaleY;
} uObjMtx_t;
typedef union
{
  _Alignas(8)
  uObjMtx_t m;
} uObjMtx;

typedef struct
{
  qs102_t X;
  qs102_t Y;
  qu510_t BaseScaleX;
  qu510_t BaseScaleY;
} uObjSubMtx_t;
typedef union
{
  _Alignas(8)
  uObjSubMtx_t m;
} uObjSubMtx;

typedef struct
{
  qu105_t imageX;
  qu102_t imageW;
  qs102_t frameX;
  qu102_t frameW;
  qu105_t imageY;
  qu102_t imageH;
  qs102_t frameY;
  qu102_t frameH;
  uint64_t *imagePtr;
  g_bglt_t imageLoad;
  g_ifmt_t imageFmt;
  g_isiz_t imageSiz;
  uint16_t imagePal;
  g_bgf_t imageFlip;
  uint16_t tmemW;
  qs132_t tmemH;
  uint16_t tmemLoadSH;
  uint16_t tmemLoadTH;
  uint16_t tmemSizeW;
  uint16_t tmemSize;
} uObjBg_t;
typedef struct
{
  qu105_t imageX;
  qu102_t imageW;
  qs102_t frameX;
  qu102_t frameW;
  qu105_t imageY;
  qu102_t imageH;
  qs102_t frameY;
  qu102_t frameH;
  uint64_t *imagePtr;
  g_bglt_t imageLoad;
  g_ifmt_t imageFmt;
  g_isiz_t imageSiz;
  uint16_t imagePal;
  g_bgf_t imageFlip;
  qu510_t scaleW;
  qu510_t scaleH;
  qs205_t imageYorig;
  char padding[4];
} uObjScaleBg_t;
typedef union
{
  _Alignas(8)
  uObjBg_t b;
  uObjScaleBg_t s;
} uObjBg;

typedef struct
{
  qs102_t objX;
  qu510_t scaleW;
  qu105_t imageW;
  uint16_t paddingX;
  qs102_t objY;
  qu510_t scaleH;
  qu105_t imageH;
  uint16_t paddingY;
  uint16_t imageStride;
  uint16_t imageAdrs;
  g_ifmt_t imageFmt;
  g_isiz_t imageSiz;
  uint16_t imagePal;
  g_objf_t imageFlags;
} uObjSprite_t;
typedef union
{
  _Alignas(8)
  uObjSprite_t s;
} uObjSprite;

typedef struct
{
  g_objlt_t type;
  uint64_t *image;
  uint16_t tmem;
  uint16_t tsize;
  uint16_t tline;
  uint16_t sid;
  uint32_t flag;
  uint32_t mask;
} uObjTxtrBlock_t;
typedef struct
{
  g_objlt_t type;
  uint64_t *image;
  uint16_t tmem;
  uint16_t twidth;
  uint16_t theight;
  uint16_t sid;
  uint32_t flag;
  uint32_t mask;
} uObjTxtrTile_t;
typedef struct
{
  g_objlt_t type;
  uint64_t *image;
  uint16_t phead;
  uint16_t pnum;
  uint16_t zero;
  uint16_t sid;
  uint32_t flag;
  uint32_t mask;
} uObjTxtrTLUT_t;
typedef union
{
  _Alignas(8)
  uObjTxtrBlock_t block;
  uObjTxtrTile_t tile;
  uObjTxtrTLUT_t tlut;
} uObjTxtr;

typedef struct
{
  uObjTxtr txtr;
  uObjSprite sprite;
} uObjTxSprite;
# 9 "/opt/n64/mips64/include/z64ovl/h/n64.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/n64/message.h" 1 3




# 1 "/opt/n64/mips64/include/z64ovl/n64/thread.h" 1 3
# 20 "/opt/n64/mips64/include/z64ovl/n64/thread.h" 3
typedef int32_t OSPri;
typedef int32_t OSId;

typedef struct
{
  uint64_t at, v0, v1, a0, a1, a2, a3,
                    t0, t1, t2, t3, t4, t5, t6, t7,
                    s0, s1, s2, s3, s4, s5, s6, s7,
                    t8, t9, gp, sp, s8, ra, lo, hi;
  uint32_t sr, pc, cause, badvaddr, rcp;
  uint32_t fpcsr;
  union
  {
    float fp32[32];
    double fp64[16];
  };

} __OSThreadContext;

typedef struct OSThread_s OSThread;
struct OSThread_s
{
  OSThread *next;
  OSPri priority;
  OSThread **queue;
  OSThread *tlnext;
  uint16_t state;
  uint16_t flags;
  OSId id;
  int32_t fp;
  __OSThreadContext context;

};

typedef void (*osCreateThread_t) (OSThread*, OSId, void(*)(void*),
                                               void*, void*, OSPri);
typedef void (*osDestroyThread_t) (OSThread*);
typedef void (*osYieldThread_t) (void);
typedef void (*osStartThread_t) (OSThread*);
typedef void (*osStopThread_t) (OSThread*);
typedef OSId (*osGetThreadId_t) (OSThread*);
typedef void (*osSetThreadPri_t) (OSThread*, OSPri);
typedef OSPri (*osGetThreadPri_t) (OSThread*);
typedef OSThread *(*osGetCurrFaultedThread_t) (void);
typedef OSThread *(*osGetNextFaultedThread_t) (OSThread*);
# 6 "/opt/n64/mips64/include/z64ovl/n64/message.h" 2 3
# 32 "/opt/n64/mips64/include/z64ovl/n64/message.h" 3
typedef uint32_t OSEvent;
typedef void *OSMesg;

typedef struct
{
  OSThread *mtqueue;
  OSThread *fullqueue;
  int32_t validCount;
  int32_t first;
  int32_t msgCount;
  OSMesg *msg;

} OSMesgQueue;

typedef void (*osCreateMesgQueue_t)(OSMesgQueue*, OSMesg*, int32_t);
typedef int32_t (*osSendMesg_t) (OSMesgQueue*, OSMesg, int32_t);
typedef int32_t (*osJamMesg_t) (OSMesgQueue*, OSMesg, int32_t);
typedef int32_t (*osRecvMesg_t) (OSMesgQueue*, OSMesg*, int32_t);
typedef void (*osSetEventMesg_t) (OSEvent, OSMesgQueue*, OSMesg);
# 10 "/opt/n64/mips64/include/z64ovl/h/n64.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/n64/pi.h" 1 3
# 36 "/opt/n64/mips64/include/z64ovl/n64/pi.h" 3
typedef struct
{
  uint32_t dram_addr;
  uint32_t cart_addr;
  uint32_t rd_len;
  uint32_t wr_len;
  uint32_t status;

} pi_regs_t;

typedef struct
{
  uint32_t errStatus;
  void *dramAddr;
  void *C2Addr;
  uint32_t sectorSize;
  uint32_t C1ErrNum;
  uint32_t C1ErrSector[4];

} __OSBlockInfo;

typedef struct
{
  uint32_t cmdType;
  uint16_t transferMode;
  uint16_t blockNum;
  int32_t sectorNum;
  uint32_t devAddr;
  uint32_t bmCtlShadow;
  uint32_t seqCtlShadow;
  __OSBlockInfo block[2];

} __OSTranxInfo;

typedef struct OSPiHandle_s OSPiHandle;
struct OSPiHandle_s
{
  OSPiHandle *next;
  uint8_t type;
  uint8_t latency;
  uint8_t pageSize;
  uint8_t relDuration;
  uint8_t pulse;
  uint8_t domain;
  uint32_t baseAddress;
  uint32_t speed;
  __OSTranxInfo transferInfo;

};

typedef struct
{
  uint16_t type;
  uint8_t pri;
  uint8_t status;
  OSMesgQueue *retQueue;

} OSIoMesgHdr;

typedef struct
{
  OSIoMesgHdr hdr;
  void *dramAddr;
  uint32_t devAddr;
  uint32_t size;
  OSPiHandle *piHandle;

} OSIoMesg;

typedef int32_t (*osEPiStartDma_t)(OSPiHandle*, OSIoMesg*, int32_t);
# 11 "/opt/n64/mips64/include/z64ovl/h/n64.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/n64/task.h" 1 3




# 1 "/opt/n64/mips64/include/z64ovl/n64/message.h" 1 3
# 6 "/opt/n64/mips64/include/z64ovl/n64/task.h" 2 3

typedef struct
{
  _Alignas(8)
  uint32_t type;
  uint32_t flags;
  uint64_t *ucode_boot;
  uint32_t ucode_boot_size;
  uint64_t *ucode;
  uint32_t ucode_size;
  uint64_t *ucode_data;
  uint32_t ucode_data_size;
  uint64_t *dram_stack;
  uint32_t dram_stack_size;
  uint64_t *output_buff;
  uint64_t *output_buff_size;
  uint64_t *data_ptr;
  uint32_t data_size;
  uint64_t *yield_data_ptr;
  uint32_t yield_data_size;

} OSTask;

typedef struct OSScTask_s OSScTask;

struct OSScTask_s
{
  OSScTask *next;
  uint32_t state;
  uint32_t flags;
  void *framebuffer;
  OSTask list;
  OSMesgQueue *msgQ;
  OSMesg msg;

};
# 12 "/opt/n64/mips64/include/z64ovl/h/n64.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/n64/thread.h" 1 3
# 13 "/opt/n64/mips64/include/z64ovl/h/n64.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/n64/vr4300.h" 1 3
# 14 "/opt/n64/mips64/include/z64ovl/h/n64.h" 2 3
# 7 "/opt/n64/mips64/include/z64ovl/oot/types.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/h/various_types.h" 1 3



# 1 "/opt/n64/mips64/include/z64ovl/h/mips.h" 1 3
# 5 "/opt/n64/mips64/include/z64ovl/h/various_types.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/h/n64.h" 1 3
# 6 "/opt/n64/mips64/include/z64ovl/h/various_types.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/h/z64_actor_bgcheck.h" 1 3
# 7 "/opt/n64/mips64/include/z64ovl/h/various_types.h" 2 3

typedef enum{
 false,
 true
} bool;
# 30 "/opt/n64/mips64/include/z64ovl/h/various_types.h" 3
typedef enum {
 INPUT_NONE = 0b0000000000000000,
 INPUT_C_RIGHT = 0b0000000000000001,
 INPUT_C_LEFT = 0b0000000000000010,
 INPUT_C_DOWN = 0b0000000000000100,
 INPUT_C_UP = 0b0000000000001000,
 INPUT_R_TRIGGER = 0b0000000000010000,
 INPUT_L_TRIGGER = 0b0000000000100000,
 INPUT_D_RIGHT = 0b0000000100000000,
 INPUT_D_LEFT = 0b0000001000000000,
 INPUT_D_DOWN = 0b0000010000000000,
 INPUT_D_UP = 0b0000100000000000,
 INPUT_START = 0b0001000000000000,
 INPUT_Z = 0b0010000000000000,
 INPUT_B = 0b0100000000000000,
 INPUT_A = 0b1000000000000000
} z64_button_t;

typedef struct {
    union {
        struct {
            uint16_t a : 1;
            uint16_t b : 1;
            uint16_t z : 1;
            uint16_t s : 1;
            uint16_t du : 1;
            uint16_t dd : 1;
            uint16_t dl : 1;
            uint16_t dr : 1;
            uint16_t : 2;
            uint16_t l : 1;
            uint16_t r : 1;
            uint16_t cu : 1;
            uint16_t cd : 1;
            uint16_t cl : 1;
            uint16_t cr : 1;
        };
        uint16_t pad;
    };
    int8_t x;
    int8_t y;
} z64_controller_t;
# 81 "/opt/n64/mips64/include/z64ovl/h/various_types.h" 3
typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb8_t;


typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} rgba8_t;


typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;

} z64_xyz_t, vec3s_t, z64_point_t;

typedef struct
{
 int16_t x;
 int16_t y;
} vec2s_t;

typedef struct
{
  float x;
  float y;
  float z;

} z64_xyzf_t, vec3f_t;

typedef struct
{
 float r, g, b, a;
} rgbaf_t;

typedef int16_t z64_angle_t;
typedef struct
{
  z64_angle_t x;
  z64_angle_t y;
  z64_angle_t z;

} z64_rot_t;

typedef struct PosRot
{
 vec3f_t pos;
 z64_rot_t rot;
} PosRot_t;



static inline float fminf(float a, float b)
{
 return a < b ? a : b;
}

static inline float fmaxf(float a, float b)
{
 return a > b ? a : b;
}

static inline float zh_pow(float in, int32_t power)
{
  float out = in;

  for (int i = 1; i < power; i++)
    out *= in;

  return out;
}
# 8 "/opt/n64/mips64/include/z64ovl/oot/types.h" 2 3

typedef struct
{
  z64_controller_t raw;



  uint16_t status;
  z64_controller_t raw_prev;
  uint16_t status_prev;
  uint16_t pad_pressed;
  int8_t x_diff;
  int8_t y_diff;
  char unk_02_[0x0002];
  uint16_t pad_released;
  int8_t adjusted_x;
  int8_t adjusted_y;
  char unk_03_[0x0002];

} z64_input_t;


typedef struct
{
  uint32_t size;
  Gfx *buf;
  Gfx *p;
  Gfx *d;

} z64_disp_buf_t;

typedef struct
{
  Gfx *poly_opa_w;
  Gfx *poly_xlu_w;
  char unk_00_[0x0008];
  Gfx *overlay_w;
  char unk_01_[0x0024];
  OSMesg task_msg[8];
  char unk_02_[0x0004];
  OSMesgQueue task_mq;
  char pad_00_[0x0004];
  OSScTask task;
  char unk_03_[0x00E0];
  Gfx *work_w;
  z64_disp_buf_t work;
  char unk_04_[0x00E4];
  z64_disp_buf_t overlay;
  z64_disp_buf_t poly_opa;
  z64_disp_buf_t poly_xlu;
  uint32_t frame_count_1;
  void *frame_buffer;
  char unk_05_[0x0008];
  uint32_t frame_count_2;

} z64_gfx_t;


typedef struct z64_game_state_s {
    z64_gfx_t * gfx_ctxt;
    void * state_main;
    void * state_dtor;
    void * next_ctor;
    uint32_t next_size;
    z64_input_t input[4];
    uint32_t state_heap_size;
    void * state_heap;
    void * heap_start;
    void * heap_end;
    void * state_heap_node;
    char unk_00_[16];
    int32_t state_continue;
    int32_t state_frames;
    uint32_t unk_01_;
} z64_game_state_t;

typedef struct
{
  uint32_t vrom_start;
  uint32_t vrom_end;

} z64_vrom_file_t;

typedef struct
{

  uint16_t type;

  struct
  {
    uint16_t unk_00_ : 3;
    uint16_t va : 13;
  };
  struct
  {
    uint16_t unk_01_ : 3;
    uint16_t vb : 13;
  };
  uint16_t vc;

  z64_xyz_t norm;

  int16_t dist;

} z64_col_poly_t;



typedef struct z64_damagechart_init_s {
    uint8_t nut;
    union damage_chart_entry_01 {
        uint8_t stick;
        uint8_t vase;
    } entry01;
    uint8_t slingshot;
    uint8_t explode;
    uint8_t boomerang;
    uint8_t arrow;
    uint8_t hammer_swing;
    uint8_t hookshot;
    struct slash {
      uint8_t sword0;
      uint8_t sword1;
      uint8_t sword2;
    } slash;
    struct magic_arrow {
      uint8_t fire;
      uint8_t ice;
      uint8_t light;
      uint8_t wind;
      uint8_t spirit;
      uint8_t shadow;
    } magic_arrow;
    struct magic {
      uint8_t fire;
      uint8_t ice;
      uint8_t light;
    } magic;
    uint8_t unk_00;
    uint8_t unk_01;
    struct littlespin {
      uint8_t sword0;
      uint8_t sword2;
      uint8_t sword1;
    } littlespin;
    union damage_chart_entry_19 {
        uint8_t sword0_jump;
        uint8_t sword0_bigspin;
        uint8_t broken_jump;
        uint8_t broken_bigspin;
    } entry19;
    union damage_chart_entry_1A {
        uint8_t sword2_jump;
        uint8_t sword2_bigspin;
    } entry1A;
    union damage_chart_entry_1B {
        uint8_t sword1_jump;
        uint8_t sword1_bigspin;
    } entry1B;
    uint8_t unk_02;
    uint8_t unk_03;
    uint8_t hammer_jump;
    uint8_t unk_04;
} z64_damagechart_init_t;

typedef struct
{
    struct attack {
        uint8_t damage : 4;
        uint8_t effect : 4;
    } attack[0x20];
} z64_damagechart_t;

typedef struct
{
  uint8_t health;
  int16_t unk_02;
  int16_t unk_04;
  uint8_t mass;
} z64_collision_check_info_init_t;

# 1 "/opt/n64/mips64/include/z64ovl/oot/actor.h" 1 3



typedef void (z64_actorfunc_t)(void *entity, void *global);

typedef enum {
  OVLTYPE_SWITCH = 0x00,
  OVLTYPE_BG = 0x01,
  OVLTYPE_PLAYER = 0x02,
  OVLTYPE_EXPLOSIVE = 0x03,
  OVLTYPE_NPC = 0x04,
  OVLTYPE_ENEMY = 0x05,
  OVLTYPE_PROP = 0x06,
  OVLTYPE_ITEM = 0x07,
  OVLTYPE_MISC = 0x08,
  OVLTYPE_BOSS = 0x09,
  OVLTYPE_DOOR = 0x0A,
  OVLTYPE_CHEST = 0x0B
} z64_actor_type_t;


typedef struct z64_actor_init_s{
             int16_t number;
             uint8_t type;
             uint8_t room;
             int32_t flags;
             int16_t object;
             int16_t padding;
             int32_t instance_size;
             void *init;
             void *dest;
             void *main;
             void *draw;
} z64_actor_init_t;


typedef struct z64_actor_s z64_actor_t;
struct z64_actor_s {
             int16_t actor_id;
             uint8_t actor_type;
             uint8_t room_index;
             uint32_t flags;
             vec3f_t pos_init;
             vec3s_t rot_init;
             uint8_t __pad_0x1A[2];
             uint16_t variable;
             uint8_t alloc_index;
             uint8_t target_dist_index;
             uint16_t sound_effect;
             uint8_t __pad_0x22[2];
             vec3f_t pos;
             vec3s_t dir;
             uint8_t __pad_0x36[2];
             vec3f_t pos_focus;
             vec3s_t rot_focus;
             uint8_t __pad_0x4A[2];
             float unk_0x4C;
             vec3f_t scale;
             vec3f_t velocity;
             float xz_speed;
             float gravity;
             float min_vel_y;
             z64_col_poly_t* wall_poly;
             z64_col_poly_t* floor_poly;
             uint8_t wall_poly_source;
             uint8_t floor_poly_source;
             int16_t wall_rot;
             float floor_height;
             float water_surface_dist;
             uint16_t bgcheck_flags;
             int16_t rot_toward_link_y;
             float dist_from_link_squared;
             float dist_from_link_xz;
             float dist_from_link_y;
             void* damage_table;
             vec3f_t displacement;
             int16_t unk_0xA8;
             int16_t unk_0xAA;
             uint8_t __pad_0xAC[2];
             uint8_t mass;
             uint8_t health;
             uint8_t damage;
             uint8_t damage_effect;
             uint8_t impact_effect;
             uint8_t unk_0xB3;
             vec3s_t rot;
             int16_t unk_0xBA;
             float unk_0xBC;
             void* shadow_func;
             float shadow_radius;
             uint8_t shadow_alpha;
             uint8_t unk_0xC9;
             uint8_t __pad_0xCA[2];
             vec3f_t unk_0xCC;
             vec3f_t unk_0xD8;
             vec3f_t unk_0xE4;
             float unk_0xF0;
             float draw_dist;
             float cam_clip_near;
             float cam_clip_far;
             vec3f_t pos_5;
             uint8_t unk_0x10C;
             uint8_t unk_0x10D;
             uint16_t text_id;
             int16_t frozen;
             uint16_t damage_color;
             uint8_t damage_color_timer;
             uint8_t active;
             uint8_t unk_0x116;
             uint8_t navi_enemy_text_id;
             z64_actor_t* attached_a;
             z64_actor_t* attached_b;
             z64_actor_t* prev;
             z64_actor_t* next;
             z64_actorfunc_t* ctor;
             z64_actorfunc_t* dtor;
             z64_actorfunc_t* main_proc;
             z64_actorfunc_t* draw_proc;
             void* code_entry;



};
# 146 "/opt/n64/mips64/include/z64ovl/oot/actor.h" 3
typedef struct z64_player_s {
    z64_actor_t actor;

    uint8_t tunic_idx;
    uint8_t sword_idx;
    uint8_t shield_idx;
    uint8_t boot_idx;
    uint8_t held_button;
    uint8_t held_action;
    uint8_t held_item_id;
    uint8_t field_0x153;
    uint8_t held_action_2;
    uint8_t field_0x155[3];
    uint8_t shield_on_back;
    uint8_t field_0x159[2];
    uint8_t shield_in_hand;
    uint8_t field_0x15c;
    uint8_t right_hand_item;
    uint8_t field_0x15e;
    uint8_t mask_now;
    uint32_t * rhand_dlist;
    uint32_t * lhand_dlist;
    uint32_t * sheath_dlist;
    uint32_t * torso_dlist;
    uint8_t field_0x170[64];
    void * title_card;
    uint8_t field_0x1b4;
    uint8_t field_0x1b5[75];
    uint8_t anime_now_1[134];
    uint8_t field_0x286[10];
    uint8_t anime_now_2[134];
    uint8_t field_0x316[148];
    z64_actor_t * held_actor;
    uint8_t field_0x3b0[132];
    uint8_t get_item_id_chest;
    int16_t gi_face_dir;
    z64_actor_t * interacted_range_actor;
    uint8_t field_0x43c[4];
    z64_actor_t * riding_actor;
    uint8_t field_0x444;
    uint8_t field_0x445[3];
    uint8_t col_struct_1[80];
    uint8_t col_struct_2[76];
    uint8_t col_struct_3[128];
    uint8_t col_struct_4[128];
    uint8_t shield_col_struct[128];
    uint8_t field_0x664[16];
    void * state_function;
    uint32_t * age_properties;
    int32_t state_flags_1;
    int32_t state_flags_2;
    uint8_t field_0x684[8];
    z64_actor_t * navi;
    uint16_t navi_msg;
    uint8_t field_0x692[62];
    uint32_t anime_now_id;
    uint8_t field_0x6d4[18];
    void * field_0x6e8;
    void * field_0x6ec;
    uint8_t field_0x6f0[8];
    void * field_0x6f8;
    uint8_t field_0x6fc[20];
    uint8_t field_0x710[132];
    uint8_t field_0x794[152];
    void * field_0x82c;
    uint8_t field_0x830[18];
    uint8_t sword_anim_index;
    uint8_t field_0x843[21];
    float field_0x858;
    float deku_stick_y_scale;
    int16_t deku_stick_flame_timer;
    uint8_t get_item_id;
    uint8_t field_0x863[73];
    float fan_wind_speed;
    int16_t fan_wind_dir;
    uint8_t field_0x8b2[6];
    vec3f_t deku_stick_tip;
    uint8_t field_0x8c4[68];
    vec3f_t field_0x908;
    uint8_t field_0x914[204];
    float sword_mf[4][4];
    float shield_mf[4][4];
    uint8_t field_0xa60[24];
    uint8_t inv_frames;
} z64_player_t;
# 190 "/opt/n64/mips64/include/z64ovl/oot/types.h" 2 3

typedef struct
{
  struct
  {
    uint32_t unk_00_ : 1;

    uint32_t drop : 1;
    uint32_t special : 4;
    uint32_t interaction : 5;
    uint32_t unk_01_ : 3;
    uint32_t behavior : 5;
    uint32_t exit : 5;
    uint32_t camera : 8;
  } flags_1;
  struct
  {
    uint32_t pad_00_ : 4;
    uint32_t wall_damage : 1;
    uint32_t unk_00_ : 6;
    uint32_t unk_01_ : 3;
    uint32_t hookshot : 1;
    uint32_t echo : 6;
    uint32_t unk_02_ : 5;
    uint32_t terrain : 2;
    uint32_t material : 4;
  } flags_2;

} z64_col_type_t;

typedef struct
{
  z64_xyz_t pos;
  z64_xyz_t rot;
  int16_t fov;
  int16_t unk_00_;

} z64_camera_params_t;

typedef struct
{
  uint16_t mode;
  uint16_t unk_01_;

  uint32_t seg_params;

} z64_camera_t;

typedef struct
{
  z64_xyz_t pos;
  int16_t width;
  int16_t depth;
  char pad_00_[0x0002];
  struct
  {
    uint32_t unk_00_ : 12;
    uint32_t active : 1;

    uint32_t group : 6;
    uint32_t unk_01_ : 5;
    uint32_t camera : 8;
  } flags;

} z64_col_water_t;

typedef struct
{
  z64_xyz_t min;
  z64_xyz_t max;
  uint16_t n_vtx;
  char pad_00_[0x0002];
  z64_xyz_t *vtx;
  uint16_t n_poly;
  char pad_01_[0x0002];
  z64_col_poly_t *poly;
  z64_col_type_t *type;
  z64_camera_t *camera;
  uint16_t n_water;
  char pad_02_[0x0002];
  z64_col_water_t *water;

} z64_col_hdr_t;

typedef struct
{
  int16_t poly_idx;
  uint16_t list_next;

} z64_col_list_t;

typedef struct
{
  uint16_t floor_list_idx;
  uint16_t wall_list_idx;
  uint16_t ceil_list_idx;

} z64_col_lut_t;

typedef struct
{

  z64_col_hdr_t *col_hdr;
  z64_xyzf_t bbox_min;
  z64_xyzf_t bbox_max;
  int n_sect_x;
  int n_sect_y;
  int n_sect_z;
  z64_xyzf_t sect_size;
  z64_xyzf_t sect_inv;
  z64_col_lut_t *stc_lut;
  uint16_t stc_list_max;
  uint16_t stc_list_pos;
  z64_col_list_t *stc_list;
  uint8_t *stc_check;
  char unk_00_[0x13F0];

  z64_col_poly_t *dyn_poly;
  z64_xyz_t *dyn_vtx;
  z64_col_list_t *dyn_list;
  char unk_01_[0x0008];
  uint32_t dyn_list_max;
  uint32_t dyn_poly_max;
  uint32_t dyn_vtx_max;
  char unk_02_[0x0004];

} z64_col_ctxt_t;

typedef struct
{

  uint32_t tex_start;
  uint32_t tex_end;
  uint32_t pal_start;
  uint32_t pal_end;

} z64_sky_image_t;

typedef struct
{
  char unk_00_[0x0128];
  char *textures[2];
  char *palettes;
  Gfx *gfx;
  char unk_01_[0x0004];
  char *vtx;
  int16_t mode;
  char unk_02_[0x0006];
  float f148;
  char unk_03_[0x0004];

} z64_sky_ctxt_t;

typedef struct
{

  uint32_t vrom_addr;
  void *dram_addr;
  uint32_t size;

  char *filename;
  int32_t line;
  int32_t unk_00_;

  OSMesgQueue *notify_mq;
  OSMesg notify_msg;

} z64_getfile_t;

typedef struct
{
  uint32_t vrom_start;
  uint32_t vrom_end;
  uint32_t prom_start;
  uint32_t prom_end;

} z64_ftab_t;

typedef struct
{
  int16_t id;
  char pad_00_[0x0002];
  void *data;
  z64_getfile_t getfile;
  OSMesgQueue load_mq;
  OSMesg load_m;

} z64_mem_obj_t;

typedef struct
{
  void *obj_space_start;
  void *obj_space_end;
  uint8_t n_objects;
  uint8_t n_special;
  uint8_t keep_index;
  uint8_t skeep_index;
  z64_mem_obj_t objects[19];

} z64_obj_ctxt_t;

typedef struct
{
  char unk_00_;
  int8_t n_entries;
  char pad_00_[0x0002];
  uint32_t seg_start;
  uint32_t seg_end;

} z64_sr_mesh_t;

typedef struct
{
  int8_t room_idx_1;
  int8_t effect_1;
  int8_t room_idx_2;
  int8_t effect_2;
  int16_t actor_id;
  z64_xyz_t pos;
  z64_angle_t rot;
  int16_t variable;

} z64_tnsn_actor_t;

typedef struct
{
  int8_t index;
  char unk_00_[0x0001];
  uint8_t bhv_z;
  uint8_t bhv_x;
  uint8_t echo;
  int8_t show_invis_act;
  char pad_00_[0x0002];
  z64_sr_mesh_t *mesh_hdr;
  void *file;
  char unk_01_[0x0004];

} z64_room_t;

typedef struct
{

  z64_room_t rooms[2];
  void *room_space_start;
  void *room_space_end;

  uint8_t load_slot;
  int8_t load_active;
  char pad_00_[0x0002];
  void *load_ptr;
  z64_getfile_t load_getfile;
  OSMesgQueue load_notify_mq;
  OSMesg load_notify_msg;


  int16_t cojiro_sfx_played;
  int16_t cojiro_sfx_timer;

  uint8_t n_tnsn;
  char pad_01_[0x0003];
  z64_tnsn_actor_t *tnsn_list;

} z64_room_ctxt_t;

typedef enum button_id_e {
    BTN_ID_B
    , BTN_ID_CL
    , BTN_ID_CD
    , BTN_ID_CR
    , INV_OFF_CL
    , INV_OFF_CD
    , INV_OFF_CR
} button_id_t;


typedef struct
{
                char view[0x128];
                void* parameter_frame_vtx;
                void* heart_vtx;

                char* parameter_segment;
                char* do_action_segment;
                char* icon_item_segment;
                char* map_segment;
                char map_palete[16 * 2];

                char pad[0x1EC - 0x160];

                int16_t do_action_flg;
                uint16_t do_action;
                uint16_t do_action_old;
                float do_action_rotate;
                int16_t navi_flag;
                int16_t sp_action_flag;
                int16_t sp_action;

                int16_t health_meter;
                int16_t now_mode;

                int16_t active_heart_fg[3];
                int16_t active_heart_bg[3];
                int16_t heart_fg_r[2];
                int16_t heart_fg_g[2];
                int16_t heart_fg_b[2];
                int16_t heart_bg_r[2];
                int16_t heart_bg_g[2];
                int16_t heart_bg_b[2];

                int16_t active_heart_max;
                int16_t active_heart_timer;
                int16_t active_heart_wait;
                int16_t active_heart_flag;

                int16_t magic_mp_cost;
                int16_t magic_delta;

                int16_t rupee_counter[4];
                uint8_t carrot_counter;

                uint16_t horseback_archery_score;
                uint16_t horseback_archery_arrow;
                uint16_t yabu_mode;
                uint16_t yabu_score;

                uint16_t fill_alpha;
                uint16_t a_alpha;
                uint16_t b_alpha;
                uint16_t cl_alpha;
                uint16_t cd_alpha;
                uint16_t cr_alpha;
                uint16_t heart_alpha;
                uint16_t magic_alpha;
                uint16_t map_alpha;
                int16_t start_alpha;

                int16_t spot_map_no;
                int16_t dungeon_map_no;
                int16_t room_no;
                int16_t map_palette_no;

                uint8_t fishing_rod_equipped;
                uint8_t marathon_flag;


    struct {
                    uint8_t h_gage;
                    uint8_t b_button;
                    uint8_t a_button;
                    uint8_t c_bottle;
                    uint8_t c_warasibe;
                    uint8_t c_hook;
                    uint8_t c_ocarina;
                    uint8_t c_warp;
                    uint8_t c_sunmoon;
                    uint8_t m_wind;
                    uint8_t m_magic;
                    uint8_t another;
    } restrictions;


} z64_if_ctxt_t;

typedef struct
{
  char unk_00_[0x0128];
  void *icon_item;
  void *icon_item_24;
  void *icon_item_s;
  void *icon_item_lang;
  void *name_texture;
  void *p13C;
  char unk_01_[0x0094];
  uint16_t state;
  char unk_02_[0x0012];
  uint16_t screen_idx;
  char unk_03_[0x002E];
  int16_t item_cursor;
  char unk_04_[0x0002];
  int16_t quest_cursor;
  int16_t equip_cursor;
  int16_t map_cursor;
  int16_t item_x;
  char unk_05_[0x0004];
  int16_t equipment_x;
  char unk_06_[0x0002];
  int16_t item_y;
  char unk_07_[0x0004];
  int16_t equipment_y;
  char unk_08_[0x0004];
  int16_t cursor_pos;
  char unk_09_[0x0002];
  int16_t item_id;
  int16_t item_item;
  int16_t map_item;
  int16_t quest_item;
  int16_t equip_item;
  char unk_0A_[0x0004];
  int16_t quest_hilite;
  char unk_0B_[0x0018];
  int16_t quest_song;
  char unk_0C_[0x0016];

  char s27C[0x0038];

} z64_pause_ctxt_t;


typedef struct
{
  int8_t dir[3];
  uint8_t col[3];

} z64_light1_t;

typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
  uint8_t col[3];
  char pad_00_[0x0001];
  int16_t intensity;

} z64_light2_t;

typedef union
{
  z64_light1_t light1;
  z64_light2_t light2;

} z64_lightn_t;

typedef struct
{
  uint8_t type;
  char pad_00_[0x0001];
  z64_lightn_t lightn;

} z64_light_t;

typedef struct z64_light_node_s z64_light_node_t;
struct z64_light_node_s
{
  z64_light_t *light;
  z64_light_node_t *prev;
  z64_light_node_t *next;

};

typedef struct
{
  uint32_t n_nodes;
  uint32_t current_node;
  z64_light_node_t nodes[32];

} z64_light_queue_t;

typedef struct
{
  z64_light_node_t *light_list;
  uint8_t ambient[3];
  uint8_t fog[3];
  int16_t fog_position;
  int16_t draw_distance;
  char pad_00_[0x0002];

} z64_lighting_t;

typedef struct
{
  vec3s_t pos;
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t unk;
  int16_t radius;
} z64_light_params_pos_t;

typedef struct
{
  uint8_t type;
  z64_light_params_pos_t params;
} z64_lightinfo_pos_t;

typedef struct {
  int16_t posX;
  int16_t posY;
  int16_t posZ;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t unk_09;
  int16_t radius;
} z64_lightinfo_params_t;

typedef struct
{
  uint8_t type;
  z64_lightinfo_params_t params;
} z64_lightinfo_t;

typedef struct
{
  int8_t numlights;
  char pad_00_[0x0007];
  Lightsn lites;

} z64_gbi_lights_t;

typedef void (*z64_light_handler_t)(z64_gbi_lights_t*, z64_lightn_t*,
                                    z64_actor_t*);

typedef struct z64_dynapoly {
    uint32_t poly_id;
    float push_movement;
    float unk_03;
    uint16_t push_direction;
    uint16_t unk_05;
    uint32_t movement;
    uint8_t flags;
    char padding[0x0003];
} z64_dynapoly_t;

# 1 "/opt/n64/mips64/include/z64ovl/h/z64_collision_check.h" 1 3





typedef enum z64_damage_fx_e {
    DMG_FX_KNOCKBACK
    , DMG_FX_FIRE
    , DMG_FX_ICE
    , DMG_FX_ELECTRIC
} z64_damage_fx_t;

typedef struct z64_collider_s {
    z64_actor_t * actor;
    z64_actor_t * at;
    z64_actor_t * ac;
    z64_actor_t * oc;
    uint8_t flags_at;
    uint8_t flags_ac;
    uint8_t mask_a;
    uint8_t mask_b;
    uint8_t type;
    uint8_t shape;
} z64_collider_t;

typedef struct z64_collider_touch_s {
    int32_t flags;
    uint8_t effect;
    uint8_t damage;
} z64_collider_touch_t;

typedef struct z64_collider_bump_init_s {
    int32_t flags;
    uint8_t effect;
    uint8_t defense;
} z64_collider_bump_init_t;

typedef struct z64_collider_body_init_s {
    uint8_t flags_body;
    z64_collider_touch_t toucher;
    z64_collider_bump_init_t bumper;
    uint8_t flags_toucher;
    uint8_t flags_bumper;
    uint8_t flags_body_2;
} z64_collider_body_init_t;

typedef struct z64_collider_bump_s {
    int32_t flags;
    uint8_t effect;
    uint8_t defense;
    vec3s_t unk_0x06;
} z64_collider_bump_t;

typedef struct z64_collider_body_s z64_collider_body_t;
struct z64_collider_body_s {
    z64_collider_touch_t toucher;
    z64_collider_bump_t bumper;
    uint8_t flags;
    uint8_t flags_toucher;
    uint8_t flags_bumper;
    uint8_t flags_oc;
    z64_collider_t * hit_at;
    z64_collider_t * hit_ac;
    z64_collider_body_t * hit_item_at;
    z64_collider_body_t * hit_item_ac;
};

typedef struct z64_collider_init_actor_s {
    z64_actor_t * actor;
    uint8_t flags_at;
    uint8_t flags_ac;
    uint8_t mask_a;
    uint8_t shape;
} z64_collider_init_actor_t;

typedef struct z64_cylinder16_s {
    int16_t radius;
    int16_t height;
    int16_t y_shift;
    vec3s_t pos;
} z64_cylinder16_t;

typedef struct z64_collider_cylinder_init_actor_s {
    z64_collider_init_actor_t base;
    z64_collider_body_init_t body;
    z64_cylinder16_t dim;
} z64_collider_cylinder_init_actor_t;

typedef struct z64_collider_init_set3_s {
    uint8_t type;
    uint8_t flags_at;
    uint8_t flags_ac;
    uint8_t mask_a;
    uint8_t shape;
} z64_collider_init_set3_t;

typedef struct z64_collider_cylinder_init_set3_s {
    z64_collider_init_set3_t base;
    z64_collider_body_init_t body;
    z64_cylinder16_t dim;
} z64_collider_cylinder_init_set3_t;

typedef struct z64_collider_init_s {
    uint8_t type;
    uint8_t flags_at;
    uint8_t flags_ac;
    uint8_t mask_a;
    uint8_t mask_b;
    uint8_t shape;
} z64_collider_init_t;

typedef struct z64_collider_cylinder_init_s {
    z64_collider_init_t base;
    z64_collider_body_init_t body;
    z64_cylinder16_t dim;
} z64_collider_cylinder_init_t;

typedef struct z64_collider_cylinder_s {
    z64_collider_t base;
    z64_collider_body_t body;
    z64_cylinder16_t dim;
} z64_collider_cylinder_t;

typedef struct z64_sphere16_s {
    vec3s_t center;
    int16_t radius;
} z64_sphere16_t;

typedef struct z64_collider_jntsph_item_dim_s {
    z64_sphere16_t sphere_model;
    z64_sphere16_t sphere_world;
    float scale;
    uint8_t joint;
} z64_collider_jntsph_item_dim_t;

typedef struct z64_collider_jntsph_item_s {
    z64_collider_body_t body;
    z64_collider_jntsph_item_dim_t dim;
} z64_collider_jntsph_item_t;

typedef struct z64_collider_jntsph_s {
    z64_collider_t base;
    int32_t count;
    z64_collider_jntsph_item_t * list;
} z64_collider_jntsph_t;

typedef struct z64_collider_jntsph_item_dim_init_s {
    uint8_t joint;
    z64_sphere16_t sphere_model;
    int16_t scale;
} z64_collider_jntsph_item_dim_init_t;

typedef struct z64_collider_jntsph_item_init_s {
    z64_collider_body_init_t body;
    z64_collider_jntsph_item_dim_init_t dim;
} z64_collider_jntsph_item_init_t;

typedef struct z64_collider_jntsph_init_actor_s {
    z64_collider_init_actor_t base;
    int32_t count;
    z64_collider_jntsph_item_init_t * list;
} z64_collider_jntsph_init_actor_t;

typedef struct z64_collider_jntsph_init_set3_s {
    z64_collider_init_set3_t base;
    int32_t count;
    z64_collider_jntsph_item_init_t * list;
} z64_collider_jntsph_init_set3_t;

typedef struct z64_collider_jntsph_init_s {
    z64_collider_init_t base;
    int32_t count;
    z64_collider_jntsph_item_init_t * list;
} z64_collider_jntsph_init_t;

typedef struct z64_collider_quad_dim_init_s {
    vec3f_t quad[4];
} z64_collider_quad_dim_init_t;

typedef struct z64_collider_quad_dim_s {
    vec3f_t quad[4];
    vec3s_t dc_mid;
    vec3s_t ba_mid;
    float unk_0x3C;
} z64_collider_quad_dim_t;

typedef struct z64_collider_quad_init_set3_s {
    z64_collider_init_set3_t base;
    z64_collider_body_init_t body;
    z64_collider_quad_dim_init_t dim;
} z64_collider_quad_init_set3_t;

typedef struct z64_collider_quad_init_s {
    z64_collider_init_t base;
    z64_collider_body_init_t body;
    z64_collider_quad_dim_init_t dim;
} z64_collider_quad_init_t;

typedef struct z64_collider_quad_s {
    z64_collider_t base;
    z64_collider_body_t body;
    z64_collider_quad_dim_t dim;
} z64_collider_quad_t;

typedef enum z64_collider_shape_e {
    COL_SHAPE_CYLINDER=1,
    COL_SHAPE_INVALID=4,
    COL_SHAPE_JNTSPH=0,
    COL_SHAPE_QUAD=3,
    COL_SHAPE_TRIS=2
} z64_collider_shape_t;

typedef struct z64_collider_tris_item_dim_init_s {
    vec3f_t vtx[3];
} z64_collider_tris_item_dim_init_t;

typedef struct z64_collider_tris_item_init_s {
    z64_collider_body_init_t body;
    z64_collider_tris_item_dim_init_t dim;
} z64_collider_tris_item_init_t;

typedef struct z64_collider_tris_init_set3_s {
    z64_collider_init_set3_t base;
    int32_t count;
    z64_collider_tris_item_init_t * list;
} z64_collider_tris_init_set3_t;

typedef struct z64_collider_tris_init_s {
    z64_collider_init_t base;
    int32_t count;
    z64_collider_tris_item_init_t * list;
} z64_collider_tris_init_t;

typedef struct z64_plane_s {
    vec3f_t normal;
    float origin_dist;
} z64_plane_t;

typedef struct z64_tri_norm_s {
    vec3f_t vtx[3];
    z64_plane_t plane;
} z64_tri_norm_t;

typedef struct z64_collider_tris_item_s {
    z64_collider_body_t body;
    z64_tri_norm_t dim;
} z64_collider_tris_item_t;

typedef struct z64_collider_tris_s {
    z64_collider_t base;
    int32_t count;
    z64_collider_tris_item_t * list;
} z64_collider_tris_t;

typedef enum z64_collider_type_t {
    COL_TYPE_SHIELD_METAL=9,
    COL_TYPE_SHIELD_WOOD=11,
    COL_TYPE_UNK10=10,
    COL_TYPE_UNK0=0,
    COL_TYPE_UNK1=1,
    COL_TYPE_UNK12=12,
    COL_TYPE_UNK13=13,
    COL_TYPE_UNK2=2,
    COL_TYPE_UNK3=3,
    COL_TYPE_UNK4=4,
    COL_TYPE_UNK5=5,
    COL_TYPE_UNK6=6,
    COL_TYPE_UNK7=7,
    COL_TYPE_UNK8=8
} z64_collider_type_t;

typedef struct z64_linef_s {
    vec3f_t a;
    vec3f_t b;
} z64_linef_t;

typedef struct z64_ocline_s {
    z64_linef_t line;
    uint16_t unk_0x18;
} z64_ocline_t;
# 715 "/opt/n64/mips64/include/z64ovl/oot/types.h" 2 3

typedef struct
{
  int16_t n_at;
  uint32_t hz_0x02;
  z64_collider_t* at_list[50];
  int32_t n_ac;
  z64_collider_t* ac_list[60];
  int32_t n_ot;
  z64_collider_t* ot_list[50];
} z64_hit_ctxt_t;

typedef struct
{
  int32_t top;
  int32_t bottom;
  int32_t left;
  int32_t right;
} z64_viewport_t;

typedef struct {
  vec3f_t pos;
  float unk_0C;
  rgb8_t color;
} z64_target_context_entry_t;

typedef struct {
  vec3f_t naviRefPos;
  vec3f_t targetCenterPos;
  struct {
    float red;
    float green;
    float blue;
    float alpha;
  } naviInner;
  struct {
    float red;
    float green;
    float blue;
    float alpha;
  } naviOuter;
  z64_actor_t* arrowPointedActor;
  z64_actor_t* targetedActor;
  float unk_40;
  float unk_44;
  int16_t unk_48;
  uint8_t activeType;
  uint8_t unk_4B;
  int8_t unk_4C;
  char unk_4D[3];
  z64_target_context_entry_t arr_50[3];
  z64_actor_t* unk_8C;
  z64_actor_t* unk_90;
  z64_actor_t* unk_94;
} z64_target_context_t;

typedef struct {
               uint32_t texture;
               int16_t unk_4;
               int16_t unk_6;
               uint8_t unk_8;
               uint8_t unk_9;
               uint8_t delayA;
               uint8_t delayB;
               int16_t unk_C;
               int16_t unk_E;
} z64_title_card_context_t;

typedef struct {
  uint32_t length;
  z64_actor_t* first;
} z64_actor_list_entry_t;

typedef struct {
  uint8_t unk_00;
  char unk_01[1];
  uint8_t unk_02;
  uint8_t unk_03;
  char unk_04[4];
  uint8_t total;
  z64_actor_list_entry_t actor_list[12];
  z64_target_context_t target_ctxt;
  struct {
    uint32_t swch;
    uint32_t temp_swch;
    uint32_t unk0;
    uint32_t unk1;
    uint32_t chest;
    uint32_t clear;
    uint32_t temp_clear;
    uint32_t collect;
    uint32_t temp_collect;
  } flags;
  z64_title_card_context_t title_ctxt;
  char unk_138[4];
  void* absolute_space;
} z64_actor_context_t;

typedef struct {
    float height;
    int16_t dist;
} special0;

typedef struct {
                 float unk_00;
                 float unk_04;
                 int16_t unk_08;
} special9;

typedef struct {
    char unk_00[0xC];
    int32_t unk_0C;
    float target_init_zoom;
    int16_t unk_14;
    int16_t unk_16;
    int16_t unk_18;
    int16_t unk_1A;
    float unk_1C;
    float unk_20;
    int16_t unk_24;
    int16_t unk_26;
    int16_t unk_28;
    int16_t unk_2A;
} normal3_unk20;

typedef struct {
    float height;
    float dist;
    float angle;
    float unk_0C;
    float nearby_height;
    float dist_height;
    float unk_18;
    int16_t unk_1C;
    int16_t unk_1E;
    normal3_unk20 unk_20;
} normal3;

typedef struct {
                 float unk_00;
                 int16_t unk_04;
} demo1_unk_04;

typedef struct {
                 int16_t unk_00;
                 int16_t unk_02;
                 demo1_unk_04 unk_04;
} demo1;

typedef struct {
                 z64_actor_t* door;
                 int16_t unk_04;
                 int16_t unk_06;
                 int16_t unk_08;
                 int16_t unk_0A;
                 special9 spec9;
                 int16_t unk_18;
} z64_camera_door_t;

typedef struct {
               int8_t continueFlag;
               int8_t cameraRoll;
               uint16_t nextPointFrame;
               float viewAngle;
               vec3s_t pos;
} z64_camera_demo_point_t;

typedef union {
    char data[0x50];
    int16_t sh[2];
    int32_t w;
    float f;
    z64_camera_door_t doorCam;
    special0 spec0;
    demo1 demo1;
    normal3 normal3;
} camera_unk_00;


typedef struct {
                 camera_unk_00 unk_00;
                 vec3f_t at;
                 vec3f_t eye;
                 vec3f_t unk_68;
                 vec3f_t eyeNext;
                 vec3f_t unk_80;
                 struct z64_global_t* globalCtx;
                 z64_player_t* player;
                 vec3f_t playerPos;
                 vec3s_t playerRot;
                 z64_actor_t* target;
                 vec3f_t targetPos;
                 vec3s_t targetRot;
                 vec3f_t unk_C0;
                 vec3f_t unk_CC;
                 float unk_D8;
                 float dist;
                 float unk_E0;
                 vec3f_t unk_E4;
                 vec3f_t unk_F0;
                 float fov;
                 float unk_100;
                 float unk_104;
                 vec3f_t unk_108;
                 char unk_114[0x4];
                 int32_t unk_118;
                 int32_t unk_11C;
                 char unk_120[0x4];
                 z64_camera_demo_point_t* atPoints;
                 z64_camera_demo_point_t* eyePoints;
                 int16_t relativeToPlayer;
                 int16_t unk_12E;
                 int16_t uid;
                 char unk_132[0x02];
                 vec3s_t unk_134;
                 vec3s_t unk_13A;
                 int16_t status;
                 int16_t setting;
                 int16_t mode;
                 int16_t unk_146;
                 int16_t unk_148;
                 int16_t unk_14A;
                 int16_t unk_14C;
                 int16_t unk_14E;
                 int16_t unk_150;
                 int16_t unk_152;
                 uint16_t unk_154;
                 int16_t unk_156;
                 int16_t unk_158;
                 int16_t roll;
                 int16_t unk_15C;
                 int16_t unk_15E;
                 int16_t unk_160;
                 int16_t unk_162;
                 int16_t unk_164;
                 int16_t unk_166;
                 int16_t unk_168;
                 int16_t unk_16A;
} z64_gl_camera_t;

typedef struct {
    int8_t continue_flag;
    int8_t roll;
    uint16_t next_point_frame;
    float view_angle;
    vec3s_t pos;
} z64_cutscene_camera_point_t;

typedef struct {
    uint16_t action;
    uint16_t start_frame;
    uint16_t end_frame;
    vec3s_t rot;
    struct
    {
      int32_t x;
      int32_t y;
      int32_t z;
    } start_pos;
    struct
    {
      int32_t x;
      int32_t y;
      int32_t z;
    } end_pos;
    struct
    {
      int32_t x;
      int32_t y;
      int32_t z;
    } normal;

} z64_cutscene_actor_action_t;

typedef struct
{
  char unk_00[0x4];
  void *ptr;
  uint8_t state;





  float unk_0C;
  uint16_t frame;
  uint16_t unk_12;
  int32_t unk_14;
  uint16_t frame_lastcmd;
  uint8_t unk_1A;
  uint8_t unk_1B;
  z64_cutscene_camera_point_t *cam_focus;
  z64_cutscene_camera_point_t *cam_pos;
  z64_cutscene_actor_action_t *link_action;
  z64_cutscene_actor_action_t *npc_action[0xA];
}z64_cutscene_t;


typedef struct
{
  z64_game_state_t common;
  uint16_t scene_index;
  char unk_00_[0x000A];
  void *scene_file;
  char unk_01_[4];
  struct
  {
    char unk[8];
    uint32_t screen_top;
    uint32_t screen_bottom;
    uint32_t screen_left;
    uint32_t screen_right;
    float camera_distance;
    float fog_distance;
    float z_distance;
    float unk_02_;
    vec3f_t eye;
    char unk_03_[0x00F4];
  } view;

  z64_gl_camera_t camera[4];
  z64_gl_camera_t* pointer[4];
  int16_t active_camera;
  int16_t next_camera;
  uint8_t seq_idx;
  uint8_t night_sfx;
  char unk_08_[0x0002];
  z64_lighting_t lighting;
  char unk_09_[0x0008];
  z64_col_ctxt_t col_ctxt;
  z64_actor_context_t actor_ctxt;
  z64_cutscene_t cutscene;
  char unk_0F_[0x01C4];
  z64_sky_ctxt_t sky_ctxt;
  char unk_10_[0xE2C0];
  char *message_texture;
  char unk_11_[0x0044];
  uint16_t message_current;
  char unk_0x103D2[0x0003];
  uint8_t message_type;
  char unk_12_[0x0006];
  uint8_t message_state_1;
  char pad_00_[0x0001];
  union
  {
    uint8_t message_data_e[200];
    uint16_t message_data_j[100];
  };
  char unk_13_[0x0016];
  uint8_t message_state_2;
  char unk_14_[0x0002];
  uint8_t message_state_3;
  char unk_15_[0x0004];
  uint16_t played_ocarina_song;
  char unk_15_2[0x001A];
  z64_actor_t *textbox_actor;

  char unk_104E4[0xC];
  z64_if_ctxt_t if_ctxt;
  z64_pause_ctxt_t pause_ctxt;
  char unk_16_[0x000C];
  uint16_t death_state;
  char unk_17_[0x0012];
  uint8_t sky_image_idx[2];
  char unk_18_[0x007A];
  int16_t unk_0x10AB0[6];
  char unk_18_1[0x48];
  uint8_t day_phase;
  char unk_19_[0x000D];
  uint8_t rain_effect_1;
  uint8_t rain_level;
  char unk_1A_[0x0002];
  uint8_t rain_effect_2;
  char unk_1B_[0x0C8D];
  z64_obj_ctxt_t obj_ctxt;
  z64_room_ctxt_t room_ctxt;
  char unk_11D3C[0x10];
  int (*unk_11D4C)(void*, void*);
  char unk_11D50[0x50];
  float unk_player_matrix[16];
  char unk_1C_2[0x0004];
  uint32_t gameplay_frames;
  uint8_t link_age;
  char unk_1D_;
  uint8_t spawn_index;
  uint8_t n_map_actors;
  uint8_t n_rooms;
  char unk_1E_[0x0003];
  z64_vrom_file_t *room_list;
  char unk_1F_[0x0004];
  void *map_actor_list;
  char unk_20_[0x0008];
  void *scene_exit_list;
  char unk_21_[0x0004];
  void *elf_message;
  uint32_t situdata;
  uint8_t skybox_type;
  int8_t scene_load_flag;
  char unk_23_[0x0004];
  int16_t entrance_index;
  char unk_24_[0x0042];
  uint8_t fadeout_transition;
  char unk_25_;
 z64_hit_ctxt_t hit_ctxt;
 char unk_26_[0x06B4];

} z64_global_t;

typedef struct {
            void *printer;
            uint32_t dlist_end;
            uint16_t x;
            uint16_t y;
            uint16_t unk1;
            uint8_t unk2;
            uint8_t unk3;
            uint32_t string_rgba;
} z64_debug_text_t;



typedef struct z64_skelanime_s z64_skelanime_t;

typedef enum {
  ANIMATION_LINKANIMETION
  , ANIMATION_TYPE1
  , ANIMATION_TYPE2
  , ANIMATION_TYPE3
  , ANIMATION_TYPE4
  , ANIMATION_TYPE5
} z64_animation_type_e;

typedef struct {
             vec3s_t translation;
             uint8_t first_child_index;
             uint8_t sibling_limb_index;
             Gfx* dlist[1];
} z64_skel_limb_entry_t;

typedef struct {
             z64_skel_limb_entry_t* limbs[1];
} z64_skeleton_t;

typedef struct {
             z64_skeleton_t* skeleton;
             uint8_t limb_count;
             uint8_t ___pad0;
             uint8_t dlist_count;
} z64_skeleton_header_t;

typedef struct {
  int16_t frame_count;
  int16_t __pad0;
} z64_anim_header_init_t;

typedef struct {
  z64_anim_header_init_t common;
  uint32_t rotation_values;
  uint32_t rotation_index;
  uint16_t limit;
} z64_anim_header_t;

typedef struct {
  uint8_t req[0x20];
  OSMesgQueue msgQueue;
  OSMesg msg;
} z64_animation_type_0_t;

typedef struct {
  uint8_t unk0;
  uint8_t vec_count;
  vec3s_t* dst;
  vec3s_t* src;
} z64_animation_type_1_t;

typedef struct {
  uint8_t unk0;
  uint8_t limb_count;
  vec3s_t* unk_04;
  vec3s_t* unk_08;
  float unk_0C;
} z64_animation_type_2_t;

typedef struct {
  uint8_t unk0;
  uint8_t vec_count;
  vec3s_t* dst;
  vec3s_t* src;
  uint8_t* index;
} z64_animation_type_3_t;

typedef struct {
  uint8_t unk0;
  uint8_t vec_count;
  uint8_t unk_02[2];
  vec3s_t* dst;
  vec3s_t* src;
  uint8_t* index;
} z64_animation_type_4_t;

typedef struct {
  z64_actor_t* actor;
  z64_skelanime_t* skelanime;
  float unk_08;
} z64_animation_type_5_t;

typedef struct {
  uint8_t raw[0x3C];
} z64_animation_type_raw_t;

typedef union {
  z64_animation_type_raw_t raw;
  z64_animation_type_0_t type0;
  z64_animation_type_1_t type1;
  z64_animation_type_2_t type2;
  z64_animation_type_3_t type3;
  z64_animation_type_4_t type4;
  z64_animation_type_5_t type5;
} z64_animation_type_t;

typedef struct {
  uint8_t type;
  uint8_t unk_01;
  z64_animation_type_t types;
} z64_animation_entry_t;

typedef struct {
  z64_anim_header_init_t common;
  uint32_t anim;
} z64_animation_entry_link_t;

struct z64_skelanime_s {
   uint8_t limb_count;
   uint8_t mode;
   uint8_t dlist_count;
   uint8_t _pad0;
   z64_skeleton_t* skeleton;
   union {
    z64_anim_header_t* seg;
    z64_animation_entry_link_t* link_animetion_seg;
    z64_anim_header_init_t* common_seg;
  } anim_current;
   float start_frame;
   float anim_frame_count;
   float anim_frame_total;
   float anim_current_frame;
   float anim_playback_speed;
   vec3s_t* limb_draw_table;
   vec3s_t* transition_draw_table;
   float trans_current_frame;
   float transition_step;
   int32_t (*anim_update)();
   int8_t init_flags;
   uint8_t flags;
   int16_t prev_frame_rot;
   vec3s_t prev_frame_pos;
   vec3s_t unk_0x3E;
};

typedef struct
{
  uint8_t unk00[0x4C];
  z64_skelanime_t skelanime;
} z64_skelanime_weighted_t;

typedef struct {
     char unk_00[0x184];
     rgba8_t p1StartColor;
     rgba8_t p2StartColor;
     rgba8_t p1EndColor;
     rgba8_t p2EndColor;
     int32_t elemDuration;
     int32_t unkFlag;
     int32_t calcMode;
} z_eff_blure_init_t;

typedef struct {
     int32_t state;
     int32_t timer;
     vec3s_t p1;
     vec3s_t p2;
     uint16_t flags;
} z64_eff_blure_elem_t;

typedef struct {
     z64_eff_blure_elem_t elements[16];
     int32_t calcMode;
     float mode4Param;
     uint16_t flags;
     int16_t addAngleChange;
     int16_t addAngle;
     rgba8_t p1StartColor;
     rgba8_t p2StartColor;
     rgba8_t p1EndColor;
     rgba8_t p2EndColor;
     uint8_t numElements;
     uint8_t elemDuration;
     uint8_t unkFlag;
     uint8_t drawMode;
     rgba8_t altPrimColor;
     rgba8_t altEnvColor;
} z64_eff_blure_t;

typedef struct {
     uint8_t button_items[4];
     uint8_t c_button_slots[3];
     uint16_t equipment;
} z64_item_equips;

typedef struct {
     uint32_t chest;
     uint32_t swch;
     uint32_t clear;
     uint32_t collect;
     uint32_t unk;
     uint32_t rooms;
     uint32_t floors;
} z64_save_scene_flags;

typedef struct {
     int16_t scene;
     vec3s_t pos;
     int16_t angle;
} z64_horse_data;

typedef struct {
     vec3f_t pos;
     int16_t yaw;
     int16_t player_params;
     int16_t entrance_index;
     uint8_t room_index;
     int8_t data;
     uint32_t temp_swch_flags;
     uint32_t temp_collect_flags;
} z64_respawn_data;


typedef struct {
     int32_t entrance_index;
     int32_t link_age;
     int32_t cutscene_index;
     uint16_t day_time;
     int32_t night_flag;
     int32_t unk_14;
     int32_t unk_18;
     char newf[6];
     int16_t deaths;
     char player_name[8];
     int16_t n64dd_flag;
     int16_t health_capacity;
     int16_t health;
     int8_t magic_level;
     int8_t magic;
     int16_t rupees;
     uint16_t bgs_hits_left;
     uint16_t navi_timer;
     uint8_t magic_acquired;
     char adult_sword_id[0x0001];
     uint8_t double_magic;
     uint8_t double_defense;
     int8_t bgs_flag;
     z64_item_equips child_equips;
     z64_item_equips adult_equips;
     char unk_54[0x0014];
     z64_item_equips equips;
     char unk_72[0x0002];
     uint8_t items[24];
     int8_t ammo[16];
     uint16_t equipment;
     uint32_t upgrades;
     uint32_t quest_items;
     uint8_t dungeon_items[20];
     int8_t dungeon_keys[19];
     int8_t defense_hearts;
     int16_t gs_tokens;
     z64_save_scene_flags scene_flags[124];
     struct {
       int32_t pos[3];
       int32_t yaw;
       int32_t player_params;
       int32_t entrance_index;
       int32_t room_index;
       int32_t set;
       int32_t temp_swch_flags;
       int32_t temp_collect_flags;
     }fw;
     char unk_E8C[0x0010];
     uint8_t gs_flags[24];
     char unk_EB4[0x0010];
     int32_t unk_EC4;
     char unk_EC8[0x000C];
     uint16_t event_chk_inf[14];
     uint16_t item_get_inf[4];
     uint16_t inf_table[30];
     char unk_F34[0x0004];
     uint32_t world_map_area_data;
     char unk_F3C[0x040C];
     z64_horse_data horse_data;
     uint16_t checksum;
     int32_t file_num;
     char unk_1358[0x0004];
     int32_t game_mode;
     int32_t scene_setup_index;
     int32_t respawn_flag;
     z64_respawn_data respawn[3];
     char unk_13BC[0x0008];
     int16_t dog_params;
     uint8_t unk_13C6;
     uint8_t unk_13C7;
     int16_t nayrus_love_timer;
     char unk_13CA[0x0002];
     int16_t rupee_accumulator;
     int16_t timer1_state;
     int16_t timer1_value;
     int16_t timer2_state;
     int16_t timer2_value;
     int16_t timer_x[2];
     int16_t timer_y[2];
     char unk_13DE[0x0002];
     uint8_t seq_index;
     uint8_t night_seq_index;
     uint8_t button_status[5];
     uint8_t unk_13E7;
     uint16_t unk_13E8;
     uint16_t unk_13EA;
     uint16_t unk_13EC;
     uint16_t unk_13EE;
     int16_t unk_13F0;
     int16_t unk_13F2;
     int16_t unk_13F4;
     int16_t unk_13F6;
     int16_t unk_13F8;
     uint16_t event_inf[4];
     uint16_t map_index;
     uint16_t minigame_state;
     uint16_t minigame_score;
     char unk_1408[0x0001];
     uint8_t language;
     uint8_t audio_setting;
     char unk_140B[0x0001];
     uint8_t z_targeting_setting;
     uint16_t unk_140D;
     uint8_t unk_1410;
     uint8_t unk_1411;
     uint16_t next_cutscene_index;
     uint8_t cutscene_trigger;
     uint8_t chamber_cutscene_cum;
     uint16_t next_day_time;
     uint8_t fade_duration;
     uint8_t unk_1419;
     uint16_t environment_time;
     uint8_t dog_is_lost;
     uint8_t next_transition;
     char unk_141E[0x0002];
     int16_t world_map_area;
     int16_t unk_1422;
     int16_t health_accumulator;
} z64_save_context_t;
# 1497 "/opt/n64/mips64/include/z64ovl/oot/types.h" 3
enum dynapoly_move_flag {
  DPM_NONE = 0b00,
 DPM_PLAYER = 0b01,
  DPM_ENEMY = 0b10
};
# 10 "/opt/n64/mips64/include/z64ovl/oot/u10.h" 2 3
# 29 "/opt/n64/mips64/include/z64ovl/oot/u10.h" 3
# 1 "/opt/n64/mips64/include/z64ovl/oot/shared.h" 1 3
# 30 "/opt/n64/mips64/include/z64ovl/oot/u10.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 1 3



# 1 "/opt/n64/mips64/include/z64ovl/h/ichain.h" 1 3
# 9 "/opt/n64/mips64/include/z64ovl/h/ichain.h" 3
# 1 "/opt/n64/lib/gcc/mips64/9.2.0/include/stddef.h" 1 3 4
# 143 "/opt/n64/lib/gcc/mips64/9.2.0/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 209 "/opt/n64/lib/gcc/mips64/9.2.0/include/stddef.h" 3 4
typedef unsigned int size_t;
# 321 "/opt/n64/lib/gcc/mips64/9.2.0/include/stddef.h" 3 4
typedef int wchar_t;
# 10 "/opt/n64/mips64/include/z64ovl/h/ichain.h" 2 3




enum ichain_types
{
 ICHAIN_U8 = 0
 , ICHAIN_S8
 , ICHAIN_U16
 , ICHAIN_S16
 , ICHAIN_U32
 , ICHAIN_S32
 , ICHAIN_F
 , ICHAIN_Fdiv1000
 , ICHAIN_VEC3F
 , ICHAIN_VEC3Fdiv1000
 , ICHAIN_VEC3S16
};
# 5 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/common.h" 1 3







enum mtxmod
{
 MTXMOD_NEW = 0
 , MTXMOD_APPLY = 1
};
# 6 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/oldnames.h" 1 3
# 7 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 2 3
# 1 "/opt/n64/mips64/include/z64ovl/real.h" 1 3
# 14 "/opt/n64/mips64/include/z64ovl/real.h" 3
extern void _z_skelanime_draw(
z64_global_t* gl
, void* limb_index
, void* dtstart
, int32_t callback0(
 z64_global_t* gl
 , int32_t limb
 , uint32_t* dlist
 , vec3f_t* translation
 , vec3s_t* rotation
 , void* instance
 )
, void callback1(
 z64_global_t* gl
 , int32_t limb
 , uint32_t dlist
 , vec3s_t* rotation
 , void* instance
 )
, void* instance
);



  asm("_z_skelanime_draw = 0x8008993C");
# 51 "/opt/n64/mips64/include/z64ovl/real.h" 3
extern
void
_z_skelanime_draw_mtx(
  z64_global_t *global
, void* limb_index
, void* adt
, uint8_t limb_dlists_count
, int32_t callback0(
   z64_global_t *global
 , int limb
 , uint32_t *dlist
 , vec3f_t *translation
 , vec3s_t *rotation
 , void *entity
  )
, void callback1(
   z64_global_t *global
 , int limb
 , uint32_t dlist
 , vec3s_t *rotation
 , void *entity
  )
, void *entity
);



 asm("_z_skelanime_draw_mtx = 0x80089D8C");
# 88 "/opt/n64/mips64/include/z64ovl/real.h" 3
extern void _z_skelanime_init(
z64_global_t* gl
, z64_skelanime_t* sk
, uint32_t skeleton
, uint32_t anim
, vec3s_t* dt_rot
, vec3s_t* dt_pos
, uint32_t nlimb
);



  asm("_z_skelanime_init = 0x8008C684");
# 111 "/opt/n64/mips64/include/z64ovl/real.h" 3
extern void _z_skelanime_mtx_init(
z64_global_t* gl
, z64_skelanime_t* sk
, uint32_t skeleton
, uint32_t anim
, vec3s_t* dt_rot
, vec3s_t* dt_pos
, uint32_t nlimb
);



  asm("_z_skelanime_mtx_init = 0x8008C788");
# 8 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 2 3
# 67 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_file_load(void *req);



 asm("z_file_load = 0x80000B0C");
# 81 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern uint32_t load_data_from_rom(
 void* vram_addr
 , void* vrom_addr
 , uint32_t size




);
# 98 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
  asm("load_data_from_rom = 0x80000DF0");





extern int32_t z_sprintf(volatile char* dst, const char* fmt, ...);



  asm("z_sprintf = 0x800CE7B4");





extern void osWritebackDCache(void *start, unsigned size);



  asm("osWritebackDCache = 0x80003440");





extern void osInvalICache(void *start, unsigned size);



  asm("osInvalICache = 0x800041A0");
# 137 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void osSendMesg(OSMesgQueue* queue, void* dest, int32_t flag);



  asm("osSendMesg = 0x80001E20");







extern void z_bzero(void *dst, const int num);



  asm("z_bzero = 0x80002E80");




extern int _Printf(
 void *pfn(void *, const char *, size_t), void *arg, const char *fmt, ...);



  asm("_Printf = 0x800D1D00");


extern int _Putfld(
          void *px, void *pap, char code, char *ac);



  asm("_Putfld = 0x800D1690");




extern const uint8_t* z_strchr(const char* str, int32_t ch);
# 185 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern size_t z_strlen(const char* str);
# 195 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void osCreateMesgQueue(OSMesgQueue* queue, OSMesg* mesg, int32_t flag);



  asm("osCreateMesgQueue = 0x80004220");





extern void osRecvMesg(OSMesgQueue* queue, OSMesg* mesq, int32_t flag);



  asm("osRecvMesg = 0x80002030");







extern int z_bcmp(const void *s1, const void *s2, int n);



  asm("z_bcmp = 0x800D4390");
# 232 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_bcopy(const void *src, void *dst, const uint32_t num);



  asm("z_bcopy = 0x80004DC0");
# 276 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void (z_assert_message)(char *mesg, char *fn, int line);



  asm("z_assert_message = 0x800A01B8");







extern void z_console_log(const char *msg, ...);
# 297 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
  asm("z_console_log = 0x800ADBF8");
# 306 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void (z_thread_log_id)(const char* name, int32_t line);
# 318 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void (z_thread_hungup)(const char* name, int32_t line);



  asm("z_thread_hungup = 0x80001B38");







extern void z_item_drop(
z64_global_t* gl
, vec3f_t* position
, uint16_t id
);



  asm("z_item_drop = 0x80013678");
# 347 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_item_drop_2(
z64_global_t* gl
, vec3f_t* position
, uint16_t id
);



 asm("z_item_drop_2 = 0x800138B0");






extern void z_item_drop_random(
z64_global_t* gl
, z64_actor_t* a
, vec3f_t* position
, uint32_t id
);



  asm("z_item_drop_random = 0x80013A84");
# 380 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_eff_blure_vertex_add(z64_eff_blure_t* blureInstance, vec3f_t* p1, vec3f_t* p2);



  asm("z_eff_blure_vertex_add = 0x80013F30");






extern void z_eff_blure_space_add(z64_eff_blure_t* blureInstance);



  asm("z_eff_blure_space_add = 0x80014254");






extern void external_func_80026230(z64_global_t* gl, rgba8_t* color, int16_t a2, int16_t a3);



  asm("external_func_80026230 = 0x8001A0E0");






extern void external_func_80026608(z64_global_t* gl);



  asm("external_func_80026608 = 0x8001A468");






extern void external_func_80026690(z64_global_t* gl, rgba8_t* color, int16_t a2, int16_t a3);



  asm("external_func_80026690 = 0x8001A4AC");






extern void external_func_80026860(z64_global_t* gl, rgba8_t* color, int16_t a2, int16_t a3);



  asm("external_func_80026860 = 0x8001A654");






extern void external_func_80026A6C(z64_global_t* gl);



  asm("external_func_80026A6C = 0x8001A83C");






extern void* z_eff_index_get(uint32_t idx);



  asm("z_eff_index_get = 0x8001A890");






extern void z_effect_add(z64_global_t* gl, int32_t* idx, int32_t type, uint8_t arg3, uint8_t arg4, void* initParams);



  asm("z_effect_add = 0x8001AA5C");






extern void z_effect_remove(z64_global_t *gl, uint32_t index);



  asm("z_effect_remove = 0x8001AE04");
# 492 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_particle_kill(void* particle_instance);



  asm("z_particle_kill = 0x8001B1A4");
# 505 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_particle_insert(z64_global_t* gl, void* particle_instance);



  asm("z_particle_insert = 0x8001B3D0");







extern void external_func_80027DD4(int16_t a0, int16_t a1, int32_t a2);



  asm("external_func_80027DD4 = 0x8001B8FC");







extern void external_func_80027F80(void);



  asm("external_func_80027F80 = 0x8001BAA0");






extern void z_effect_spawn_dust_a(z64_global_t* globalCtx, vec3f_t* pos, vec3f_t* velocity, vec3f_t* accel, rgba8_t* primColor,
                   rgba8_t* envColor, int16_t scale, int16_t scaleStep);



  asm("z_effect_spawn_dust_a = 0x8001BD94");






extern void external_func_8002836C(z64_global_t* globalCtx, vec3f_t* pos, vec3f_t* velocity, vec3f_t* accel, rgba8_t* primColor,
                   rgba8_t* envColor, int16_t scale, int16_t scaleStep, int16_t life);



  asm("external_func_8002836C = 0x8001BE64");





extern void external_func_800283D4(z64_global_t* globalCtx, vec3f_t* pos, vec3f_t* velocity, vec3f_t* accel, rgba8_t* primColor,
                   rgba8_t* envColor, int16_t scale, int16_t scaleStep, int16_t life);



  asm("external_func_800283D4 = 0x8001BECC");






extern void external_func_8002843C(void);



  asm("external_func_8002843C = 0x8001BF34");







extern void z_effect_spawn_dust_4(
z64_global_t* gl
, vec3f_t* position
, vec3f_t* velocity
, vec3f_t* acceleration
, int16_t scale
, int16_t scaleStep
);



  asm("z_effect_spawn_dust_4 = 0x8001C154");






extern void z_effect_spawn_dust_5(
z64_global_t* gl
, vec3f_t* position
, vec3f_t* velocity
, vec3f_t* acceleration
, int16_t scale
, int16_t scaleStep
);



  asm("z_effect_spawn_dust_5 = 0x8001C1C4");
# 625 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8002873C(void);



  asm("external_func_8002873C = 0x8001C234");






extern void external_func_800287AC(void);



  asm("external_func_800287AC = 0x8001C2A4");






extern void external_func_80028990(void);



  asm("external_func_80028990 = 0x8001C488");






extern void external_func_80028A54(void);



  asm("external_func_80028A54 = 0x8001C54C");






extern void external_func_80028B18(void);



  asm("external_func_80028B18 = 0x8001C610");






extern void z_effect_spawn_sparkle(z64_global_t* gl, vec3f_t* a1, void* a2, void* a3, rgba8_t a, rgba8_t b);



  asm("z_effect_spawn_sparkle = 0x8001C66C");






extern void external_func_80028BB0(void);



  asm("external_func_80028BB0 = 0x8001C6A8");






extern void external_func_80028CEC(void);



  asm("external_func_80028CEC = 0x8001C7E4");





extern void z_effect_spawn_bomb2(
z64_global_t* gl
, vec3f_t* position
, vec3f_t* burst_gravity
, vec3f_t* burst_velocity
, uint16_t scale
, int16_t growth_velocty
);



  asm("z_effect_spawn_bomb2 = 0x8001C97C");
# 732 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_80028F84(void);



  asm("external_func_80028F84 = 0x8001CA7C");






extern void z_effect_spawn_blast_ring(z64_global_t* gl, vec3f_t* position, vec3f_t* grav, vec3f_t* u0);



  asm("z_effect_spawn_blast_ring = 0x8001CB1C");







extern void z_effect_spawn_spark(z64_global_t* gl, z64_actor_t* a, vec3f_t* pos, vec3f_t* grav, vec3f_t* u0);



  asm("z_effect_spawn_spark = 0x8001CC7C");






extern void z_effect_spawn_fire_breath(void);



  asm("z_effect_spawn_fire_breath = 0x8001CE98");
# 779 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_bubble(z64_global_t* gl, vec3f_t* pos, float a, float b, float c, float d);



  asm("z_effect_spawn_bubble = 0x8001CEDC");
# 792 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_water_ripple(z64_global_t* global, vec3f_t* pos, int32_t unk0, int32_t unk1, int32_t unk2);



  asm("z_effect_spawn_water_ripple = 0x8001CF3C");
# 805 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_water_splash(
 z64_global_t *global, vec3f_t *pos,
 int32_t unk0, int32_t unk1, int32_t unk2, int32_t unk3
);



  asm("z_effect_spawn_water_splash = 0x8001CF94");
# 821 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_magma(void);



  asm("z_effect_spawn_magma = 0x8001D028");






extern void z_effect_spawn_lightning(z64_global_t *global, vec3f_t *position, uint32_t *opacity, uint32_t *color, uint16_t size);



        asm("z_effect_spawn_lightning= 0x8001D098");





extern void z_effect_spawn_dt_bubble_0(
z64_global_t* gl
, vec3f_t* position
, vec3f_t* velocity
, vec3f_t* acceleration
, int16_t drop_scale
, int16_t sp14
, int16_t color
, int16_t sp1C
);



 asm("z_effect_spawn_dt_bubble_0 = 0x8001D110");
# 864 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_80029694(void);



  asm("external_func_80029694 = 0x8001D18C");







extern void z_effect_spawn_hahen(
z64_global_t* gl
, vec3f_t* position
, vec3f_t* velocity
, vec3f_t* acceleration
, int16_t xr, int16_t yr, int16_t zr
, int16_t sp20
, int32_t sp24
);



  asm("z_effect_spawn_hahen = 0x8001D21C");
# 897 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_hahen_n(
z64_global_t* gl
, vec3f_t* position
, float y_speed
, int16_t a3
, int16_t srand_offset
, int16_t srand_range
, int16_t count
, int16_t sp20
, int16_t sp24
, int32_t sp28
);



  asm("z_effect_spawn_hahen_n = 0x8001D29C");
# 921 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_splash(z64_global_t* gl, vec3f_t* pos);



  asm("z_effect_spawn_splash = 0x8001D4A8");






extern void z_effect_spawn_magma2(void);



  asm("z_effect_spawn_magma2 = 0x8001D68C");






extern void z_effect_spawn_stone1(void);



  asm("z_effect_spawn_stone1 = 0x8001D6FC");





extern void z_effect_spawn_hitmark(z64_global_t* gl, int32_t a, vec3f_t* pos);



  asm("z_effect_spawn_hitmark = 0x8001D7A8");






extern void external_func_80029CC8(void);



  asm("external_func_80029CC8 = 0x8001D7CC");






extern void external_func_80029CF0(void);



  asm("external_func_80029CF0 = 0x8001D7F8");






extern void external_func_80029D5C(void);



  asm("external_func_80029D5C = 0x8001D864");






extern void z_effect_spawn_k_fire(void);



  asm("z_effect_spawn_k_fire = 0x8001D8C8");





extern void external_func_80029E24(void);



  asm("external_func_80029E24 = 0x8001D930");
# 1035 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_fragment(
 z64_global_t *global,
 vec3f_t *burst_depth_y, vec3f_t *burst_depth_x, vec3f_t *burst_origin,
 int16_t gravity_influence,
 int16_t u0,
 int16_t rotation_speed,
 int16_t burst_velocity,
 int16_t u1,
 int16_t scale,
 int16_t u2,
 int16_t jitter,
 int32_t duration,
 int16_t u3,
 int16_t objno,
 uint32_t dlist
 );



  asm("z_effect_spawn_fragment = 0x8001D998");
# 1063 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8002A140(void);



  asm("external_func_8002A140 = 0x8001DC4C");






extern void external_func_8002A1DC(z64_global_t *gl, void *en, int16_t *unk, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7, uint8_t a8, uint8_t a9, uint32_t a10);



  asm("external_func_8002A1DC = 0x8001DCEC");






extern void external_func_8002A2A4(void);



  asm("external_func_8002A2A4 = 0x8001DDB8");






extern void z_effect_spawn_fire_tail(void);



  asm("z_effect_spawn_fire_tail = 0x8001DED8");






extern void z_effect_spawn_fire(
z64_global_t* gl
, z64_actor_t* a
, vec3f_t* position
, int16_t a3
, int16_t sp10
, int16_t sp14
, int16_t count
);



  asm("z_effect_spawn_fire = 0x8001DFEC");







extern void external_func_8002A54C(void);



  asm("external_func_8002A54C = 0x8001E064");






extern void z_effect_spawn_extra(void);



  asm("z_effect_spawn_extra = 0x8001E110");





extern void z_effect_spawn_flame_circle(
z64_global_t* gl
, z64_actor_t* a
, vec3f_t* position
, uint16_t radius
, uint16_t height
);



  asm("z_effect_spawn_flame_circle = 0x8001E178");
# 1168 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_dead_db(
z64_global_t* gl
, vec3f_t* position
, vec3f_t* a2
, vec3f_t* a3
, uint16_t scale
, uint16_t sp14
, uint8_t smoke_ir, uint8_t smoke_ig, uint8_t smoke_ib
, uint8_t smoke_a
, uint8_t smoke_or, uint8_t smoke_og, uint8_t smoke_ob
, uint16_t sp34
, uint32_t duration
, uint16_t sp3C
);



  asm("z_effect_spawn_dead_db = 0x8001E1D4");
# 1194 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_effect_spawn_dead_dodongo(void);



  asm("z_effect_spawn_dead_dodongo = 0x8001E28C");






extern void z_effect_spawn_dead_deku_scrub(void);



  asm("z_effect_spawn_dead_deku_scrub = 0x8001E428");






extern void z_effect_spawn_dead_sound(z64_global_t* gl, vec3f_t* pos, uint16_t sfx, int16_t u0, int16_t u1, uint32_t u2);



  asm("z_effect_spawn_dead_sound = 0x8001E510");






extern void z_effect_spawn_ice_smoke(void);



  asm("z_effect_spawn_ice_smoke = 0x8001E560");







extern void z_actor_shadow_init(
void* a
, float f0
, void* fdraw
, float radius
);







  asm("z_actor_shadow_init = 0x8001EC20");
  asm("Z_SHADOW_CIRCLE = 0x8001EFF4");
  asm("Z_SHADOW_TEARDROP = 0x8001F280");
# 1268 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void *Z_SHADOW_CIRCLE, *Z_SHADOW_TEARDROP;




extern void external_func_8002BDB0(void);



  asm("external_func_8002BDB0 = 0x8001F74C");







extern int32_t z_flags_switch_get(z64_global_t *global, int32_t flag);



  asm("z_flags_switch_get = 0x8002049C");
# 1299 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_flags_switch_set(z64_global_t *global, int32_t flag);



  asm("z_flags_switch_set = 0x800204D0");
# 1313 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_flags_switch_unset(z64_global_t *global, int32_t flag);



  asm("z_flags_switch_unset = 0x80020510");
# 1328 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_flags_switch_unk_get(z64_global_t *global, int32_t flag);



  asm("z_flags_switch_unk_get = 0x80020554");
# 1341 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_flags_switch_unk_set(z64_global_t *global, int32_t flag);



  asm("z_flags_switch_unk_set = 0x80020588");
# 1354 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_flags_switch_unk_unset(z64_global_t *global, int32_t flag);



  asm("z_flags_switch_unk_unset = 0x800205C8");







extern int32_t z_flags_chest_get(z64_global_t *global, int32_t flag);



  asm("z_flags_chest_get = 0x8002060C");







extern void z_flags_chest_set(z64_global_t *global, int32_t flag);



  asm("z_flags_chest_set = 0x80020624");







extern int32_t z_flags_clear_get(z64_global_t *global, int32_t flag);



  asm("z_flags_clear_get = 0x80020640");







extern void z_flags_clear_set(z64_global_t *global, int32_t flag);



  asm("z_flags_clear_set = 0x80020658");






extern void z_flags_clear_unset(z64_global_t *global, int32_t flag);



  asm("z_flags_clear_unset = 0x80020674");







extern int32_t z_flags_clear_temp_get(z64_global_t *global, int32_t flag);



  asm("z_flags_clear_temp_get = 0x80020694");
# 1439 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_flags_clear_temp_set(z64_global_t *global, int32_t flag);



  asm("z_flags_clear_temp_set = 0x800206AC");
# 1453 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_flags_collect_get(z64_global_t *global, int32_t flag);



  asm("z_flags_collect_get = 0x800206E8");
# 1467 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_flags_collect_set(z64_global_t *global, int32_t flag);



  asm("z_flags_collect_set = 0x8002071C");
# 1482 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_titlecard_boss(z64_global_t *global, z64_global_t *global_plus_0x1D4C, uint32_t texture, int16_t arg3, int16_t arg4, uint8_t arg5, uint8_t arg6);



  asm("z_actor_titlecard_boss = 0x80020780");
# 1499 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_kill(
z64_actor_t* a
);



  asm("z_actor_kill = 0x80020EB4");
# 1516 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_set_height(
z64_actor_t* a
, float height
);



  asm("z_actor_set_height = 0x80020F04");
# 1533 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_set_scale(
z64_actor_t* a
, float scale
);



  asm("z_actor_set_scale = 0x80020F88");
# 1550 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_set_object(z64_global_t *global, z64_actor_t *actor);



  asm("z_actor_set_object = 0x80020FA4");
# 1563 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_update_pos(z64_actor_t *actor);



  asm("z_actor_update_pos = 0x80021124");
# 1577 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_update_vel(z64_actor_t *actor);



  asm("z_actor_update_vel = 0x800211A4");
# 1591 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_move_dir_vel(
z64_actor_t* a
);



  asm("z_actor_move_dir_vel = 0x8002121C");
# 1607 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8002D908(z64_actor_t *actor);



  asm("external_func_8002D908 = 0x80021248");







extern void external_func_8002D97C(z64_actor_t* a);



  asm("external_func_8002D97C = 0x800212B8");







extern void external_func_8002D9A4(z64_actor_t* a, float a1);



  asm("external_func_8002D9A4 = 0x800212E4");





extern int16_t z_actor_math_yaw_actor(
z64_actor_t* a
, z64_actor_t* target
);



  asm("z_actor_math_yaw_actor = 0x8002140C");







extern int16_t z_actor_math_yaw_vec3f(
z64_actor_t* a
, vec3f_t* target
);



  asm("z_actor_math_yaw_vec3f = 0x8002140C");







extern void external_func_8002DAE0(z64_actor_t* a, z64_actor_t* b);



  asm("external_func_8002DAE0 = 0x80021430");





extern void external_func_8002DB28(z64_actor_t* a, vec3f_t* b);



  asm("external_func_8002DB28 = 0x80021488");
# 1694 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float math_distance_xyz_actor_actor(z64_actor_t *a, z64_actor_t *b);



  asm("math_distance_xyz_actor_actor = 0x800214AC");







extern float math_distance_xyz_actor_point(z64_actor_t *a, vec3f_t *b);



  asm("math_distance_xyz_actor_point = 0x800214D8");






extern float math_distance_xz_actor_actor(z64_actor_t *a, z64_actor_t *b);



  asm("math_distance_xz_actor_actor = 0x800214FC");





extern float z_actor_math_dist_xz_vec3f(
z64_actor_t* a
, vec3f_t* target
);



  asm("z_actor_math_dist_xz_vec3f = 0x80021528");
# 1744 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8002DBD0(z64_actor_t *actor, vec3f_t *result, vec3f_t *point);



  asm("external_func_8002DBD0 = 0x8002154C");
# 1757 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_actor_y_distance(z64_actor_t *a, z64_actor_t *b);
# 1767 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8002DD78(z64_player_t* player);



  asm("external_func_8002DD78 = 0x800216F8");






extern void external_func_8002DDE4(z64_global_t* gl);



  asm("external_func_8002DDE4 = 0x80021768");






extern void external_func_8002DDF4(z64_global_t* gl);



  asm("external_func_8002DDF4 = 0x8002177C");





extern void external_func_8002DE04(z64_global_t* gl, z64_actor_t* a, z64_actor_t* b);



  asm("external_func_8002DE04 = 0x80021790");





extern void external_func_8002DEEC(z64_global_t* gl, z64_player_t* Link, z64_actor_t* a);



  asm("external_func_8002DEEC = 0x8002187C");





extern void external_func_8002DF38(z64_global_t* gl, z64_actor_t* a, uint8_t action);



  asm("external_func_8002DF38 = 0x800218C8");
# 1842 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_cutscene_link_action(
 z64_global_t *global
 , z64_actor_t *actor
 , uint8_t action
);



  asm("z_cutscene_link_action = 0x800218EC");





extern void external_func_8002DF90(z64_actor_t* dynapoly_actor);



  asm("external_func_8002DF90 = 0x80021928");





extern void external_func_8002DFC8(z64_actor_t* actor, int16_t a1, z64_global_t* gl);



  asm("external_func_8002DFC8 = 0x80021968");






extern float z_actor_player_in_range(
z64_actor_t* a
, int16_t rot
);



  asm("z_actor_player_in_range = 0x80021A28");







extern int32_t external_func_8002E12C(z64_actor_t* a, float a1, int16_t a2);



  asm("external_func_8002E12C = 0x80021AD4");





extern void external_func_8002E1A8(z64_actor_t* a, z64_actor_t* b, float a2, int16_t a3);



  asm("external_func_8002E1A8 = 0x80021B54");







extern void z_actor_find_bounds(
z64_global_t* gl
, z64_actor_t* a
, float below
, float radius
, float above
, uint32_t flags
);



  asm("z_actor_find_bounds = 0x80021E6C");







extern void * external_func_8002EABC(vec3f_t* object, vec3f_t* eye, vec3f_t* lightDir, z64_gfx_t* gfx_ctxt);



  asm("external_func_8002EABC = 0x800223C8");





extern void external_func_8002EB44(vec3f_t* object, vec3f_t* eye, vec3f_t* lightDir, z64_gfx_t* gfx_ctxt);



  asm("external_func_8002EB44 = 0x80022400");






extern void z_actor_texgen_init(z64_actor_t *a0, z64_global_t *gl, int32_t flag);



  asm("z_actor_texgen_init = 0x80022438");





extern void external_func_8002ED80(z64_actor_t *a0, z64_global_t *gl, int32_t flag);



  asm("external_func_8002ED80 = 0x80022554");





extern void* external_func_8002EF14(void* PosRot, z64_actor_t* actor);



  asm("external_func_8002EF14 = 0x800226A4");
# 1992 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern uint32_t external_func_8002F194(z64_actor_t *actor, z64_global_t *global);



  asm("external_func_8002F194 = 0x80022930");







extern int32_t z_actor_poll_trade_cylinder(z64_actor_t *actor, z64_global_t *, float dist_xz, float dist_y, uint32_t item_index);



  asm("z_actor_poll_trade_cylinder = 0x80022960");
# 2017 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_actor_poll_trade_cube(z64_actor_t *actor, z64_global_t *global, float distance, uint32_t item_index);



  asm("z_actor_poll_trade_cube = 0x80022A34");
# 2031 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_poll_speak_cube(z64_actor_t *actor, z64_global_t *gl, float distance);



  asm("z_actor_poll_speak_cube = 0x80022A68");
# 2044 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8002F2F4(z64_actor_t *actor, z64_global_t *global);



  asm("external_func_8002F2F4 = 0x80022A90");







extern void external_func_8002F334(z64_actor_t* actor, z64_global_t* gl);



  asm("external_func_8002F334 = 0x80022AD0");
# 2069 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_actor_player_trade_item_get(z64_global_t *global);



  asm("z_actor_player_trade_item_get = 0x80022B04");





extern void external_func_8002F374(z64_global_t *global, z64_actor_t *actor, int16_t *unk0, int16_t *unk1);



  asm("external_func_8002F374 = 0x80022B14");
# 2093 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_actor_is_attached(
z64_actor_t* a
);



  asm("z_actor_is_attached = 0x80022BB0");
# 2112 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_give_item(
 z64_actor_t *actor,
 z64_global_t *global,
 uint32_t get_item_id,
 float range_xz, float range_y
);



  asm("z_actor_give_item = 0x80022BD4");
# 2134 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_give_item_50_10(
z64_actor_t* a
, z64_global_t* gl
, uint32_t id
);



  asm("z_actor_give_item_50_10 = 0x80022CF4");
# 2157 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_give_id_0(z64_actor_t *actor, z64_global_t *global);



  asm("z_actor_give_id_0 = 0x80022D20");





extern int32_t z_actor_is_attached2(z64_actor_t* a);



  asm("z_actor_is_attached2 = 0x80022D40");





extern void external_func_8002F5C4(z64_player_t* Link, z64_actor_t* a);



  asm("external_func_8002F5C4 = 0x80022D64");





extern void external_func_8002F5F0(z64_actor_t* actor, z64_global_t* gl);



  asm("external_func_8002F5F0 = 0x80022D94");





extern int32_t external_func_8002F618(z64_global_t* gl, z64_actor_t* a);



  asm("external_func_8002F618 = 0x80022DBC");





extern int32_t external_func_8002F63C(z64_global_t* gl, z64_actor_t* a, int32_t a2);



  asm("external_func_8002F63C = 0x80022DE0");





extern int32_t external_func_8002F674(z64_global_t* gl, z64_actor_t* a);



  asm("external_func_8002F674 = 0x80022E18");






extern void external_func_8002F698(z64_global_t* gl, uint32_t a1, float a2, int16_t a3, float a4, uint32_t a5, uint32_t a6);



  asm("external_func_8002F698 = 0x80022E3C");





extern void Player_SetBootData(z64_global_t *gl, z64_player_t *p);



  asm("Player_SetBootData = 0x80079200");





extern void external_func_8002F6D4(z64_global_t* gl, uint32_t a1, float a2, int16_t a3, float a4, uint32_t a5);



  asm("external_func_8002F6D4 = 0x80022E7C");
# 2261 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_player_knockback(z64_global_t *gl, z64_actor_t* a, float distance, int16_t direction, float height);



  asm("z_player_knockback = 0x80022EC4");





extern void external_func_8002F758(z64_global_t *gl, void *gl830, float a, float b, float *c, void *unk);



  asm("external_func_8002F758 = 0x80022F00");







extern void external_func_8002F7A0(z64_global_t* gl, uint32_t a1, float a2, int16_t a3, float a4);



  asm("external_func_8002F7A0 = 0x80022F48");
# 2297 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_play_sfx(z64_actor_t *actor, uint16_t sound_id);



  asm("z_actor_play_sfx = 0x80022F84");







extern void z_actor_play_sfx2(
z64_actor_t* a
, uint16_t sfx
);



  asm("z_actor_play_sfx2 = 0x80022FD0");
# 2325 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8002F850(z64_global_t* gl, z64_actor_t* a);



  asm("external_func_8002F850 = 0x80022FFC");






extern void sound_play_actor3(z64_actor_t *actor, uint16_t sound_id);



  asm("sound_play_actor3 = 0x800230A0");





extern void external_func_8002F948(z64_actor_t *actor, uint16_t sound_id);



  asm("external_func_8002F948 = 0x80023108");





extern void z_actor_play_sfx_flag(z64_actor_t *actor, uint16_t sound_id);



  asm("z_actor_play_sfx_flag = 0x8002313C");





extern void external_func_8002F994(z64_actor_t *actor, uint16_t sound_id);



  asm("external_func_8002F994 = 0x80023164");





extern void external_func_8002F9EC(z64_global_t* gl, z64_actor_t* a, void* a2, void* a3, void* a4);



  asm("external_func_8002F9EC = 0x800231BC");
# 2390 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_set_draw_distance(z64_global_t *global, z64_actor_t *actor, void *a2 , float *a3 );



  asm("z_actor_set_draw_distance = 0x800249DC");







extern z64_actor_t* z_actor_spawn(
z64_actor_context_t* actor_ctxt
, z64_global_t *gl
, int16_t id
, float x, float y, float z
, int16_t xr, int16_t yr, int16_t zr
, uint16_t variable
);



  asm("z_actor_spawn = 0x80025110");
# 2426 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern z64_actor_t* z_actor_spawn_attached(
z64_actor_context_t* actor_ctxt
, z64_actor_t* host
, z64_global_t *gl
, int16_t id
, float x, float y, float z
, int16_t xr, int16_t yr, int16_t zr
, uint16_t variable
);



  asm("z_actor_spawn_attached = 0x800253F0");
# 2447 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern z64_actor_t* z_actor_find(z64_actor_context_t* ctxt, int32_t id, int32_t type);



  asm("z_actor_find = 0x80025B0C");





extern void z_actor_play_sound_defeated(
z64_global_t* gl
, z64_actor_t *a
);



  asm("z_actor_play_sound_defeated = 0x80025B4C");







extern void external_func_80032E24(void* a0, int32_t a1, z64_global_t* gl);



  asm("external_func_80032E24 = 0x80025D04");





extern void external_func_80032F54(int32_t *a0, uint8_t limb, int32_t a2, int32_t a3, int32_t a4, uint32_t dlist, int32_t a6);



  asm("external_func_80032F54 = 0x80025DFC");





extern void external_func_8003305C(void);



  asm("external_func_8003305C = 0x80025F04");





extern void external_func_80033260(void);



  asm("external_func_80033260 = 0x800260E8");






extern void external_func_80033480(
 z64_global_t *global,
 vec3f_t *pos,
 float radius,
 int32_t particle_count,
 int16_t scale_a,
 int16_t scale_b,
 int8_t type
 );



  asm("external_func_80033480 = 0x80026308");
# 2534 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern z64_actor_t* z_actor_test_explosive(z64_global_t *global, z64_collider_t* col);



  asm("z_actor_test_explosive = 0x800264C8");







extern int32_t z_find_explosive(z64_global_t *global, void *explosive);



  asm("z_find_explosive = 0x8002650C");






extern void z_actor_type_change(
z64_global_t* gl
, void* actor_ctxt
, z64_actor_t* a
, uint8_t type
);



  asm("z_actor_type_change = 0x800265D4");







extern z64_actor_t* external_func_80033780(z64_global_t* gl, z64_actor_t* a, float a2);



  asm("external_func_80033780 = 0x80026614");






extern void z_actor_set_text_scene(z64_global_t* gl, z64_actor_t* actor, int16_t text_id);



  asm("z_actor_set_text_scene = 0x800267D4");





extern int16_t external_func_800339B8(z64_actor_t* actor, z64_global_t* gl, float a2, int16_t a3);



  asm("external_func_800339B8 = 0x80026850");







extern int32_t external_func_80033A84(z64_global_t* gl, z64_actor_t* a);



  asm("external_func_80033A84 = 0x8002691C");







extern int32_t external_func_80033AB8(z64_global_t* gl, z64_actor_t* a);



  asm("external_func_80033AB8 = 0x80026950");





extern float external_func_80033AEC(vec3f_t* a0, vec3f_t* a1, float a2, float a3, float a4, float a5);



  asm("external_func_80033AEC = 0x80026984");






extern void z_actor_shadow_draw_vec3f(
vec3f_t* pos
, vec3f_t* scale
, uint32_t opacity
, z64_global_t* gl
);



  asm("z_actor_shadow_draw_vec3f = 0x80026AD0");







extern void external_func_80033DB8(z64_global_t* gl, int16_t a1, int16_t a2);



  asm("external_func_80033DB8 = 0x80026C1C");





extern void external_func_80033E1C(z64_global_t* gl, int16_t a1, int16_t a2, int16_t a3);



  asm("external_func_80033E1C = 0x80026C84");





extern void external_func_80033E88(z64_actor_t* actor, z64_global_t* gl, int16_t a2, int16_t a3);



  asm("external_func_80033E88 = 0x80026CF4");






extern float z_math_frand(float n);



  asm("z_math_frand= 0x80026D64");
# 2701 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_math_frand_center(float n);



  asm("z_math_frand_center = 0x80026D90");
# 2714 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_80033F54(z64_global_t* gl, int32_t a1, int32_t a2);



  asm("external_func_80033F54 = 0x80026DC8");






extern void external_func_8003424C(z64_global_t* gl, vec3f_t* arg1);



  asm("external_func_8003424C = 0x80027070");







extern void z_actor_damage_color(
z64_actor_t* a
, int16_t a1
, int16_t a2
, int16_t a3
, int16_t timer
);



  asm("z_actor_damage_color = 0x80027090");
# 2760 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8003435C(vec3f_t* object, z64_global_t* gl);



  asm("external_func_8003435C = 0x80027188");





extern int32_t external_func_800343CC(z64_global_t* gl, z64_actor_t* a, int16_t* a2, uint16_t (*unkFunc1)(z64_global_t*, z64_actor_t*), int16_t (*unk_Func2)(z64_global_t*, z64_actor_t*));



 asm("external_func_800343CC = 0x800271FC");





extern int16_t external_func_800347E8(int16_t a0);



  asm("external_func_800347E8 = 0x80027620");





extern void external_func_80034A14(z64_actor_t* actor, void* a1, int16_t a2, int16_t a3);



  asm("external_func_80034A14 = 0x80027854");
# 2804 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_draw_mtx_alpha_opa(z64_global_t *global, z64_skelanime_t *skelanime, void *internal0, void *internal1, z64_actor_t *actor, int16_t opacity);



  asm("z_skelanime_draw_mtx_alpha_opa = 0x800279CC");
# 2818 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_draw_mtx_alpha_xlu(z64_global_t *global, z64_skelanime_t *skelanime, void *internal0, void *internal1, z64_actor_t *actor, int16_t opacity);



  asm("z_skelanime_draw_mtx_alpha_xlu = 0x80027AC4");






extern float external_func_80034DD4(z64_actor_t* actor, z64_global_t* gl, float a2, float a3);



  asm("external_func_80034DD4 = 0x80027BA8");






extern void external_func_80034EC0(z64_skelanime_t* skl, void* a1, int32_t a2);



  asm("external_func_80034EC0 = 0x80027C98");





extern void external_func_80034F54(z64_global_t* gl, int16_t* a1, int16_t* a2, int32_t a3);



  asm("external_func_80034F54 = 0x80027D30");
# 2863 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_cheap_proc_draw_opa(
z64_global_t* gl
, uint32_t dl
);



 asm("z_cheap_proc_draw_opa = 0x80028048");
# 2881 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_cheap_proc_draw_xlu(
z64_global_t* gl
, uint32_t dl
);



 asm("z_cheap_proc_draw_xlu = 0x800280C8");
# 2899 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern z64_actor_t* z_actor_detect_nearest(z64_global_t *global, z64_actor_t *actor, int16_t actor_id, z64_actor_type_t type, float range);



  asm("z_actor_detect_nearest = 0x80028158");







extern int32_t external_func_800354B4(z64_global_t* gl, z64_actor_t *actor, float range, int16_t a3, int16_t a4, int16_t a5);



  asm("external_func_800354B4 = 0x8002821C");





extern void external_func_8003555C(z64_global_t* gl, vec3f_t* a1, vec3f_t* a2, vec3f_t* a3);



  asm("external_func_8003555C = 0x800282C4");





extern void external_func_800355B8(z64_global_t* gl, vec3f_t* a1);



  asm("external_func_800355B8 = 0x80028320");






extern uint8_t external_func_800355E4(z64_global_t* gl, z64_collider_t* collider);



  asm("external_func_800355E4 = 0x8002834C");






extern uint8_t z_actor_update_health(
z64_actor_t* a
);



  asm("z_actor_update_health = 0x80028390");







extern void z_actor_is_frozen(
z64_actor_t* a
, z64_collider_body_t* collider
, int32_t is_frozen
);



  asm("z_actor_is_frozen = 0x800283BC");







extern void z_actor_is_frozen_jntsphs(
z64_actor_t* a
, void* jntsphs
, int32_t is_frozen
);



  asm("z_actor_is_frozen_jntsphs = 0x800284A8");
# 3000 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_func_80035844(vec3f_t* a0, vec3f_t* a1, int16_t* a2, int32_t a3);



  asm("z_actor_func_80035844 = 0x800285B0");





extern void external_func_800358DC(z64_actor_t* host, vec3f_t* pos, vec3s_t* rot, float* physics, int16_t a, int32_t b, z64_global_t* gl, int16_t variable, int32_t c);



  asm("external_func_800358DC = 0x80028644");





extern void external_func_800359B8(z64_actor_t* actor, int16_t a1, vec3s_t* a2);



  asm("external_func_800359B8 = 0x80028720");







extern int32_t z_flags_event_get(int32_t flag);



  asm("z_flags_event_get = 0x800288B4");







extern void z_flags_event_set(int32_t flag);



  asm("z_flags_event_set = 0x800288E0");







extern int32_t z_flags_inf_table_get(int32_t flag);



  asm("z_flags_inf_table_get = 0x80028914");







extern void z_flags_inf_table_set(int32_t flag);



  asm("z_flags_inf_table_set = 0x80028940");







extern void external_func_80037C30(z64_global_t* gl, int16_t a1);



  asm("external_func_80037C30 = 0x8002A9AC");







extern void external_func_80037D98(z64_global_t* gl, z64_actor_t* a, int16_t a2, int32_t* a3);



  asm("external_func_80037D98 = 0x8002AB20");





  extern int32_t z_actor_vector_focus_main(z64_actor_t* actor, vec3f_t* targetVector, vec3s_t* headVector, vec3s_t* waistVector);



    asm("z_actor_vector_focus_main = 0xDEADBEEF");







extern int32_t z_actor_vector_focus(z64_global_t* gl, z64_actor_t* actor, vec3s_t* headVector, vec3s_t* waistVector, vec3f_t arg4);



  asm("z_actor_vector_focus = 0x8002B024");





extern void z_bg_poly_mtxf_init(
z64_col_poly_t* poly
, vec3f_t* x, vec3f_t* y, vec3f_t* z
, float* mf
);



  asm("z_bg_poly_mtxf_init = 0x8002B668");







extern void external_func_8003C890(void);



  asm("external_func_8003C890 = 0x8002F3A4");





extern float external_func_8003C940(void *col_ctxt, void *floorpoly, void *unk_sp2C, z64_actor_t *actor, vec3f_t *pos);



  asm("external_func_8003C940 = 0x8002F454");
# 3166 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_bgcheck_raycast(z64_col_ctxt_t* col_ctxt, void *unk0, void *unk1, z64_actor_t *actor, vec3f_t *pos);





  asm("z_bgcheck_raycast = 0x8002F4B8");






extern void external_func_8003CA0C(z64_global_t* gl, z64_col_ctxt_t* col_ctxt, void** poly, uint32_t* a, z64_actor_t* actor, vec3f_t* b);



  asm("external_func_8003CA0C = 0x8002F520");





extern void external_func_8003CA64(void);



  asm("external_func_8003CA64 = 0x8002F578");





extern void external_func_8003D464(void);



  asm("external_func_8003D464 = 0x8002FF1C");





extern void external_func_8003DE84(void);



  asm("external_func_8003DE84 = 0x800308B4");







extern void external_func_8003DF10(void);



  asm("external_func_8003DF10 = 0x80030940");





extern void external_func_8003DFA0(void);



  asm("external_func_8003DFA0 = 0x800309D0");





extern void external_func_8003E02C(void);



  asm("external_func_8003E02C = 0x80030A5C");





extern void external_func_8003E0B8(void);



  asm("external_func_8003E0B8 = 0x80030AE8");





extern void external_func_8003E0FC(void);



  asm("external_func_8003E0FC = 0x80030B2C");






extern int32_t z_collision_sphere_test(z64_col_ctxt_t *gcollision, vec3f_t *point, float radius);



  asm("z_collision_sphere_test = 0x80030D08");
# 3285 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern uint32_t z_dynapoly_actor_set(z64_global_t *global, void *global_plus_0x810, z64_actor_t *actor, uint32_t dynacollision);



  asm("z_dynapoly_actor_set = 0x800313A4");
# 3301 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_dynapoly_actor_get(z64_global_t *gl, uint32_t dynapolyid);



  asm("z_dynapoly_actor_get = 0x80031464");







extern void external_func_8003EBF8(z64_global_t *global, void *global_plus_0x810, uint32_t dynapoly_id);



  asm("external_func_8003EBF8 = 0x800314D8");







extern void external_func_8003EC50(z64_global_t *gl, void *gl880, uint32_t *collision);;



  asm("external_func_8003EC50 = 0x80031530");







extern void external_func_8003ECA8(void);



  asm("external_func_8003ECA8 = 0x80031588");
# 3350 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_dynapoly_free(z64_global_t *global, void *global_plus_0x810, uint32_t dynacollision_id);



  asm("z_dynapoly_free = 0x80031638");







extern void external_func_8003EE6C(void);



  asm("external_func_8003EE6C = 0x800316C0");
# 3376 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_dynapoly_alloc(const uint32_t collision, void *collision_pointer);



  asm("z_dynapoly_alloc = 0x80033EF4");
# 3393 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern uint32_t get_collision_polytype(z64_col_ctxt_t *collision_cotext, void *Polygon, uint16_t mesh, bool word);



  asm("get_collision_polytype = 0x80034028");







extern void external_func_80041D4C(void);



  asm("external_func_80041D4C = 0x800343D4");






extern void external_func_80041DB8(void);



  asm("external_func_80041DB8 = 0x8003444C");






extern void external_func_80041EA4(void);



  asm("external_func_80041EA4 = 0x80034540");






extern void external_func_80041EEC(void);



  asm("external_func_80041EEC = 0x80034590");





extern void external_func_80041F34(void);



  asm("external_func_80041F34 = 0x800345DC");






extern void external_func_80041FE8(void);



  asm("external_func_80041FE8 = 0x8003469C");





extern void external_func_80042048(void);



  asm("external_func_80042048 = 0x80034700");






extern uint32_t get_collision_conveyor_speed(z64_col_ctxt_t *collision_cotext, void *Polygon, uint16_t mesh);



  asm("get_collision_conveyor_speed = 0x80034778");






extern uint32_t get_collision_conveyor_direction(z64_col_ctxt_t *collision_cotext, void *Polygon, uint16_t mesh);



  asm("get_collision_conveyor_direction = 0x800347A0");





extern void external_func_8004213C(void);



  asm("external_func_8004213C = 0x800347FC");





extern void external_func_80042244(void);



  asm("external_func_80042244 = 0x80034908");






extern void external_func_8004239C(void);



  asm("external_func_8004239C = 0x80034A60");





extern void external_func_800433A4(void);



  asm("external_func_800433A4 = 0x80035180");





extern void actor_dynapoly_set_move(z64_actor_t *actor, enum dynapoly_move_flag flags);



  asm("actor_dynapoly_set_move = 0x80035260");
# 3561 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
 static inline void
 z_dynapoly_new(
  z64_global_t *global
  , z64_actor_t *actor
  , uint32_t dynacollision
 )
 {

  z64_dynapoly_t *dynapoly = (z64_dynapoly_t*)(actor + 1);
  uint32_t result = 0;
  z_dynapoly_alloc(dynacollision, &result);
  dynapoly->poly_id =
  z_dynapoly_actor_set(
   global
   , &global->col_ctxt.unk_00_
   , actor
   , result
  );
 }
# 3593 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void dynapoly_set_flag_1(z64_actor_t *actor);



  asm("dynapoly_set_flag_1 = 0x80035290");





extern void dynapoly_set_flag_8(z64_actor_t *actor);



  asm("dynapoly_set_flag_8 = 0x8003532C");





extern uint16_t dynapoly_check_flag_1(void);



  asm("dynapoly_check_flag_1 = 0x80035340");





extern uint16_t dynapoly_check_flag_2(z64_actor_t *actor);



  asm("dynapoly_check_flag_2 = 0x80035364");







extern uint16_t dynapoly_check_flag_4(z64_actor_t *actor);



  asm("dynapoly_check_flag_4 = 0x80035388");





extern uint16_t dynapoly_check_flag_8(z64_actor_t *actor);



  asm("dynapoly_check_flag_8 = 0x800353AC");





extern int32_t actor_dynapoly_get_link_floorcast(z64_actor_t *actor);



  asm("actor_dynapoly_get_link_floorcast = 0x80035388");





extern void external_func_800435B4(void);



  asm("external_func_800435B4 = 0x800353AC");





extern void external_func_800435D8(void);



  asm("external_func_800435D8 = 0x800353D0");
# 3688 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8005A77C(void);



  asm("external_func_8005A77C = 0x800495BC");






extern void set_camera_type(void *camera_context, uint16_t camera_type);



  asm("set_camera_type = 0x800495E8");







extern void set_camera_id(void *camera_context, uint16_t camera_id);



  asm("set_camera_id = 0x800495E8");





extern void external_func_8005A948(void);



  asm("external_func_8005A948 = 0x80049708");





extern void external_func_8005A970(vec3s_t*, z64_gl_camera_t*);



  asm("external_func_8005A970 = 0x80049730");





extern void external_func_8005A9CC(void);



  asm("external_func_8005A9CC = 0x80049754");





extern int16_t external_func_8005A9F4(void* gl790);



  asm("external_func_8005A9F4 = 0x8004977C");
# 3765 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_camera_earthquake(void* global1E0, uint16_t unk, uint16_t strength, uint16_t duration);



  asm("z_camera_earthquake = 0x800497A4");





extern void external_func_8005AA90(void);



  asm("external_func_8005AA90 = 0x80049818");





extern void external_func_8005AC60(void);



  asm("external_func_8005AC60 = 0x800499F0");






extern void cutscene_set_relative_camera_command(void* global1E0, void*focus_tween_list, void*focus_point_list,z64_actor_t *actor);



  asm("cutscene_set_relative_camera_command = 0x80049A00");





extern void external_func_8005ACFC(void);



  asm("external_func_8005ACFC = 0x80049A94");





extern void external_func_8005AD1C(void);



  asm("external_func_8005AD1C = 0x80049AB8");





extern void external_func_8005AD40(void);



  asm("external_func_8005AD40 = 0x80049AE0");





extern void external_func_8005AFB4(void);



  asm("external_func_8005AFB4 = 0x80049D34");







extern void camera_set_data(void);



  asm("camera_set_data = 0x80049D58");





extern void external_func_8005B198(void);



  asm("external_func_8005B198 = 0x80049DA4");






extern void external_func_8005B1A4(void);



  asm("external_func_8005B1A4 = 0x80049DB4");







extern void* z_actor_damage_chart_get(int32_t id);



  asm("actor_damage_chart_get = 0x80049E10");
# 3894 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_jntsph_alloc(
z64_global_t* gl
, void* c
);



  asm("z_collider_jntsph_alloc = 0x8004A484");







extern void external_func_8005BC28(void);



  asm("external_func_8005BC28 = 0x8004A4B0");





extern void z_collider_jntsph_free(
z64_global_t* gl
, void* c
);



  asm("z_collider_jntsph_free = 0x8004A550");







extern void external_func_8005BE50(void);



  asm("external_func_8005BE50 = 0x8004A6BC");







extern int32_t z_collider_jntsph_init(
z64_global_t* gl
, void* c
, z64_actor_t* a
, void* init
, void* list
);



  asm("z_collider_jntsph_init = 0x8004A874");
# 3965 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_cylinder_alloc(
z64_global_t* gl
, void* c
);



  asm("z_collider_cylinder_alloc = 0x8004AB7C");
# 3981 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_cylinder_free(
z64_global_t* gl
, void* c
);



  asm("z_collider_cylinder_free = 0x8004ABCC");
# 3998 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8005C3F4(void);



  asm("external_func_8005C3F4 = 0x8004AC1C");







extern void external_func_8005C450(void);



  asm("external_func_8005C450 = 0x8004AC84");
# 4023 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_cylinder_init(
z64_global_t* gl
, void* c
, z64_actor_t* a
, const z64_collider_cylinder_init_t* source
);



  asm("z_collider_cylinder_init = 0x8004ACEC");







extern int32_t z_collider_tri_list_alloc(z64_global_t* gl, z64_collider_tris_t* t);



  asm("z_collider_tri_list_alloc = 0x8004B064");





extern void z_collider_tri_list_free(z64_global_t* gl, z64_collider_tris_t* t);



  asm("z_collider_tri_list_free = 0x8004B148");





extern int32_t z_collider_tri_list_init(z64_global_t* gl, z64_collider_tris_t* dest, z64_actor_t* actor, void* src, void* list);



  asm("z_collider_tri_list_init = 0x8004B3EC");





extern int32_t z_collider_quad_alloc(z64_global_t *gl, z64_collider_quad_t* col);



  asm("z_collider_quad_alloc = 0x8004B858");





extern void z_collider_quad_free(z64_global_t *gl, z64_collider_quad_t* col);



  asm("z_collider_quad_free = 0x8004B8A8");





extern int32_t z_collider_quad_init(z64_global_t *gl, z64_collider_t *collider, z64_actor_t *a, z64_collider_quad_init_t* col_init);



  asm("z_collider_quad_init = 0x8004B960");





extern void external_func_8005D160(void);



  asm("external_func_8005D160 = 0x8004B9C8");
# 4113 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_hitbox(
z64_global_t* gl
, z64_hit_ctxt_t* hit_ctxt
, void* c
);



  asm("z_collider_hitbox = 0x8004BD50");
# 4132 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_hurtbox(
z64_global_t* gl
, z64_hit_ctxt_t* hit_ctxt
, void* c
);



  asm("z_collider_hurtbox = 0x8004BF40");
# 4151 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_bumpbox(
z64_global_t* gl
, z64_hit_ctxt_t* hit_ctxt
, void* c
);



  asm("z_collider_bumpbox = 0x8004C130");







extern void external_func_8005DFAC(void);



  asm("external_func_8005DFAC = 0x8004C430");
# 4180 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_damage_table_init(
void* out
, z64_damagechart_init_t* damage_chart
, z64_collision_check_info_init_t* init
);



  asm("z_actor_damage_table_init = 0x80050344");
# 4202 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_actor_damage_table_init_80061EFC(
void* out
, z64_damagechart_init_t* damage_chart
, const uint32_t* init_data
);



  asm("z_actor_damage_table_init_80061EFC = 0x80050370");
# 4219 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_collider_cylinder_update(
z64_actor_t* a
, void* c
);



  asm("z_collider_cylinder_update = 0x80050B00");







extern void external_func_80062718(void);



  asm("external_func_80062718 = 0x80050B44");





extern void z_collider_quad_translate(z64_collider_quad_t* col, vec3f_t* a, vec3f_t* b, vec3f_t* c, vec3f_t* d);



  asm("z_collider_quad_translate = 0x80050B64");





extern void external_func_800627A0(void);



  asm("external_func_800627A0 = 0x80050BD4");






extern void z_collider_translate_index(
int32_t c_index
, void* clist
);



  asm("z_collider_translate_index = 0x80050CE4");






extern void z_effect_spawn_metalspark(z64_global_t* global, vec3f_t position);



  asm("z_effect_spawn_metalspark = 0x80051124");





extern void external_func_80062D60(void);



  asm("external_func_80062D60 = 0x800511B8");





extern void external_func_80062DF4(z64_global_t* gl, vec3f_t* pos);



  asm("external_func_80062DF4 = 0x80051250");





extern void external_func_800635D0(void);



  asm("external_func_800635D0 = 0x80051A34");





extern void external_func_80063E9C(void);



  asm("external_func_80063E9C = 0x80051E70");







extern void actor_cutscene_enable(z64_global_t *, z64_cutscene_t *global_cutscene);



  asm("actor_cutscene_enable = 0x80052328");







extern void actor_cutscene_disable(z64_global_t *, z64_cutscene_t *global_cutscene);



  asm("actor_cutscene_disable = 0x80052340");
# 4365 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void cutscene_init_script(z64_global_t *, uint32_t segptr);



  asm("cutscene_init_script = 0x80056F98");

static inline void cutscene_play_script(z64_global_t *gl, uint32_t segptr)
{
 cutscene_init_script(gl, segptr);
 (*(uint8_t*)((uint8_t*)(((0x8011A5D0) + 0x1414))+(0))) = 1;
}







extern void z_draw_gi_model(
z64_global_t* gl
, int16_t id
);



  asm("z_draw_gi_model = 0x800570C0");
# 4399 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_sfx_play_position(
z64_global_t* gl
, vec3f_t* pos
, int32_t radius
, uint16_t id
);



  asm("z_sfx_play_position = 0x80058FF8");







extern void external_func_8006C2B0(void);



  asm("external_func_8006C2B0 = 0x80059714");





extern void external_func_8006C318(void);



  asm("external_func_8006C318 = 0x8005977C");





extern uint16_t external_func_8006C360(z64_global_t *global, int32_t unk1);



  asm("external_func_8006C360 = 0x800597C0");





extern void external_func_8006C3D0(void);



  asm("external_func_8006C3D0 = 0x80059840");





extern void external_func_8006C438(void);



  asm("external_func_8006C438 = 0x800598AC");





extern void external_func_8006C4A4(void);



  asm("external_func_8006C4A4 = 0x8005991C");





extern void external_func_8006C750(void);



  asm("external_func_8006C750 = 0x80059BD0");





extern void external_func_8006C778(void);



  asm("external_func_8006C778 = 0x80059C00");





extern void external_func_8006C85C(void);



  asm("external_func_8006C85C = 0x80059CB0");





extern void external_func_8006C894(void);



  asm("external_func_8006C894 = 0x80059CE0");





extern void external_func_8006C8C4(void);



  asm("external_func_8006C8C4 = 0x80059D18");





extern void external_func_8006CF6C(void);



  asm("external_func_8006CF6C = 0x8005A36C");





extern void external_func_8006D074(void);



  asm("external_func_8006D074 = 0x8005A474");





extern void external_func_8006DD9C(void);



  asm("external_func_8006DD9C = 0x8005B00C");





extern void external_func_8006EF10(void);



  asm("external_func_8006EF10 = 0x8005BD78");





extern float math_linear_tween(uint16_t endframe, uint16_t startframe, uint16_t currentframe);



  asm("math_linear_tween = 0x8005C690");





extern void external_func_8006F9BC(void);



  asm("external_func_8006F9BC = 0x8005C714");





extern void external_func_80070600(void);



  asm("external_func_80070600 = 0x8005D2B4");





extern void external_func_80074CE8(void);



  asm("external_func_80074CE8 = 0x80060CE8");





extern void external_func_800773A8(z64_global_t* gl, float a, float b, float c, float d);



  asm("external_func_800773A8 = 0x800631D8");







extern void external_func_800775CC(void);



  asm("external_func_800775CC = 0x80063404");






extern void external_func_800775D8(void);



  asm("external_func_800775D8 = 0x80063414");







extern void external_func_800775F0(void);



  asm("external_func_800775F0 = 0x80063434");





extern void external_func_80077624(void);



  asm("external_func_80077624 = 0x80063474");






extern void external_func_80077684(void);



  asm("external_func_80077684 = 0x800634D4");






extern void external_func_800776E4(void);



  asm("external_func_800776E4 = 0x80063534");
# 4686 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_memset(void *dst, const uint32_t len, const uint8_t value);



  asm("z_memset = 0x80063630");
# 4699 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_coss(
int16_t angle
);



  asm("z_coss = 0x80063684");
# 4716 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_sins(
int16_t angle
);



  asm("z_sins = 0x800636C4");
# 4732 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_lib_approx_angle_s(
int16_t* angle
, int16_t target
, int16_t change
);



  asm("z_lib_approx_angle_s = 0x80063704");
# 4750 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int16_t z_lib_approx_s(
int16_t* out
, int16_t target
, int16_t change
);



  asm("z_lib_approx_s = 0x80063704");
# 4768 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_lib_approx_f(
float* out
, float target
, float change
);



  asm("z_lib_approx_f = 0x8006385C");
# 4787 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_80077AF8(void);



  asm("external_func_80077AF8 = 0x80063958");







extern void external_func_80077B58(void);



  asm("external_func_80077B58 = 0x800639B8");
# 4812 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int16_t z_lib_math_rand_s16_offset(
int16_t offset
, int16_t range
);



  asm("z_lib_math_rand_s16_offset = 0x80063BF0");
# 4828 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_vec3f_copy(
vec3f_t *out
, vec3f_t *in
);



  asm("z_lib_vec3f_copy = 0x80063CAC");
# 4844 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_vec3s_to_vec3f(
vec3f_t* out
, vec3s_t* in
);



    asm("z_lib_vec3s_to_vec3f = 0x80063CCC");
# 4861 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_vec3f_sum(
vec3f_t* a
, vec3f_t* b
, vec3f_t* out
);



    asm("z_lib_vec3f_sum = 0x80063D10");
# 4879 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_vec3f_diff(
vec3f_t* a
, vec3f_t* b
, vec3f_t* out
);



    asm("z_lib_vec3f_diff = 0x80063D48");
# 4898 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_vec3s_diff_to_vec3f(
vec3f_t* out
, vec3s_t* a
, vec3s_t* b
);



    asm("z_lib_vec3s_diff = 0x80063D80");
# 4916 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_vec3f_scale(
vec3f_t* out
, float scale
);



    asm("z_lib_vec3f_scale = 0x80063DDC");
# 4933 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_lib_vec3f_dist_xyz(
vec3f_t* a
, vec3f_t* b
);



    asm("z_lib_vec3f_dist_xyz = 0x80063E18");
# 4952 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_lib_vec3f_dist_diff(
vec3f_t* a
, vec3f_t* b
, vec3f_t* out
);



    asm("z_lib_vec3f_dist_diff = 0x80063E5C");
# 4970 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_lib_vec3f_dist_xz(
vec3f_t* a
, vec3f_t* b
);



  asm("z_lib_vec3f_dist_xz = 0x80063EB8");
# 4986 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int16_t z_lib_vec3f_yaw(
vec3f_t* a
, vec3f_t* b
);



  asm("z_lib_vec3f_yaw = 0x80063F00");
# 5002 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int16_t z_lib_vec3f_pitch(
vec3f_t* a
, vec3f_t* b
);



  asm("z_lib_vec3f_pitch = 0x80063F34");
# 5018 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_ichain_init(
z64_actor_t* a
, const uint32_t* data
);



  asm("z_lib_ichain_init = 0x80063F7C");
# 5034 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_lib_smooth_scale_max_min_f(
float* src
, float target
, float scale
, float max
, float min
);



  asm("z_lib_smooth_scale_max_min_f = 0x80064178");
# 5053 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_smooth_scale_max_f(
float* src
, float target
, float scale
, float max
);



  asm("z_lib_smooth_scale_max_f = 0x80064280");
# 5071 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_smooth_downscale_max_f(
float* src
, float scale
, float max
);



  asm("z_lib_smooth_downscale_max_f = 0x800642F0");







extern int16_t z_lib_smooth_scale_max_min_s(
int16_t* src
, int16_t target
, int16_t invScale
, int16_t max
, int16_t min
);



  asm("z_lib_smooth_scale_max_min_s = 0x80064508");







extern int16_t z_lib_smooth_scale_max_s(
int16_t* src
, int16_t target
, int16_t invScale
, int16_t max
);



  asm("z_lib_smooth_scale_max_s = 0x80064624");
# 5124 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_lib_word_copy(
void* dest
, void* src
);



  asm("z_lib_word_copy = 0x800646C8");







extern void external_func_80078884(int16_t id);



  asm("external_func_80078884 = 0x800646F0");






extern void play_sound_global_once(uint16_t sfx_id);



  asm("play_sound_global_once = 0x80064738");







extern void external_func_80078914(uint16_t sfx_id);



  asm("external_func_80078914 = 0x80064780");







extern void z_lights_init_pos_0(
void* info
, int16_t x, int16_t y, int16_t z
, uint8_t r, uint8_t g, uint8_t b
, int16_t radius
);



 asm("z_lights_init_pos_0 = 0x80065BCC");







extern void z_lights_init_pos_2(
void* info
, int16_t x, int16_t y, int16_t z
, uint8_t r, uint8_t g, uint8_t b
, int16_t radius
);



 asm("z_lights_init_pos_2 = 0x80065C30");






extern void z_lights_set_rgb_radius(
z64_lightinfo_t* info
, uint8_t r, uint8_t g, uint8_t b
, int16_t radius
);



 asm("z_lights_set_rgb_radius = 0x80065C98");






extern z64_light_node_t* z_lights_insert(
z64_global_t* gl
, z64_lighting_t* lighting
, z64_lightinfo_t* info
);



 asm("z_lights_insert = 0x800665B0");






extern void z_lights_kill(
z64_global_t* gl
, z64_lighting_t* lighting
, z64_light_node_t* light
);



 asm("z_lights_kill = 0x80066610");





extern void external_func_8007AE10(void);



  asm("external_func_8007AE10 = 0x80066C10");







extern void *z_malloc(
    uint32_t size




);
# 5278 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
        asm("z_malloc = 0x80066C10");







extern void *z_malloc_reverse(
 uint32_t size




);
# 5304 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void* z_realloc(void *addr, int32_t size);



   asm("z_realloc = 0x80066C60");






extern void z_free(void *address);



    asm("z_free = 0x80066CB8");





extern void external_func_8007C25C(void);



  asm("external_func_8007C25C = 0x80067850");





extern void external_func_8007C3F4(void);



  asm("external_func_8007C3F4 = 0x800679E8");







extern void actor_closeup(z64_global_t* globalCtx, int16_t arg1, int16_t arg2, z64_actor_t* actor, int16_t arg4);



  asm("actor_closeup = 0x8006B6FC");







extern void external_func_800803F0(void);



  asm("external_func_800803F0 = 0x8006B9B4");






extern void actor_one_point_cutscene(z64_global_t *, z64_actor_t *actor);



  asm("actor_one_point_cutscene = 0x8006BA10");






extern void actor_one_point_cutscene_sound(z64_global_t *, z64_actor_t *actor, uint16_t sound);



  asm("actor_one_point_cutscene_sound = 0x8006BB7C");





extern void external_func_80080728(void);



  asm("external_func_80080728 = 0x8006BBF4");





extern void interface_draw_compass(z64_global_t *gl);



  asm("interface_draw_compass = 0x8008921C");





extern void external_func_800825E0(void);



  asm("external_func_800825E0 = 0x8006D8E0");
# 5425 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void player_swap_age_equipment(void);



        asm("player_swap_age_equipment = 0x8006F804");





extern void external_func_800849A8(void);



  asm("external_func_800849A8 = 0x8006FA88");





extern void external_func_800849EC(void);



  asm("external_func_800849EC = 0x8006FAD0");





extern void gfx_update_item_icon(z64_global_t *gl, uint8_t button_id);



  asm("gfx_update_item_icon = 0x8006FB50");






extern void external_func_80084BF4(void);



  asm("external_func_80084BF4 = 0x8006FCB0");






extern void inventory_item_set(z64_global_t *global, uint8_t item);



  asm("inventory_item_set = 0x8006FDCC");







extern uint8_t inventory_item_get(uint8_t item);



  asm("inventory_item_get = 0x80071420");






extern int32_t inventory_item_update(uint8_t item_old, uint8_t item_new);



  asm("inventory_item_update = 0x800719E0");





extern int32_t inventory_has_empty_bottle(void);



  asm("inventory_has_empty_bottle = 0x80071A94");





extern s32 inventory_has_specific_bottle(u8 bottle_item);



  asm("external_func_80086B2C = 0x80071B04");





extern void external_func_80086F00(void);



  asm("external_func_80086F00 = 0x80071E6C");







extern void external_func_8008708C(void);



  asm("external_func_8008708C = 0x80071FF8");
# 5555 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_player_update_health(z64_global_t* gl, int16_t health);



  asm("z_player_update_health = 0x800720BC");
# 5568 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_player_update_rupees(int32_t num_rupees);



  asm("z_player_update_rupees = 0x800721CC");






extern void z_inventory_update_ammo(int16_t item, int16_t ammo_change);



  asm("z_inventory_update_ammo = 0x800721F4");





extern void external_func_80087680(void);



  asm("external_func_80087680 = 0x80072500");





extern void external_func_800876C8(z64_global_t *gl);



  asm("external_func_800876C8 = 0x80072548");
# 5612 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_parameter_subtract_magic(z64_global_t* gl, int16_t amount, int16_t a2);



  asm("z_parameter_subtract_magic = 0x80072588");





extern void external_func_80088AA0(int16_t seconds);



  asm("external_func_80088AA0 = 0x800738E8");





extern void external_func_80088AF0(void);



  asm("external_func_80088AF0 = 0x80073938");





extern void external_func_80088B34(int16_t a);



  asm("external_func_80088B34 = 0x8007397C");






extern void z_parameter_draw_action_label(z64_gfx_t* gfx, uint32_t a1);



  asm("z_parameter_draw_action_label = 0x800739CC");






extern void z_parameter_draw_item_button(z64_gfx_t* gfx, uint32_t a1);



  asm("z_parameter_draw_item_button = 0x80073AB4");






extern void z_parameter_draw_item_icon(z64_global_t* gl, uint32_t icon_texture, uint32_t button);



  asm("z_parameter_draw_item_icon = 0x800748DC");






extern void z_parameter_draw_ammo(z64_global_t* gl, uint32_t icon_texture, uint32_t button);



  asm("z_parameter_draw_ammo = 0x80074A84");






extern void z_parameter_draw_action_button(z64_global_t* gl);



  asm("z_parameter_draw_action_button = 0x80074F24");





extern void external_func_8008A3E0(z64_global_t* gl);
# 5718 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8008A8B8(z64_global_t* gl, int32_t a1, int32_t a2, int32_t a3, int32_t sp10);



  asm("external_func_8008A8B8 = 0x80075108");





extern void z_if_viewport_init(z64_if_ctxt_t* if_ctxt);



  asm("z_if_viewport_init = 0x800756A8");






extern void* z_get_path_index(z64_global_t* gl, int16_t index, int16_t max);



  asm("z_get_path_index = 0x80078F80");





extern void external_func_8008E520(void);



  asm("external_func_8008E520 = 0x80078FC4");





extern void external_func_8008E60C(void);



  asm("external_func_8008E60C = 0x800790B0");







extern int32_t player_is_busy(z64_global_t *global, void *link_instance);



  asm("player_is_busy = 0x8007938C");






extern int32_t player_is_busy_talking(z64_global_t *global);



  asm("player_is_busy_talking = 0x8007943C");







extern void external_func_8008EC04(void);



  asm("external_func_8008EC04 = 0x800796C0");







extern void external_func_8008ED9C(void);



  asm("external_func_8008ED9C = 0x80079854");





extern void external_func_8008EEAC(void);



  asm("external_func_8008EEAC = 0x80079968");





extern void external_func_8008EF44(void);



  asm("external_func_8008EF44 = 0x80079A04");





extern int32_t external_func_8008EF5C(z64_global_t* gl, vec3f_t* pos, float radius, float u0);



  asm("external_func_8008EF5C = 0x80079A20");





extern void z_player_lib_draw_link(
 z64_global_t *globalCtx
 , void **skeleton
 , vec3s_t *jointTable
 , int32_t dListCount
 , int32_t lod
 , int32_t tunic
 , int32_t boots
 , int32_t face
 , void *overrideLimbDraw
 , void *postLimbDraw
 , void *data
);



  asm("z_player_lib_draw_link = 0x80079F48");







extern void external_func_8008F034(void);



  asm("external_func_8008F034 = 0x80079AF8");
# 5883 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern uint8_t player_get_mask(z64_global_t *global);



  asm("player_get_mask = 0x80079B44");







extern void player_set_mask(z64_global_t *global);



  asm("player_set_mask = 0x80079B54");






extern int32_t player_is_mirrorshield(z64_global_t *global);



  asm("player_is_mirrorshield = 0x80079B64");





extern void external_func_8008F0AC(void);



  asm("external_func_8008F0AC = 0x80079B7C");







extern int32_t player_is_hookshotting(void *link_instance);



  asm("player_is_hookshotting = 0x80079BD4");





extern void external_func_8008FCC8(void);



  asm("external_func_8008FCC8 = 0x8007A740");





extern void external_func_80090480(void);



  asm("external_func_80090480 = 0x8007AF14");





extern void external_func_80090D20(void);



  asm("external_func_80090D20 = 0x8007B734");






extern void external_func_8009214C(void);



  asm("external_func_8009214C = 0x8007CA54");





extern void external_func_80092DAC(void);



  asm("external_func_80092DAC = 0x8007D668");





extern void external_func_80092DF0(void);



  asm("external_func_80092DF0 = 0x8007D6B0");





extern void external_func_80092E70(void);



  asm("external_func_80092E70 = 0x8007D738");





extern void external_func_80092F88(void);



  asm("external_func_80092F88 = 0x8007D85C");






extern Gfx* z_rcp_fog_set(Gfx* gfx, int32_t r, int32_t g, int32_t b, int32_t a, int32_t n, int32_t f);



  asm("z_rcp_fog_set = 0x8007DC40");






extern Gfx* z_rcp_fog_set_2(Gfx* gfx, int32_t r, int32_t g, int32_t b, int32_t a, int32_t n, int32_t f);



  asm("z_rcp_fog_set_2 = 0x8007DF4C");






extern Gfx* z_rcp_set_dlist(Gfx* gfx, uint32_t i);



  asm("z_rcp_set_dlist = 0x8007DFBC");





extern Gfx* external_func_800937C0(Gfx *p);



  asm("external_func_800937C0 = 0x8007E008");





extern void external_func_80094140(z64_gfx_t *g);
# 6072 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_80094520(z64_gfx_t *g);
# 6082 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_80094A14(z64_gfx_t *g);



  asm("external_func_80094A14 = 0x8007E09C");





extern void external_func_80093C14(void);



  asm("external_func_80093C14 = 0x8007E204");





extern void external_func_80093C80(void);



  asm("external_func_80093C80 = 0x8007E22C");






extern void z_rcp_append_preset_opa(
z64_gfx_t* gfx_ctxt
);



  asm("z_rcp_append_preset_opa = 0x8007E298");
# 6128 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_rcp_append_preset_xlu_80093D84(
z64_gfx_t* gfx_ctxt
);



  asm("z_rcp_append_preset_xlu_80093D84 = 0x80093D84");







extern void external_func_80093F34(void);



  asm("external_func_80093F34 = 0x8007E388");






extern void z_rcp_append_preset_xlu_80094044(
z64_gfx_t* gfx_ctxt
);



  asm("z_rcp_append_preset_xlu_80094044 = 0x8007E544");
# 6169 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800943C8(void);



  asm("external_func_800943C8 = 0x8007E56C");





extern void interface_jump_to_main_dlist(z64_gfx_t *gfx_ctxt);



  asm("external_func_80094520 = 0x8007E5BC");





extern void external_func_8009457C(void);



  asm("external_func_8009457C = 0x8007E63C");





extern void external_func_8009460C(void);



  asm("external_func_8009460C = 0x8007E690");





extern void external_func_80094968(void);



  asm("external_func_80094968 = 0x8007E824");





extern void external_func_80094B58(z64_gfx_t* gfx_ctxt);



  asm("external_func_80094B58 = 0x8007E908");





extern void external_func_80094BC4(void);



  asm("external_func_80094BC4 = 0x8007E930");





extern void external_func_80094C50(void);



  asm("external_func_80094C50 = 0x8007E978");





extern void external_func_80094D28(void);



  asm("external_func_80094D28 = 0x8007E9C8");





extern void external_func_80094E78(void);



  asm("external_func_80094E78 = 0x8007EADC");







extern Gfx* z_rcp_gen_1_settilesize(
z64_gfx_t* gfx_ctxt
, int32_t tile0
, int32_t s0_ul
, int32_t t0_ul
, int32_t t0_w
, int32_t t0_h
);



  asm("z_rcp_gen_1_settilesize = 0x8007EB00");
# 6294 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern Gfx* z_rcp_gen_2_settilesize(
z64_gfx_t* gfx_ctxt
, int32_t tile0
, int32_t s0_ul
, int32_t t0_ul
, int32_t t0_w
, int32_t t0_h
, int32_t tile1
, int32_t s1_ul
, int32_t t1_ul
, int32_t t1_w
, int32_t t1_h
);



  asm("z_rcp_gen_2_settilesize = 0x8007EB84");







extern void external_func_80095068(void);



  asm("external_func_80095068 = 0x8007ECA4");





extern void external_func_800951D0(void);



  asm("external_func_800951D0 = 0x8007EE04");





extern void external_func_80095248(z64_gfx_t* gfx, uint8_t a1, uint8_t a2, uint8_t a3);
# 6350 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_8009728C(void);



  asm("external_func_8009728C = 0x80080A3C");





extern void external_func_80097534(void);



  asm("external_func_80097534 = 0x80080C98");





extern void external_func_80097A54(void);



  asm("external_func_80097A54 = 0x80081188");
# 6384 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_scene_object_load(
z64_obj_ctxt_t* obj_ctxt
, int32_t id
);



  asm("z_scene_object_load = 0x800812F0");
# 6405 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_scene_object_get_index(
z64_obj_ctxt_t* obj_ctxt
, int32_t id
);



  asm("z_scene_object_get_index = 0x80081628");
# 6427 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_scene_object_is_loaded(
z64_obj_ctxt_t* obj_ctxt
, int32_t id
);



  asm("z_scene_object_is_loaded = 0x80081688");
# 6447 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_draw_lod(z64_global_t* gl, z64_skeleton_t* skel, vec3s_t* limb_draw_table, void* override, void* postdraw, z64_actor_t* actor, int32_t dlist_idx);



  asm("z_skelanime_draw_lod = 0x8008902C");
# 6460 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern Gfx* z_skelanime_draw_mtx_lod(
z64_global_t* gl
, uint32_t skeleton
, uint32_t animation
, uint32_t limb_dlists_count
, int32_t callback0(
   z64_global_t *global
 , uint8_t limb
 , uint32_t *dlist
 , vec3f_t *translation
 , vec3s_t *rotation
 , void *entity
  )
, void callback1(
   z64_global_t *global
 , uint8_t limb
 , uint32_t dlist
 , vec3s_t *rotation
 , void *entity
  )
, void* instance
, Gfx* dest
);



  asm("z_skelanime_draw_mtx_lod = 0x800894A4");
# 6498 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
static inline void z_skelanime_draw(
z64_global_t* gl
, bool is_matrix
, void* instance
, z64_skelanime_t *sk
, int32_t callback0(
 z64_global_t* gl
 , int32_t limb
 , uint32_t* dlist
 , vec3f_t* translation
 , vec3s_t* rotation
 , void* instance
 )
, void callback1(
 z64_global_t* gl
 , int32_t limb
 , uint32_t dlist
 , vec3s_t* rotation
 , void* instance
 )
) {
 if (is_matrix)
  _z_skelanime_draw_mtx(
   gl
   , sk->skeleton
   , sk->limb_draw_table
   , sk->dlist_count
   , callback0
   , callback1
   , instance
  );
 else
  _z_skelanime_draw(
   gl
   , sk->skeleton
   , sk->limb_draw_table
   , callback0
   , callback1
   , instance
  );
}






extern int32_t z_skelanime_anim_nframes(
uint32_t anim
);



  asm("z_skelanime_anim_nframes = 0x8008A194");
# 6562 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern Gfx* z_skelanime_draw_dest(z64_global_t *global, uint32_t limb_index, uint32_t adt, void* subr0, void* subr1, z64_actor_t *actor, Gfx *gfx_buffer);



  asm("z_skelanime_draw_dest = 0x8008A1DC");





extern Gfx* z_skelanime_draw_mtx_destination(z64_global_t *global, uint32_t limb_index, void* adt, uint8_t limb_dlists_count, void* subr0, void* subr1, z64_actor_t *actor, void *gfx_buffer);



  asm("z_skelanime_draw_mtx_destination = 0x8008A608");






extern void z_skelanime_interpolate_vec3s(int32_t a, vec3s_t* b, vec3s_t* c, vec3s_t* d, float e);



  asm("z_skelanime_interpolate_vec3s = 0x8008AFB8");






extern void z_skelanime_load_anim_3(z64_global_t* gl, int32_t nvec, vec3s_t* dst, vec3s_t* src, uint8_t* idx);



  asm("z_skelanime_load_anim_3 = 0x8008B698");






extern void z_skelanime_load_anim_5(z64_global_t* gl, z64_actor_t* actor, z64_skelanime_t* skl, float a3);



  asm("z_skelanime_load_anim_5 = 0x8008B778");





extern void external_func_800A3BC0(void);



  asm("external_func_800A3BC0 = 0x8008BCA4");
# 6628 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
static inline void z_skelanime_init(
z64_global_t* gl
, bool is_matrix
, z64_skelanime_t* sk
, uint32_t skeleton
, uint32_t anim
)
{
 if (is_matrix)
  _z_skelanime_mtx_init(gl, sk, skeleton, anim, 0, 0, 0);

 else
  _z_skelanime_init(gl, sk, skeleton, anim, 0, 0, 0);
}





static inline void z_skelanime_init_ext(
z64_global_t* gl
, bool is_matrix
, z64_skelanime_t* sk
, uint32_t skeleton
, uint32_t anim
, vec3s_t* dt_rot
, vec3s_t* dt_pos
, uint32_t nlimb
)
{
 if (is_matrix)
  _z_skelanime_mtx_init(gl, sk, skeleton, anim, dt_rot, dt_pos, nlimb);

 else
  _z_skelanime_init(gl, sk, skeleton, anim, dt_rot, dt_pos, nlimb);
}







extern int32_t z_skelanime_update_anim(
z64_skelanime_t* s
);



  asm("z_skelanime_update_anim = 0x8008C9C0");
# 6687 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_change_anim_impl(z64_skelanime_t* sk, z64_anim_header_t* anim, float playback_speed, float frame, float nframes, uint8_t unk, float transition_rate, int8_t unk2);



  asm("z_skelanime_change_anim_impl = 0x8008CFC0");
# 6702 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_change_anim(
z64_skelanime_t* sk
, uint32_t anim
, float speed
, float frame_begin
, int frame_count
, uint32_t unk_1
, float xrate
);



  asm("z_skelanime_change_anim = 0x8008D17C");
# 6723 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_change_anim_default_stop(
z64_skelanime_t* s
, uint32_t anim
);



  asm("z_skelanime_change_anim_default_stop = 0x8008D1C4");
# 6739 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_change_anim_trate(
z64_skelanime_t* s
, uint32_t anim
, float trate
);



  asm("z_skelanime_change_anim_trate = 0x8008D21C");
# 6757 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_change_anim_playback(
z64_skelanime_t* s
, uint32_t anim
, float playback_speed
);



  asm("z_skelanime_change_anim_playback = 0x8008D278");
# 6776 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_anim_set(
z64_skelanime_t* s
, uint32_t anim
);



  asm("z_skelanime_anim_set = 0x8008D2D4");
# 6794 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_change_frame_count(
z64_skelanime_t* s
, uint32_t anim
, float frame_count
);



  asm("z_skelanime_change_frame_count = 0x8008D328");
# 6811 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_change_anim_playback_repeat(
z64_skelanime_t* s
, uint32_t anim
, float playback_speed
);



 asm("z_skelanime_change_anim_playback_repeat = 0x8008D360");






extern void z_skelanime_anim_reverse(z64_skelanime_t* sk);



  asm("z_skelanime_anim_reverse = 0x8008D3E4");





extern void external_func_800A5428(void);



  asm("external_func_800A5428 = 0x8008D408");





extern int32_t z_skelanime_frame_index_test(
z64_skelanime_t* s
, float frame
);



  asm("z_skelanime_frame_index_test = 0x8008D6A8");
# 6862 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_skelanime_free(z64_skelanime_t* skl, z64_global_t* gl);



  asm("z_skelanime_free = 0x8008D6D0");





extern void external_func_800A5F60(void);



  asm("external_func_800A5F60 = 0x8008DE88");






extern void skelanime_draw_weighted(z64_actor_t* actor, z64_global_t* global, z64_skelanime_weighted_t* weighted_skelanime, void* callback1, uint32_t unk0);



  asm("skelanime_draw_weighted = 0x8008E1D4");






extern void skelanime_draw_weighted_unk(z64_actor_t* actor, z64_global_t* global, z64_skelanime_weighted_t* weighted_skelanime, void* callback1, void* callback2, uint32_t unk0);



        asm("skelanime_draw_weighted_unk = 0x8008E204");





extern void external_func_800A63CC(void);



  asm("external_func_800A63CC = 0x8008E270");





extern void external_func_800A6408(void);



  asm("external_func_800A6408 = 0x8008E2AC");






extern void z_skelanime_init_weighted(z64_global_t *global, z64_skelanime_weighted_t *weighted_skelanime, uint32_t skeleton, uint32_t animation);



  asm("z_skelanime_init_weighted = 0x8008E4EC");





extern void external_func_800A6888(void);



  asm("external_func_800A6888 = 0x8008E6BC");





extern void external_func_800A6E10(void);



  asm("external_func_800A6E10 = 0x8008EC20");





extern void external_func_800A6EF4(void);



  asm("external_func_800A6EF4 = 0x8008ED08");





extern void z_skin_mtx_multiply(float* in, float* mult, float* out);



  asm("external_func_800A6EF4 = 0x8008EDB8");






extern void external_func_800A7B04(void);



  asm("external_func_800A7B04 = 0x8008F890");





extern void external_func_800A7E70(void);



  asm("external_func_800A7E70 = 0x8008FC98");






extern void external_func_800A9CD4(void);



  asm("external_func_800A9CD4 = 0x800912C4");





extern void external_func_800A9F6C(float a, uint8_t b, uint8_t c, uint8_t d);



  asm("external_func_800A9F6C = 0x8009151C");






extern void external_func_800AA000(float a, uint8_t b, uint8_t duration, uint8_t step);



  asm("external_func_800AA000 = 0x800915CC");





extern void external_func_800AA148(void);



  asm("external_func_800AA148 = 0x80091730");
# 7041 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800AA278(void* view, z64_gfx_t* gfx);



  asm("external_func_800AA278 = 0x80091858");






extern void external_func_800AA358(void* view, vec3f_t* eye, vec3f_t* vec2, vec3f_t* vec3);



  asm("external_func_800AA358 = 0x80091918");





extern void external_func_800AA4FC(void* view, void* viewport);
# 7072 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800AAA50(void* view, int32_t a1);



  asm("external_func_800AAA50 = 0x80091F94");






extern void external_func_800B3840(void);



  asm("external_func_800B3840 = 0x80099620");





extern void external_func_800BB2B4(void);



  asm("external_func_800BB2B4 = 0x800999A4");





extern void external_func_800BC490(void);



  asm("external_func_800BC490 = 0x8009A1B0");





extern void external_func_800BC56C(void);



  asm("external_func_800BC56C = 0x8009A25C");





extern void external_func_800BC590(void);



  asm("external_func_800BC590 = 0x8009A284");





extern void external_func_800BC8A0(void);



  asm("external_func_800BC8A0 = 0x8009A574");







extern int32_t external_func_800BFC84(z64_global_t* gl);



  asm("external_func_800BFC84 = 0x8009CB08");







extern uint16_t start_cutscene_camera(z64_global_t *global);



  asm("start_cutscene_camera = 0x8009D0F0");







extern void external_func_800C0314(z64_global_t *global, int32_t unk0, int32_t flags);



  asm("external_func_800C0314 = 0x8009D1AC");





extern void external_func_800C0384(void);



  asm("external_func_800C0384 = 0x8009D21C");





extern void external_func_800C0438(void);



  asm("external_func_800C0438 = 0x8009D284");







extern void external_func_800C04A4(void);



  asm("external_func_800C04A4 = 0x8009D2F0");







extern void update_cutscene_camera(z64_global_t *global, int16_t a1, vec3f_t *camera_focus_point, vec3f_t *camera_origin);



  asm("update_cutscene_camera = 0x8009D328");





extern void external_func_800C05E4(void);



  asm("external_func_800C05E4 = 0x8009D438");





extern void external_func_800C0704(void);



  asm("external_func_800C0704 = 0x8009D55C");





extern void external_func_800C078C(void);



  asm("external_func_800C078C = 0x8009D5F0");





extern void external_func_800C0808(void);



  asm("external_func_800C0808 = 0x8009D66C");







extern void end_cutscene_camera(z64_global_t *global, int16_t unk0, int32_t end_movement_speed);



  asm("end_cutscene_camera = 0x8009D718");







extern void external_func_800C0AF4(void);



  asm("external_func_800C0AF4 = 0x8009D94C");






extern void z_void_out(z64_global_t *global);



  asm("z_void_out = 0x8009D9B8");





extern void external_func_800C0C88(void);



  asm("external_func_800C0C88 = 0x8009DAB0");





extern void external_func_800C0CB8(void);



  asm("external_func_800C0CB8 = 0x8009DAE4");






extern void game_updates_off(z64_global_t *global);



  asm("game_updates_off = 0x8009DB54");





extern void external_func_800C0DB4(void);



  asm("external_func_800C0DB4 = 0x8009DBE4");






extern void external_func_800C0F08(void);



  asm("external_func_800C0F08 = 0x8009DD44");






extern void external_func_800C3770(void);



  asm("external_func_800C3770 = 0x8009FDEC");






extern uint32_t z_game_alloc(z64_global_t* gl, int32_t size, char* file, int32_t line);
# 7383 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
  static void *
  graph_alloc(z64_gfx_t *gfx_ctxt, int32_t size)
  {


   gfx_ctxt->poly_opa.d -= size / 8;
   return gfx_ctxt->poly_opa.d;
  }






extern void z_debug_graph_alloc(
Gfx* buffer
, z64_gfx_t* gfx_ctxt
, char* filename
, int32_t line
);
# 7415 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_debug_graph_write(
Gfx* buffer
, z64_gfx_t* gfx_ctxt
, char* filename
, int32_t line
);
# 7432 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800C6C20(void);



  asm("external_func_800C6C20 = 0x800A1AA0");





extern void external_func_800C6C28(void);



  asm("external_func_800C6C28 = 0x800A1AAC");





extern float external_func_800CA720(float a0);



  asm("external_func_800CA720 = 0x800A45FC");







extern void external_func_800CA774(void);



  asm("external_func_800CA774 = 0x800A4650");





extern void external_func_800CAFEC(void);



  asm("external_func_800CAFEC = 0x800A4EBC");





extern void external_func_800CB010(void);



  asm("external_func_800CB010 = 0x800A4EE0");





extern void external_func_800CB0C0(void);



  asm("external_func_800CB0C0 = 0x800A4F98");







extern void external_func_800CB198(void);



  asm("external_func_800CB198 = 0x800A506C");





extern void external_func_800CB55C(void);



  asm("external_func_800CB55C = 0x800A5434");





extern void external_func_800CB594(void);



  asm("external_func_800CB594 = 0x800A5470");





extern float math_vec3f_sum_squares(vec3f_t *in);



  asm("math_vec3f_sum_squares = 0x800A54E4");





extern void external_func_800CB628(void);



  asm("external_func_800CB628 = 0x800A5510");





extern float math_distance_squared(vec3f_t *in, vec3f_t *in_2);



  asm("math_distance_squared = 0x800A5538");







extern void external_func_800CB678(void);



  asm("external_func_800CB678 = 0x800A5560");







extern void external_func_800CB7B4(void);



  asm("external_func_800CB7B4 = 0x800A56B8");





extern void external_func_800CC824(void);



  asm("external_func_800CC824 = 0x800A6750");





extern void external_func_800CCB0C(void);



  asm("external_func_800CCB0C = 0x800A69A4");





extern void external_func_800CCF48(void);



  asm("external_func_800CCF48 = 0x800A6D8C");





extern void external_func_800CE15C(void);



  asm("external_func_800CE15C = 0x800A7FC8");





extern void external_func_800CE4B8(void);



  asm("external_func_800CE4B8 = 0x800A8334");







extern int16_t z_atan2s(float x, float y);



  asm("z_atan2_s = 0x800AA4F8");
# 7655 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_atan2f(float x, float y);



  asm("z_atan2f = 0x800AA670");
# 7672 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_new(void *gameState);



  asm("z_matrix_new = 0x800AA6B0");
# 7688 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_push(void);



  asm("z_matrix_push = 0x800AA6EC");
# 7706 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_pop(void);



  asm("z_matrix_pop = 0x800AA724");
# 7721 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_get(
float* mf
);



  asm("z_matrix_get = 0x800AA740");
# 7738 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_put(
float* mf
);



  asm("z_matrix_put = 0x800AA764");
# 7753 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float* z_matrix_get_now(void);
# 7769 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_multiply(
float* in
, int32_t apply
);



  asm("z_matrix_multiply = 0x800AA79C");
# 7786 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_translate_3f(
float x, float y, float z
, int32_t apply
);



  asm("z_matrix_translate_3f = 0x800AA7F4");
# 7803 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_scale_3f(
float x, float y, float z
, int32_t apply
);



  asm("z_matrix_scale_3f = 0x800AA8FC");
# 7820 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_pitch(
int16_t x
, int32_t apply
);



  asm("z_matrix_pitch = 0x800AA9E0");
# 7837 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_yaw(
int16_t y
, int32_t apply
);



  asm("z_matrix_yaw = 0x800AAB94");
# 7854 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_roll(
float z
, int32_t apply
);



  asm("z_matrix_roll = 0x800AAD4C");
# 7871 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_rotate_3s(
int16_t x, int16_t y, int16_t z
, int32_t apply
);



  asm("z_matrix_rotate_3s = 0x800AAF00");
# 7887 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_translate_rotate(
vec3f_t* translation
, vec3s_t* rotation
);



  asm("z_matrix_translate_rotate = 0x800AB1BC");
# 7903 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_translate_3f_800D1694(
float x, float y, float z
, vec3s_t* r
);



 asm("z_matrix_translate_3f_800D1694 = 0x800AB510");
# 7920 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern Mtx* z_matrix_float_to_fixed(
float* src
, Mtx* dest
);



  asm("z_matrix_float_to_fixed = 0x800AB6BC");
# 7937 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern Mtx* z_matrix_top_to_fixed(
Mtx* dest
, char* file
, int32_t line
);



  asm("z_matrix_top_to_fixed = 0x800AB8D8");
# 7955 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern Mtx* z_matrix_alloc(
   z64_gfx_t *gfx_ctx




);
# 7970 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
  asm("z_matrix_alloc = 0x800AB900");
# 7979 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_new_f2l(float src[4][4], z64_gfx_t* gfx);
# 7993 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_mult_vec3f(vec3f_t* src, vec3f_t* dest);



  asm("z_matrix_mult_vec3f = 0x800AB958");
# 8009 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_float_copy(void *dst, void *src);



  asm("z_matrix_float_copy = 0x800ABA10");
# 8022 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_fixed_to_float(Mtx* src, float dest[4][4]);
# 8035 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_mult_vec3f_ext(vec3f_t* src, vec3f_t* dest, float mf[4][4]);



  asm("z_matrix_mult_vec3f_ext = 0x800ABD6C");






extern void z_matrix_reverse(float mf[4][4]);
# 8057 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_rotate_vec3f(vec3f_t* rot);



  asm("z_matrix_rotate_vec3f = 0x800ABE54");
# 8071 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_matrix_float_to_vec3s(
float* mf
, vec3s_t*
, int32_t flag
);



  asm("z_matrix_float_to_vec3s = 0x800ABF50");







extern void external_func_800D2264(void);



  asm("external_func_800D2264 = 0x800AC0E8");





extern void external_func_800D23FC(void);



  asm("external_func_800D23FC = 0x800AC280");





extern void external_func_800D285C(void);
# 8117 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800ED858(void);



  asm("external_func_800ED858 = 0x800C2C90");






extern void external_func_800ED93C(void);



  asm("external_func_800ED93C = 0x800C2D74");





extern void external_func_800F3F3C(void);



  asm("external_func_800F3F3C = 0x800C4C84");





extern void external_func_800F4190(void);



  asm("external_func_800F4190 = 0x800C4ED0");





extern void external_func_800F41E0(void);



  asm("external_func_800F41E0 = 0x800C4F20");





extern void external_func_800F4254(vec3f_t* a0, uint32_t a1);



  asm("external_func_800F4254 = 0x800C4F94");





extern void z_sound_loop_pitch(void *actor_plus_0xE4, uint16_t sfx, float pitch);



  asm("z_sound_loop_pitch = 0x800C50AC");





extern void external_func_800F4414(void);



  asm("external_func_800F4414 = 0x800C5154");





extern void external_func_800F44EC(void);



  asm("external_func_800F44EC = 0x800C522C");





extern void external_func_800F4524(void);



  asm("external_func_800F4524 = 0x800C5264");





extern void external_func_800F4634(void);



  asm("external_func_800F4634 = 0x800C5374");





extern void external_func_800F46E0(void);



  asm("external_func_800F46E0 = 0x800C5420");





extern void external_func_800F483C(void);



  asm("external_func_800F483C = 0x800C557C");





extern void external_func_800F4870(void);



  asm("external_func_800F4870 = 0x800C55B0");







extern void external_func_800F4A54(void);



  asm("external_func_800F4A54 = 0x800C5794");





extern void external_func_800F4B58(void);



  asm("external_func_800F4B58 = 0x800C5898");





extern void external_func_800F4BE8(void);



  asm("external_func_800F4BE8 = 0x800C5928");





extern void external_func_800F4BF4(void);



  asm("external_func_800F4BF4 = 0x800C5934");





extern void external_func_800F4E30(void);



  asm("external_func_800F4E30 = 0x800C5B70");





extern void external_func_800F50EC(void);



  asm("external_func_800F50EC = 0x800C5E2C");





extern void external_func_800F52A0(void);



  asm("external_func_800F52A0 = 0x800C5FE0");






extern void external_func_800F5504(void);



  asm("external_func_800F5504 = 0x800C6258");





extern void play_windmill_music(void);



  asm("external_func_800F5718 = 0x800C646C");





extern void external_func_800F574C(void);



  asm("external_func_800F574C = 0x800C64A0");





extern void external_func_800F5918(void);



  asm("external_func_800F5918 = 0x800C666C");





extern void external_func_800F5A58(void);



  asm("external_func_800F5A58 = 0x800C67AC");







extern void z_bgm_play_midboss(uint32_t musicID);



  asm("z_bgm_play_midboss = 0x800C6820");





extern void z_bgm_stop_midboss(void);



  asm("z_bgm_stop_midboss = 0x800C6894");





extern void external_func_800F5BF0(void);



  asm("external_func_800F5BF0 = 0x800C692C");





extern void external_func_800F5C2C(void);



  asm("external_func_800F5C2C = 0x800C6968");





extern void external_func_800F5C64(void);



  asm("external_func_800F5C64 = 0x800C69A0");





extern void external_func_800F6268(void);



  asm("external_func_800F6268 = 0x800C6F9C");





extern void external_func_800F6584(void);



  asm("external_func_800F6584 = 0x800C72A4");





extern void external_func_800F67A0(void);



  asm("external_func_800F67A0 = 0x800C74C0");





extern void external_func_800F6828(void);



  asm("external_func_800F6828 = 0x800C7548");





extern void external_func_800F68BC(void);



  asm("external_func_800F68BC = 0x800C75DC");





extern void external_func_800F6D58(void);



  asm("external_func_800F6D58 = 0x800C7A78");





extern void external_func_800F6FB4(void);



  asm("external_func_800F6FB4 = 0x800C7C90");





extern void external_func_800F7260(void);



  asm("external_func_800F7260 = 0x800C7F40");






extern void z_sfx_play_system(
uint16_t sfx_id
, vec3f_t* pos
, uint32_t a2
, float* a3
, float* a4
, float* a5
);



 asm("z_sfx_play_system = 0x800C806C");





extern void external_func_800F89E8(void);



  asm("external_func_800F89E8 = 0x800C9568");





extern void external_func_800F8A44(void);



  asm("external_func_800F8A44 = 0x800C95C4");





extern void external_func_800F8D04(void);



  asm("external_func_800F8D04 = 0x800C9884");





extern void external_func_800F8FF4(void);



  asm("external_func_800F8FF4 = 0x800C9B74");






extern void sound_set_bgm(uint32_t music_id);



  asm("sound_set_bgm = 0x800CAA70");





extern void external_func_800FA0B4(void);



  asm("external_func_800FA0B4 = 0x800CAB18");





extern void debug_set_text_rgba(z64_debug_text_t *text_struct, uint8_t r, uint8_t g, uint8_t b, uint8_t a);



  asm("debug_set_text_rgba = 0x800CBE58");







extern void debug_set_text_xy(z64_debug_text_t *text_struct, int32_t x, int32_t y);



  asm("debug_set_text_xy = 0x800CBEC8");







extern void debug_init_text_struct(z64_debug_text_t *text_struct);



  asm("debug_init_text_struct = 0x800CC4AC");
# 8630 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800FBC14(z64_debug_text_t* t);



  asm("external_func_800FBC14 = 0x800CC500");
# 8643 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void debug_do_text_struct(z64_debug_text_t *text_struct, void *gfx_buffer);



  asm("debug_do_text_struct = 0x800CC508");







extern
void *
debug_update_text_struct(z64_debug_text_t *text_struct);



  asm("debug_update_text_struct = 0x800CC550");







extern void debug_set_text_string(z64_debug_text_t *text_struct, const char *format, ...);



  asm("debug_set_text_string = 0x800CC588");







extern void z_overlay_do_relocation(void* overlay_file, void* overlay_header, void* vram_start);



  asm("z_overlay_do_relocation = 0x800CC8F0");







extern void external_func_800FCC6C(void);



  asm("external_func_800FCC6C = 0x800CCED4");




extern float z_tanf(float x);
# 8713 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_floorf(float x);
# 8724 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_ceilf(float x);
# 8735 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_roundf(float x);
# 8746 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_truncf(float x);
# 8757 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_nearby_int_f(float x);
# 8770 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_atanf_taylor_q(float x);
# 8781 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_atanf_taylor(float x);
# 8791 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_atanf_cfrac(float x);



  asm("z_atanf_cfrac = 0x800CD648");






extern float z_atanf(float x);
# 8813 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_atan2f_2(float y, float x);



  asm("z_atan2f_2 = 0x800CD76C");






extern void z_asinf(float x);
# 8835 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void z_acosf(float x);



  asm("z_acosf = 0x800CD890");





extern float z_fp_floorf(float x);
# 8855 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern double z_fp_floor(double x);
# 8865 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_fp_lfloorf(float x);
# 8875 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_fp_lfloor(double x);
# 8907 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800FD7B4(void);



  asm("external_func_800FD7B4 = 0x800CDB00");







extern float z_math_rand_zero_one(void);



  asm("z_math_rand_zero_one = 0x800CDCCC");







extern int32_t external_func_800FD970(void);



  asm("external_func_800FD970 = 0x800CDC90");
# 8946 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t z_srand(uint32_t seed);



  asm("z_srand = 0x800CDCC0");







extern float z_sinf(
float angle
);



  asm("z_sinf = 0x800CF470");
# 8973 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_sqrt(float value);



  asm("z_sqrt = 0x800D0DC0");
# 8990 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern float z_cosf(float angle);



  asm("z_cosf = 0x800D2CD0");





extern int16_t z_coss_2(int16_t angle);



  asm("z_coss_2 = 0x800D2FA0");
# 9017 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
  static inline __attribute__((always_inline)) float z_fabs(float value) {
   if (value < 0)
    return -value;
   return value;
  }
# 9035 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
  static inline __attribute__((always_inline)) float z_fmod(float a, float b) {
   if (b == 0.00000000)
    a = 0.00000000;
   else
    a = a - (a / b) * b;
   return a;
  }





extern void external_func_80106AA8(void);



  asm("external_func_80106AA8 = 0x800D5FEC");
# 9062 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int32_t player_responded_to_textbox(z64_global_t *global);



        asm("player_responded_to_textbox = 0x800D6110");





extern void external_func_80106CCC(void);



  asm("external_func_80106CCC = 0x800D6218");
# 9089 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void textbox_begin(z64_global_t *, uint16_t text_id, z64_actor_t *actor);



  asm("textbox_begin = 0x800DCE14");
# 9102 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void textbox_continue(z64_global_t *global, uint16_t text_id);



  asm("textbox_continue = 0x800DCE80");







extern void external_func_8010BD58(void);



  asm("external_func_8010BD58 = 0x800DD400");







extern void external_func_8010BD88(void);



  asm("external_func_8010BD88 = 0x800DD430");







extern uint32_t player_talk_state(z64_global_t *gl_20D8);



  asm("player_talk_state = 0x800DD464");





extern void external_func_800F64E0(uint32_t onoff);
# 9157 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void external_func_800418D0(uint32_t global7C0,z64_global_t *global);







extern void save_flags(z64_global_t *global);







extern void save_game(uint32_t global1F74,z64_global_t *global);
# 9182 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern uint32_t player_refresh_equipment(z64_global_t *global, z64_actor_t *actor);



  asm("player_refresh_equipment = 0x80079764");
# 9195 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern int z_tri_line_intersect(vec3f_t* v0, vec3f_t* v1, vec3f_t* v2, float nx, float ny, float nz, float originDist, vec3f_t* lineStart, vec3f_t* lineEnd, vec3f_t* intersectionPoint, int arg);

   asm("z_tri_line_intersect = 0x800A80D0");
# 9206 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guScale(Mtx* m, float x, float y, float z);
# 9217 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guPerspectiveF(
 float mf[4][4]
 , uint16_t* perspNorm, float fovy, float aspect
 , float near, float far, float scale
);
# 9232 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guPerspective(
 Mtx* m
 , uint16_t* perspNorm, float fovy, float aspect
 , float near, float far, float scale
);
# 9247 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guMtxIdentF(float mf[4][4]);
# 9258 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guLookAtF(
 float mf[4][4],
 float xEye, float yEye, float zEye
 , float xAt, float yAt, float zAt
 , float xUp, float yUp, float zUp
);
# 9274 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guLookAt(
 Mtx* m,
 float xEye, float yEye, float zEye
 , float xAt, float yAt, float zAt
 , float xUp, float yUp, float zUp
);
# 9290 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guLookAtHiliteF(
 float mf[4][4], LookAt* l, Hilite* h
 , float xEye, float yEye, float zEye
 , float xAt, float yAt, float zAt
 , float xUp, float yUp, float zUp
 , float xl1, float yl1, float zl1
 , float xl2, float yl2, float zl2
 , int32_t hiliteWidth, int32_t hiliteHeight
);
# 9309 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guLookAtHilite(
 Mtx* m, LookAt* l, Hilite* h
 , float xEye, float yEye, float zEye
 , float xAt, float yAt, float zAt
 , float xUp, float yUp, float zUp
 , float xl1, float yl1, float zl1
 , float xl2, float yl2, float zl2
 , int32_t hiliteWidth, int32_t hiliteHeight
);
# 9328 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guMtxIdent(Mtx* m);
# 9339 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guPositionF(float mf[4][4], float rot, float pitch, float yaw, float scale, float x, float y, float z);
# 9350 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guPosition(Mtx* m, float rot, float pitch, float yaw, float scale, float x, float y, float z);
# 9361 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guRotateF(float mf[4][4], float a, float x, float y, float z);
# 9372 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guRotate(Mtx* m, float a, float x, float y, float z);
# 9383 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guNormalize(float x, float y, float z);
# 9394 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guOrthoF(float mf[4][4], float left, float right, float bottom, float top, float near, float far, float scale);
# 9405 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guOrtho(Mtx* m, float left, float right, float bottom, float top, float near, float far, float scale);
# 9416 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guTranslate(Mtx* m, float x, float y, float z);
# 9427 "/opt/n64/mips64/include/z64ovl/z64_functions.h" 3
extern void guMtxF2L(float mf[4][4], Mtx* m);
# 31 "/opt/n64/mips64/include/z64ovl/oot/u10.h" 2 3
# 2 "boot_load_statics.c" 2


# 3 "boot_load_statics.c"
extern void DmaMgr_Init();
extern void Main(void*);
extern u32 osGetMemSize(void);

extern u32 statics_START;

typedef struct {
   void* vrom;
   void* vram;
   u32 size;
} DmaRequest;
# 22 "boot_load_statics.c"
void func_800005A0(void* arg0) {
    static DmaRequest rhstaticsFile = { (void*)0xDEADBEEF, &statics_START, 0x04206969 };

    DmaMgr_Init();
    
# 26 "boot_load_statics.c" 3
   load_data_from_rom(
# 26 "boot_load_statics.c"
   (void*)0x800110A0
# 26 "boot_load_statics.c" 3
   , 
# 26 "boot_load_statics.c"
   (void*)0x00A87000
# 26 "boot_load_statics.c" 3
   , 
# 26 "boot_load_statics.c"
   (void*)0x00B8AD30 - (void*)0x00A87000
# 26 "boot_load_statics.c" 3
   )
# 26 "boot_load_statics.c"
                                                                                                             ;
    z_bzero((void*)0x80114DD0, (void*)0x8012BE30 - (void*)0x80114DD0);





    z_file_load(&rhstaticsFile);

    Main(arg0);
}
