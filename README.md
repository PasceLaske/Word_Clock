# ESP32 Wortuhr mit NeoPixel LEDs

Dies ist ein ESP32-Projekt, das eine Wortuhr steuert. Die Uhr zeigt die aktuelle Uhrzeit in Wörtern an, z. B. „Es ist fünf nach drei“, mit NeoPixel-LEDs.

Die Uhr nutzt WiFi zur Zeitsynchronisation über NTP. Außerdem kann das WLAN über ein Konfigurations-Portal (`WiFiManager`) eingerichtet werden.

---

## Funktionen

- Anzeige der Uhrzeit in **Wörtern** auf einer LED-Matrix oder LED-Kette
- **Automatische Helligkeit**: gedimmt nachts (22:00–6:00) und hell tagsüber
- **WLAN-Konfiguration über WiFiManager**: falls noch kein WLAN gespeichert ist
- **Zeitsynchronisation über NTP** für genaue Uhrzeit

---

## Hardware

- **ESP32 C3**
- **NeoPixel LEDs** (WS2812B 60 Leds/M)
- **Button** zum Löschen der gespeicherten WLAN-Daten (optional)

**Anschlüsse:**

| Komponente     | Pin     |
|----------------|---------|
| NeoPixel Daten | GPIO 4  |
| Button         | GPIO 5  |



## Software / Libraries

Benötigt:

- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [WiFiManager](https://github.com/tzapu/WiFiManager)
- ESP32/ESP8266 Board Definitions (Arduino IDE oder PlatformIO)
- Standard ESP32/Arduino Bibliotheken: `WiFi.h`, `time.h`, `nvs_flash.h`


##Setup
-Code auf Esp flashen
-Uhr einstecken und auf https://192.168.1.4 gehen
-Wlan konfigurieren
-Uhr stellt sich automatisch ein
