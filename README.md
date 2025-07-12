# JC8012P4A1 Display & Touch Demo (ESP32-P4)

This project demonstrates how to bring up the JD9365-based MIPI DSI display and GSL3680 capacitive touch controller on the JC8012P4A1 board using Arduino.

## Features

- 10.1" JD9365 800x1280 MIPI DSI LCD display
- GSL3680 I2C capacitive touch support
- Backlight control via PWM (GPIO 23)
- Display updates using Arduino_GFX + ESP32-P4 DSI peripheral
- Touchpoint visualization (draws circle on touch)
- Basic Wi-Fi connectivity

## Hardware

- **Board:** JC8012P4A1 (ESP32-P4-based dev board)
- **Display:** JD9365 over 2-lane MIPI DSI
- **Touch:** GSL3680 over I2C
- **Backlight:** Controlled via PWM on GPIO 23
- **Optional:** Camera support (not yet configured)

## Pin Configuration

| Function   | GPIO |
|------------|------|
| LCD Reset  | 27   |
| Backlight  | 23   |
| Touch SDA  | 7    |
| Touch SCL  | 8    |
| Touch RST  | 22   |
| Touch INT  | 21   |

## Setup

1. Clone this repo and open in PlatformIO
2. Copy-paste and adjust the following code into a new file `src/secrets.hpp`.  
```c++
#pragma once

constexpr const char SSID[] = "network name";
constexpr const char PSK[] = "network password";
```
3. Upload to the board — you should see the screen light up and respond to touch

## Libraries Used

- [`Arduino_GFX`](https://github.com/moononournation/Arduino_GFX)
- `esp_lcd_touch` (for GSL3680 driver, via ESP-IDF integration)
- `esp32-hal-ledc` (PWM backlight)

## To Do

- [ ] Add double buffering or frame sync to reduce tearing
- [ ] Integrate camera (if supported)
- [ ] Optional: Add LVGL support with input & widgets
