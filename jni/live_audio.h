#include <time.h>

typedef enum gs_link_stat_t {
    GS_LINK_STAT_NORMAL=0,
    GS_LINK_STAT_WEAK=1,
    GS_LINK_STAT_LOST=2,
    GS_LINK_STAT_UKNOWN=3
} gs_link_stat_t;

static int32_t (* gs_modem_get_link_state_wrap)(void *, enum gs_link_stat_t *) = 0;
static uint32_t (*gs_enable_audio_liveview)(void *_gs_info, bool b_enable) = 0;
static uint32_t (*gs_get_uav_hardware_version)(void *_gs_info, char *_hw_ver) = 0;
static void *djiGUILib = 0;
static uint32_t *hardware_info = 0;
static uint32_t *ui_config = 0;
static gs_link_stat_t connection;

struct timespec prev;
struct timespec now;
static bool restart = false;
static uint32_t (* timeout)(void *this) = 0;
static uint32_t (* settings)() = 0;
uint32_t getTimeout(void *this);
uint32_t getSettings();
void setLiveAudio(bool enable);
bool isAirUnitLite();
void initLibs();
void updateConnection();