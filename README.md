# ESP32 German Word Clock with NeoPixel LEDs
<img width="398" height="481" alt="image" src="https://github.com/user-attachments/assets/539d47d6-6ea0-4599-90a4-51635743f03b" />


This project is an **ESP32-based German word clock (Wortuhr)** using NeoPixel (WS2812B) LEDs.

Instead of displaying numbers, the clock shows the **current time in German words**, for example:

> **„ES IST FÜNF NACH DREI“**  
> (“It is five past three”)

The words are illuminated on a letter matrix using individually addressable LEDs.

The clock connects to WiFi and automatically synchronizes the time via **NTP**.  
WiFi credentials are configured through a **WiFiManager configuration portal**, so no credentials are hardcoded.

---

## ✨ Features

- ⏰ Displays time as **German words**
- 🌙 **Automatic brightness control**
  - Dimmed at night (22:00 – 06:00)
  - Bright during the day
- 📶 **WiFi configuration via WiFiManager**
- 🌍 **Automatic time synchronization via NTP**
- 🔘 Optional button to reset WiFi settings

---

## 🧰 Hardware

- **ESP32-C3**
- **NeoPixel LEDs (WS2812B)** – 60 LEDs per meter
- **Optional push button** (WiFi reset)

### Pin Assignment

| Component        | GPIO |
|------------------|------|
| NeoPixel Data    | GPIO 4 |
| Button (optional)| GPIO 5 |

---

## 📦 Software & Libraries

Required libraries:

- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [WiFiManager](https://github.com/tzapu/WiFiManager)

ESP32 / Arduino core libraries:

- `WiFi.h`
- `time.h`
- `nvs_flash.h`

Compatible with:
- **Arduino IDE**
- **PlatformIO**

---

## 🚀 Setup

1. Flash the firmware to the ESP32
2. Power the word clock
3. Open a browser and navigate to:  
   **http://192.168.1.4**
4. Configure your WiFi network
5. The clock synchronizes the time automatically and starts displaying it in **German words**

---

## 📝 Notes

- This is a **German word clock**  
  (uses German time rules like *„fünf nach“*, *„viertel vor“*, *„halb“*)
- The LED index layout must match the word matrix in the code
- Brightness levels and time logic can be adjusted in the source code

---

##DEMO

https://youtube.com/shorts/ShPfFWpKsJU?feature=share
