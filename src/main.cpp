// #include <WiFi.h>

#include <Arduino_GFX_Library.h>
#include "Arduino_GFX_dev_device.h"
#include "DejaVu40-modded.h"

#include "touch/gsl3680_touch.h"
#include "touch/esp_lcd_touch.h"
// #include "secrets.hpp" // untracked file containing Wifi SSID and PSK

#define TP_I2C_SDA 7
#define TP_I2C_SCL 8
#define TP_RST 22
#define TP_INT 21

const int rotation = 0;

// https://docs.espressif.com/projects/esp-iot-solution/en/latest/display/lcd/lcd_screen_tearing.html

gsl3680_touch touch(TP_I2C_SDA, TP_I2C_SCL, TP_RST, TP_INT);

void setup()
{
    Serial.begin(115200);
    // WiFi.begin(SSID, PSK);

    if (!gfx->begin())
    {
        Serial.println("Failed to init display!");
        while (true)
            delay(1);
    }

    Serial.println("Display initialized");

    gfx->setFont(&DejaVu40Modded);
    gfx->setTextSize(1);
    String str = "Hello world from JC8012P4A1!";
    int16_t x, y, x1, y1;
    uint16_t w, h;
    gfx->getTextBounds(str, x, y, &x1, &y1, &w, &h);
    gfx->setCursor((gfx->width() / 2 - (w / 2)), (gfx->height() / 2) - (h / 2));
    gfx->print(str);

    touch.begin();
    touch.set_rotation(rotation);

    constexpr int BIT_DEPTH = 14;
    constexpr int MAX_PWM_VAL = (1 << BIT_DEPTH) - 1;
    if (!ledcAttachChannel(GFX_BL, 1220, BIT_DEPTH, 0))
    {
        Serial.printf("Error setting ledc pin %i. system halted", index);
        while (1)
            delay(1000);
    }

    if (!ledcWrite(GFX_BL, MAX_PWM_VAL >> 3))
    {
        Serial.printf("Error setting ledc value. system halted");
        while (1)
            delay(1000);
    }

    // Serial.printf("WiFi waiting for %s\n", SSID);

    // while (!WiFi.isConnected())
    // delay(10);

    Serial.println("entering loop");
}

void loop()
{
    uint16_t x, y;
    while (touch.getTouch(&x, &y))
    {
        gfx->fillCircle(x, y, 10, RED);
    }
}
