
typedef struct {
    uint8_t ambientClrR, ambientClrG, ambientClrB;
    uint8_t diffuseClrA_R, diffuseClrA_G, diffuseClrA_B;
    uint8_t diffuseDirA_X, diffuseDirA_Y, diffuseDirA_Z;
    uint8_t diffuseClrB_R, diffuseClrB_G, diffuseClrB_B;
    uint8_t diffuseDirB_X, diffuseDirB_Y, diffuseDirB_Z;
    uint8_t fogClrR, fogClrG, fogClrB;
    uint16_t unk;
    uint16_t drawDistance;
} LightSettings;

typedef struct {
    uint8_t dummy[0xB4];
    uint8_t numLightSettings;
    LightSettings *lightSettingsList;
    uint8_t dummy2[0xE1 - 0xBC];
    uint8_t screenfadeEnable;
    uint8_t screenfadeColor[4];
    uint8_t dummy3[0xEE - 0xE6];
    uint8_t unk_EE[4]; //makes it rain
} EnvironmentContext_lights_t;

typedef struct {
    uint8_t dummy[0x10A24];
    EnvironmentContext_lights_t envCtx;
} GlobalContext_Env_t;
