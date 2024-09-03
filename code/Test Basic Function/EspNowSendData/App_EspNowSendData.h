#ifndef _APP_ESPNOWSENDDATA_H
#define _APP_ESPNOWSENDDATA_H

#include "Sys_Init.h"

void Init_Esp_Now(void);
void Send_Wifi_Data(const uint8_t *mac_addr, esp_now_send_status_t status);
void Check_Wifi_Connect_Status(esp_now_peer_info_t *wifiPeerInfo);
void Init_EspNowSendData(void);
void App_EspNowSendData(void);

#endif
