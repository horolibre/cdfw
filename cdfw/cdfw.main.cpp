// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Main file for Horolibre Cleaner display firmware.

#ifndef PIO_UNIT_TESTING

// Local Headers
#include "cdfw/core/core.h"
#include "cdfw/gui/gui.h"
#include "cdfw/hal/hal.h"
#include "cdfw/hw/hw.h"

// Third Party Headers
#include <lvgl.h>
#ifdef CDFW_NATIVE
#include <SDL2/SDL.h>
#endif // CDFW_NATIVE

// C++ Standard Library Headers
#include <cstdint>
#include <memory>

namespace {
// Static device pointers.
cdfw::hal::Touchscreen *touchscreen = nullptr;

std::shared_ptr<cdfw::core::ui::SettingsModel> settings_model = nullptr;
std::unique_ptr<cdfw::core::ui::HomePresenter> home_presenter = nullptr;
} // namespace

#ifdef ARDUINO
void setup() {

#else  // ARDUINO
void loop(); // Forward declaration of the loop function.
int main() {
#endif // ARDUINO

  Serial.begin(115200);

  // Initialise LVGL.
  cdfw::hw::lvgl::Init();
  mem_report();

  // Initialise devices.
  touchscreen = cdfw::hw::touchscreen::Create();

  // The boot screen is shown as soon as it is initialized. After that, we have
  // no use for the wrapping classes, so we let them destruct after use.
  cdfw::core::ui::BootPresenter::Create(cdfw::gui::screen::BootView::Create(),
                                        cdfw::core::ui::BootModel::Create())
      ->Init();

  settings_model = cdfw::core::ui::SettingsModel::Create();
  home_presenter = cdfw::core::ui::HomePresenter::Create(
      cdfw::gui::screen::HomeView::Create(),
      cdfw::core::ui::HomeModel::Create(settings_model));
  // Initialization for the home screen queues a delayed show.
  home_presenter->Init();

#ifndef ARDUINO
  while (true) {
    loop();
  }
#endif // ARDUINO
}

void loop() {
  static std::uint32_t last_tick = 0; // Used to track the tick timer.

  // Update the tick timer.
  lv_tick_inc(millis() - last_tick);
  last_tick =
#ifdef CDFW_NATIVE
      SDL_GetTicks();
#else  // CDFW_NATIVE
      millis();
#endif // CDFW_NATIVE

  // Update the UI.
  lv_timer_handler();

  // Delay seems to be suggested by others online, but I'm not sure on its
  // purpose/implications. Therefore, I'm currently not able to make a judgement
  // call on the delay time.
#ifdef CDFW_NATIVE
  SDL_Delay(5);
#else  // CDFW_NATIVE
  delay(5);
#endif // CDFW_NATIVE
}

#endif // PIO_UNIT_TESTING