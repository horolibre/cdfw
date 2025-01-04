// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Main file for Horolibre Cleaner display firmware.

// Local Headers
#include "cdfw/gui/gui.h"
#include "cdfw/hal/hal.h"
#include "cdfw/hw/hw.h"

// Third Party Headers
#include <Arduino.h>
#include <lvgl.h>

// C++ Standard Library Headers
#include <array>
#include <cstdint>

namespace {
// Static device pointers.
cdfw::hal::Touchscreen *touchscreen = nullptr;
} // namespace

void setup() {
  Serial.begin(115200);

  // Initialise devices.
  touchscreen = cdfw::hw::touchscreen::Create();

  // Initialise LVGL.
  lv_init();

  // Initialise display driver.
  // Using the LVGL suggest 1/10th screen size for the draw buffer.
  static std::array<std::uint8_t, TFT_WIDTH * TFT_HEIGHT / 10> draw_buf = {0};
  lv_display_t *disp =
      lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, &draw_buf, draw_buf.size());
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

  // Initialize touchscreen driver.
  auto indev = lv_indev_create();
  lv_indev_set_user_data(indev, touchscreen);
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, &cdfw::hal::Touchscreen::ReadCallbackRouter);

  // Register GUI screens.
  cdfw::gui::screen::boot::Register();
  cdfw::gui::screen::home::Register();
}

void loop() {
  static std::uint32_t last_tick = 0; // Used to track the tick timer.

  // Update the tick timer.
  lv_tick_inc(millis() - last_tick);
  last_tick = millis();

  // Update the UI.
  lv_timer_handler();

  // Not sure why the delay.
  delay(5);
}
