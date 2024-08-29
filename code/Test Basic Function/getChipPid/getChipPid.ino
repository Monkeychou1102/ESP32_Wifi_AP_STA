// getChipPid.ino

#include "WiFi.h"
#include <String.h>

uint64_t chipId = 0;
char chip_ID[19] = {0};

void setup()
{
    uint16_t val = 0;

    Serial.begin(115200);

    Serial.println("111111111111111111111111"); // Debug Indicator

    // MAC Aress
    Serial.print("MAC Address : ");
    Serial.println(WiFi.macAddress()); // Get MAC Address

    // Chip ID
    chipId = ESP.getEfuseMac(); // Chip ID is the same as MAC address (6 bytes)

    Serial.println("222222222222222222222222"); // Debug Indicator

    Serial.printf("ESP32 Chip ID = %04X", (uint16_t)(chipId >> 32)); // Print high 2 bytes
    Serial.printf(" %08X\n", (uint32_t)chipId);                      // Print low 4 bytes

    // Save read chip id to array
    val = (uint16_t)(chipId >> 32); // Get high 2 bytes

    Serial.println("3333333333333333333333333"); // Debug Indicator

    // Save high 2 bytes (= 4 numbers) + low 4 bytes (= 8 numbers) numbers from two parts (val + chipId)
    // ESP32-(4 numbers)(8 number numbers) -> Total 18 mumbers
    snprintf(chip_ID, sizeof(chip_ID), "ESP32-%04X%08X", val, (uint32_t)chipId);

    Serial.println("4444444444444444444444444"); // Debug Indicator

    Serial.print("CHIP ID = ");
    Serial.println(chip_ID);

    /* ------------- TEST REULT --------------------

    111111111111111111111111
    MAC Address : C8:C9:A3:FA:0C:88

    222222222222222222222222
    ESP32 Chip ID = 880C FAA3C9C8

    3333333333333333333333333

    4444444444444444444444444
    CHIP ID = ESP32-880CFAA3C9C8

    */
}

void loop()
{
    delay(1000);
}
