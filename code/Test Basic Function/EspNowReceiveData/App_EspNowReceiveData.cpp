#include "App_EspNowReceiveData.h"

String val;

// Receive Data Callback Function
void ReceiveData(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&val, incomingData, sizeof(val));

    Serial.print("Received Data: ");
    Serial.println(val);
}

void Init_EspNowReceiveData(void)
{
    Serial.begin(115200);
    Serial.println();

    // Wifi Mode = STA
    WiFi.mode(WIFI_STA);

    // Get MAC Address
    Serial.print("ESP32 Board MAC Address:  ");
    Serial.println(WiFi.macAddress());

    while (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        delay(500);
    }
}

void App_EspNowReceiveData(void)
{
    // Try to receive Data
    esp_now_register_recv_cb(ReceiveData);
    delay(500);
}