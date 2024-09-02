#include "App_EspNowSendData.h"

// Set MAC Address of Receiver
#define MAC_ADDRESS_0 0xC8
#define MAC_ADDRESS_1 0xC9
#define MAC_ADDRESS_2 0xA3
#define MAC_ADDRESS_3 0xFA
#define MAC_ADDRESS_4 0x0C
#define MAC_ADDRESS_5 0x88

uint8_t Index_Send_Data = 0;
String SSD;

// Received Data
esp_now_peer_info_t peerInfo;

// Set Receiver MAC address
uint8_t Receiver_Mac_Address[6] = {MAC_ADDRESS_0, MAC_ADDRESS_1, MAC_ADDRESS_2, MAC_ADDRESS_3, MAC_ADDRESS_4, MAC_ADDRESS_5};
uint8_t Test_Array[6] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36};

// Callback Function - Send Data
void Send_Wifi_Data(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    char macStr[18];

    Serial.print("Packet to: ");

    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

    Serial.println(macStr);

    Serial.print("Send status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? SSD = "Delivery Success" : SSD = "Delivery Fail");

    if (status == ESP_NOW_SEND_SUCCESS)
    {
        Index_Send_Data = Index_Send_Data + 1; // Increasing index if success
    }
}

void Init_Esp_Now(void)
{
    // Initial ESP-NOW
    WiFi.mode(WIFI_STA);
    Serial.println("Try to initialize ESP-NOW function");

    // Check initial result?
    while (esp_now_init() != ESP_OK)
    {
        Serial.print(".");
        delay(500);
    }

    esp_now_register_send_cb(Send_Wifi_Data); // Set callback function

    Serial.println("Success to initialize ESP-NOW function");
}

void Check_Wifi_Connect_Status(esp_now_peer_info_t *wifiPeerInfo)
{
    Serial.println("Try to add peer");

    // Check machine connects to machine?
    while (esp_now_add_peer(wifiPeerInfo) != ESP_OK)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("Success to add peer");
}

void Init_EspNowSendData(void)
{
    Serial.begin(115200);

    Init_Esp_Now();

    memcpy(peerInfo.peer_addr, Receiver_Mac_Address, sizeof(Receiver_Mac_Address));
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    Check_Wifi_Connect_Status(&peerInfo);
}

void App_EspNowSendData(void)
{
    // If more than 1 ESP Receiver in used, then use different "MAC address" to send data.

    // Send Data 1 - Index Number
    String data1 = "Index = " + String(Index_Send_Data);
    Serial.println(data1);
    esp_err_t result_1 = esp_now_send(Receiver_Mac_Address, (uint8_t *)&data1, sizeof(data1));

    // Send Data 2 - Data
    esp_err_t result_2 = esp_now_send(Receiver_Mac_Address, (uint8_t *)&Test_Array, sizeof(Test_Array));

    // Check Sending Data Success?
    if (result_1 == ESP_OK && result_2 == ESP_OK)
    {
        Serial.println("Sent with success");
    }
    else
    {
        Serial.println("Error sending the data");
        Serial.println("Try to resend Data...");
    }
    delay(500);
}
