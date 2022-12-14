#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "live_audio.h"

void initLibs() {
  if (djiGUILib == 0) {
    djiGUILib = dlopen("/system/lib/libtp1801_gui.so", 1);
  }

  if (ui_config == 0) {
    ui_config = (uint32_t *)*(uint32_t *)((int)getSettings() + 0xe4);
  }

  if (gs_get_uav_hardware_version == 0) {
    gs_get_uav_hardware_version = (void *)*(uint32_t *)((int) ui_config + 0x3a8);
  }

  if (hardware_info == 0) {
    hardware_info = (uint32_t *)*(uint32_t *)((int) ui_config + 0x4c);
  }

  if (gs_enable_audio_liveview == 0) {
    gs_enable_audio_liveview = (void *)*(uint32_t *)((int) ui_config + 0x3e0);
  }

  if (gs_modem_get_link_state_wrap == 0) {
    gs_modem_get_link_state_wrap = (void *)*(uint32_t *)((int) ui_config + 0x228);
  }
}

uint32_t getTimeout(void* this) {
   if (timeout == 0 && djiGUILib) {
      timeout = dlsym (djiGUILib, "_ZN19GlassRacingChnlMenu7timeOutEv");
      if (timeout == 0) {
        return 0;
      } else {
        return timeout(this);
      }
   } else {
     return timeout(this);
   }
}

uint32_t getSettings() {
   if (settings == 0 && djiGUILib) {
      settings = dlsym (djiGUILib, "_ZN17GlassUserSettings11getInstanceEv");
      if (settings == 0) {
        return 0;
      } else {
        return settings();
      }
   } else {
     return settings();
   }
}

void setLiveAudio(bool enable){
    restart = enable;
	printf("update live audio: %d\n", enable);
	gs_enable_audio_liveview(hardware_info, enable);
	printf("update live audio\n");
}

bool isAirUnitLite(){
	char hw_ver[16];
	memset(hw_ver, 0, 0x10);
	gs_get_uav_hardware_version(hardware_info, hw_ver);
	if(strncmp(hw_ver,"LT150 VT Ver.A",0x10) == 0) {
	  return true;
	}
	return false;
}

void updateConnection() {

    connection = GS_LINK_STAT_UKNOWN;
    gs_link_stat_t *connection_status = &connection;
    gs_modem_get_link_state_wrap(hardware_info, connection_status);
}

int32_t _ZN19GlassRacingChnlMenu7timeOutEv(void* this){
    initLibs();

	if(!isAirUnitLite()){
		updateConnection();

		if(connection != GS_LINK_STAT_NORMAL){
		   clock_gettime(CLOCK_MONOTONIC, &prev);
		} else {
		   clock_gettime(CLOCK_MONOTONIC, &now);
		}

		if ((now.tv_sec - prev.tv_sec) > 9) {
		   if(!restart  && connection == GS_LINK_STAT_NORMAL){
		     setLiveAudio(true);
		   }
		}

		if(restart && connection == GS_LINK_STAT_LOST){
		  setLiveAudio(false);
		}
	}
	return getTimeout(this);
}