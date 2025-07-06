#pragma once
#include <LovyanGFX.hpp>

class LGFX_JD9365 : public lgfx::LGFX_Device {
  lgfx::Panel_MIPI_Custom _panel;

public:
  LGFX_JD9365() {
    {
      auto cfg = _panel.config_panel();
      cfg.memory_width  = 800;
      cfg.memory_height = 1280;
      cfg.panel_width   = 800;
      cfg.panel_height  = 1280;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.readable = false;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = false;
    }

    {
      auto cfg = _panel.config_mipi_dsi();
      cfg.freq = 416;         // PLL_CLOCK = 416MHz
      cfg.lanes = 2;          // 2-lane MIPI
      cfg.hsync_polarity = false;
      cfg.vsync_polarity = false;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 20;
      cfg.hsync_back_porch = 20;
      cfg.vsync_front_porch = 20;
      cfg.vsync_pulse_width = 4;
      cfg.vsync_back_porch = 8;
      cfg.auto_flush = true;
    }

    // Panel init sequence from your file
    _panel.init_commands = {
      {0xE0, {0x00}}, {0xE1, {0x93}}, {0xE2, {0x65}}, {0xE3, {0xF8}},
      {0x80, {0x01}}, {0xE0, {0x01}}, {0x00, {0x00}}, {0x01, {0x39}},
      {0x03, {0x10}}, {0x04, {0x41}}, {0x0C, {0x74}},
      {0x17, {0x00}}, {0x18, {0xD7}}, {0x19, {0x00}}, {0x1A, {0x00}}, {0x1B, {0xD7}}, {0x1C, {0x00}},
      {0x24, {0xFE}}, {0x35, {0x26}}, {0x37, {0x69}}, {0x38, {0x05}}, {0x39, {0x06}}, {0x3A, {0x08}}, {0x3C, {0x78}},
      {0x3D, {0xFF}}, {0x3E, {0xFF}}, {0x3F, {0xFF}}, {0x40, {0x06}}, {0x41, {0xA0}}, {0x43, {0x14}}, {0x44, {0x0B}},
      {0x45, {0x30}}, {0x4B, {0x04}}, {0x55, {0x02}}, {0x57, {0x89}}, {0x59, {0x0A}}, {0x5A, {0x28}}, {0x5B, {0x15}},
      // ... continue translating from your init file
      {0x11, {}}, // Sleep Out
      {lgfx::CommandType::Delay, 120}, // Wait 120ms
      {0x29, {}}, // Display ON
      {lgfx::CommandType::Delay, 5},
      {0x35, {0x00}}, // Tearing Effect OFF?
    };

    _panel.rotation_offset = 0;
    setPanel(&_panel);
  }
};
