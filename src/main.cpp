//#include <WiFi.h>

#include <Arduino_GFX_Library.h>

#include "touch/gsl3680_touch.h"
#include "touch/esp_lcd_touch.h"
#include "secrets.hpp"

#define TP_I2C_SDA 7
#define TP_I2C_SCL 8
#define TP_RST 22
#define TP_INT 21

const int rotation = 0;

/// see https://github.com/moononournation/Arduino_GFX/blob/master/examples/PDQgraphicstest/Arduino_GFX_dev_device.h

// https://docs.espressif.com/projects/esp-iot-solution/en/latest/display/lcd/lcd_screen_tearing.html

Arduino_ESP32DSIPanel *dsipanel = new Arduino_ESP32DSIPanel(
    20 /* hsync_pulse_width */,
    20 /* hsync_back_porch */,
    40 /* hsync_front_porch */,
    4 /* vsync_pulse_width */,
    8 /*vsync_back_porch  */,
    20 /* vsync_front_porch */,
    60000000 /* prefer_speed */);

Arduino_DSI_Display *gfx = new Arduino_DSI_Display(
    800 /* width */,
    1280 /* height */,
    dsipanel,
    rotation /* rotation */,
    true /* auto_flush */,
    27 /* RST */,
    jd9365_init_operations, sizeof(jd9365_init_operations) / sizeof(lcd_init_cmd_t));

gsl3680_touch touch(TP_I2C_SDA, TP_I2C_SCL, TP_RST, TP_INT);

void setup()
{
    Serial.begin(115200);
    //WiFi.begin(SSID, PSK);

    if (!gfx->begin())
    {
        Serial.println("Failed to init display!");
        while (true)
            delay(1);
    }

    log_i("Display initialized");

    gfx->setCursor(10, 10);
    gfx->setFont();
    gfx->setTextSize(1);
    gfx->print("Hello world!");

    touch.begin();
    touch.set_rotation(rotation);

    constexpr int BACKLIGHT_PIN = 23;
    constexpr int BIT_DEPTH = 14;
    constexpr int MAX_PWM_VAL = 1 << BIT_DEPTH;
    if (!ledcAttachChannel(BACKLIGHT_PIN, 1220, BIT_DEPTH, 0))
    {
        log_e("Error setting ledc pin %i. system halted", index);
        while (1)
            delay(1000);
    }

    if (!ledcWrite(BACKLIGHT_PIN, MAX_PWM_VAL >> 3))
    {
        log_e("Error setting ledc value. system halted");
        while (1)
            delay(1000);
    }

    log_i("WiFi waiting for %s", SSID);

    // while (!WiFi.isConnected())
    // delay(10);

    log_i("entering loop");
}

void loop()
{
    uint16_t x, y;
    if (touch.getTouch(&x, &y))
    {
        gfx->fillCircle(x, y, 10, RED);
    }
}
