#include "ESP8266AutoConfig.h"

#define RECONFIG_PIN 4

void setup() {

  // initialize serial debug port
  Serial.begin(115200);
  Serial.println();

  // connect IO4 to GND to reconfig WiFi
  pinMode(RECONFIG_PIN, INPUT_PULLUP);

  int reconfig = digitalRead(RECONFIG_PIN);
  if (reconfig == LOW) {
    ESP8266AutoConfig.startAp(true);
  } else {  
    // starting WiFi
    ESP8266AutoConfig.connectWiFi(true);
  }
}

// the loop function runs over and over again forever
void loop() {
  ESP8266AutoConfig.poll();
}
