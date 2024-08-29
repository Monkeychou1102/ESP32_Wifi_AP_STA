// checkMAC.ino

#include "WiFi.h"
#include <String.h>

void setup()
{
    Serial.begin(115200);
    Serial.println("");
    Serial.print("MAC Address : ");
    Serial.println(WiFi.macAddress()); // Get MAC Address
}

void loop()
{
    delay(1000);
}
