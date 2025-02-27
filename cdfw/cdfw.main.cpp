// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Main file for Horolibre Cleaner display firmware.

#ifndef PIO_UNIT_TESTING

// Local Headers
#include "cdfw/compat/arduino.h"
#include "cdfw/core/core.h"
#include "cdfw/gui/gui.h"
#include "cdfw/hal/hal.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdint>
#include <iostream>
#include <memory>

namespace cdfw {
// Hawdware.
std::unique_ptr<hal::Touchscreen> touchscreen = nullptr;
std::shared_ptr<vfs::Volume> sd = nullptr;

// Presenters.
std::unique_ptr<core::ui::AppPresenter> app_presenter = nullptr;

void InitHardware() {
  Serial.begin(115200);

  // Initialise LVGL.
  lv_init();
  // mem_report();

  // Hardware is initialized on creation.
  touchscreen = hal::Touchscreen::Create();
  sd = hal::SD::CreateVolume();

  // Initialize app directories.
  // sd->RemoveAll("/sd/"); // TEMP: Clear the SD card.
  DirManager(sd).CreateDirs(sd->MountPoint());

  // Playing around with SD card functionality.
  // Note: This section is temporary.
  sd->PrintInfo();
  sd->Walk();
}

void InitGUI() {
  // The boot screen is shown as soon as it is initialized. After that, we have
  // no use for the wrapping classes, so we let them destruct after use.
  core::ui::BootPresenter::Create(gui::screen::BootView::Create(),
                                  core::ui::BootModel::Create())
      ->Init();

  // Initialize the other GUI components.
  auto settings_model = core::ui::SettingsModel::Create();
  app_presenter = core::ui::AppPresenter::Create(
      core::ui::HomePresenter::Create(
          gui::screen::HomeView::Create(),
          core::ui::HomeModel::Create(settings_model)),
      core::ui::CleanPresenter::Create(gui::screen::CleanView::Create(),
                                       core::ui::CleanModel::Create()),
      core::ui::RoutinesPresenter::Create(gui::screen::RoutinesView::Create(),
                                          core::ui::RoutinesModel::Create()),
      core::ui::SettingsPresenter::Create(gui::screen::SettingsView::Create(),
                                          settings_model));
  app_presenter->Init();

  // Initialization for the home screen queues a delayed show.
  app_presenter->ShowHomeDelayed();
}
} // namespace cdfw

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

#ifdef ARDUINO
void setup() {
#else  // ARDUINO
int main() {
#endif // ARDUINO

  cdfw::InitHardware();
  cdfw::InitGUI();

#ifndef ARDUINO
  while (true) {
    loop();
  }
  return 0;
#endif // ARDUINO
}

#endif // PIO_UNIT_TESTING