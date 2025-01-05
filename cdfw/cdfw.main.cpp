// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Main file for Horolibre Cleaner display firmware.

// Local Headers
#include "cdfw/core/core.h"
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

std::unique_ptr<cdfw::core::ui::HomePresenter> home_presenter = nullptr;
//std::unique_ptr<cdfw::gui::screen::HomeView> home_view = nullptr;
} // namespace

#ifndef PIO_UNIT_TESTING

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

  // The boot screen is shown as soon as it is initialized. After that, we have
  // no use for the wrapping classes, so we let them destruct after use.
  cdfw::core::ui::BootPresenter::Create(cdfw::gui::screen::BootView::Create(),
                                        cdfw::core::ui::BootModel::Create())
      ->Init();

  home_presenter = cdfw::core::ui::HomePresenter::Create(
      cdfw::gui::screen::HomeView::Create(),
      cdfw::core::ui::HomeModel::Create());
  // Initialization for the home screen queues a delayed show.
  home_presenter->Init();
}

void loop() {
  static std::uint32_t last_tick = 0; // Used to track the tick timer.

  // Update the tick timer.
  lv_tick_inc(millis() - last_tick);
  last_tick = millis();

  // Update the UI.
  lv_timer_handler();

  // Delay seems to be suggested by others online, but I'm not sure on its
  // purpose/implications. Therefore, I'm currently not able to make a judgement
  // call on the delay time.
  delay(5);
}

#endif // PIO_UNIT_TESTING