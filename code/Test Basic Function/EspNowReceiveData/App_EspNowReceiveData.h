#ifndef _APP_ESPNOWRECEIVEDATA_H
#define _APP_ESPNOWRECEIVEDATA_H

#include "Sys_Init.h"

void Init_EspNowReceiveData(void);
void App_EspNowReceiveData(void);
void ReceiveData(const uint8_t *mac, const uint8_t *incomingData, int len);

#endif