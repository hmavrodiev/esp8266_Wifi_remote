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

//#define VIRTUAL_CHANNEL 1
//#define ACTUATOR_PIN 4 // Do not use digital pins 0 or 1 since those conflict with the use of Serial.


IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
IRCoolixAC ac(kIrLed); 

void setup()
{
  Serial.begin(115200);
  irsend.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
 
}

void loop()
{
  Cayenne.loop();
}


CAYENNE_IN(1) { // send volume -
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x20238C7);
    delay(40);
  }
}

CAYENNE_IN(2) { // send volume +
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x202A857);
    delay(40);
  }
}

CAYENNE_IN(3) { // send program +
 irsend.sendNEC(0x202D02F);
}

CAYENNE_IN(4) { // send program -
 irsend.sendNEC(0x202708F);
}

CAYENNE_IN(0) { // send power on/off
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0xFEA857);
    delay(40);
  }
}


CAYENNE_IN(5) { // send AC power on-summer
  for (int i = 0; i < 3; i++) {
    irsend.sendCOOLIX(0xB2BF90);
    delay(40);
  }
}




CAYENNE_IN(6) { // send AC power off
  for (int i = 0; i < 3; i++) {
    irsend.sendCOOLIX(0xB27BE0);
    delay(40);
  }
}


CAYENNE_IN(7) { // send AC heat
  for (int i = 0; i < 3; i++) {
    irsend.sendCOOLIX(0xB2BF6C);
    delay(40);
  }
}

