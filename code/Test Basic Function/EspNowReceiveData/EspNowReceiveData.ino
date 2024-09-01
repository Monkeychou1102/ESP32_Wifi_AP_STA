#include <WiFi.h>
#include <esp_now.h>

String val;

// Receive Data Callback Function
void ReceiveData(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&val, incomingData, sizeof(val));

  Serial.print("Received Data: ");
  Serial.println(val);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  // Wifi Mode = STA
  WiFi.mode(WIFI_STA);

  // Get MAC Address
  Serial.print("ESP32 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != 0)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
}

void loop()
{
  // Try to receive Data
  esp_now_register_recv_cb(ReceiveData);
  delay(500);
}
