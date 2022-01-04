ESP8266 WiFi Auto Config
===========================

This is an example of using WiFi auto config on ESP8266.

With the `ESP8266AutoConfig.h` included, you can conenct to WiFi by simply
calling `ESP8266AutoConfig.connectWiFi(true)` without providing the SSID and the
passphrase. `ESP8266AutoConfig` will put ESP8266 into AP mode so that the user
can connect to it and provide the SSID and passphrase with browser.
Once the SSID and the passphrase are provided, they will be stored in EEPROM
and used for connecting WiFi.

Example:

```cpp
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

```

