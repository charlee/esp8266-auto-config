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



## Usage

First of all, 

```cpp
#include "ESP8266AutoConfig.h"
```

Then call `ESP8266AutoConfig.connectWiFi(true)` in the `setup()`. This will try
to read the WiFi config from EEPROM. If config unavailable, it will put ESP8266
in AP mode with the SSID "ESP8266". The user can connect to the "ESP8266" AP, and
provide the WiFi config page by accesing `http://192.168.4.1` with any browser.
Once a valid SSID and a passphrase are provided, ESP8266 will store them in EEPROM
and try to reconnect to WiFi.

Also, `ESP8266AutoConfig.poll()` needs to be called in the `loop()` to make the 
AP mode web server work.

The minimal setup is as follows.

```cpp
void setup() {
  ESP8266AutoConfig.connectWiFi(true);
}

void loop() {
  ESP8266AutoConfig.poll();
}
```

By calling `ESP8266AutoConfig.connectWiFi(true)` will do everything above
automatically. If you prefer doing these manually, you can call it without the
`true` argument:


```cpp
void setup() {
  bool connected = ESP8266AutoConfig.connectWiFi();
  if (!connected) {
    // we recommend to call `startAp(true)`. If `true` not provided,
    // the user needs to manually reset ESP8266 once the SSID and passphrase are set.
    ESP8266AutoConfig.startAp(true);
  }
}

void loop() {
  ESP8266AutoConfig.poll();
}
```

If you need to reconfigure WiFi, use a push button to connect any IO port to GND,
and test it in the `setup()`:

```cpp
#include "ESP8266AutoConfig.h"

#define RECONFIG_PIN 4

void setup() {
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
```
