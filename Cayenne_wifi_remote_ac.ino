#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>
//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTESP8266.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

// WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "wifiPassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";


/*/ WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "wifiPassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";
*/

#define VIRTUAL_CHANNEL 1
#define ACTUATOR_PIN 4 // Do not use digital pins 0 or 1 since those conflict with the use of Serial.


IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.


void setup()
{
  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop()
{
  Cayenne.loop();
}

CAYENNE_IN(V3) { // send volume -
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x20238C7);
    delay(40);
  }
}

CAYENNE_IN(V4) { // send volume +
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x202A857);
    delay(40);
  }
}

CAYENNE_IN(V5) { // send program +
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x202D02F);
    delay(40);
  }
}

CAYENNE_IN(V6) { // send program -
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x202708F);
    delay(40);
  }
}

CAYENNE_IN(V7) { // send power on/off
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0xFEA857);
    delay(40);
  }
}


CAYENNE_IN(V8) { // send AC power on-summer
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0xB2BF90);
    delay(40);
  }
}


CAYENNE_IN(V9) { // send AC power off
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0xB27BE0);
    delay(40);
  }
}
