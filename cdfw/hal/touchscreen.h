// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HAL_TOUCHSCREEN_H
#define CDFW_HAL_TOUCHSCREEN_H

// Interface for touchscreen devices.

// Local Headers
#include "cdfw/hal/point.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace hal {
// Representation of a touchscreen device.
// Initialization of this device should handle setting up the display as well as
// LVGL input device registration.
class Touchscreen {
public:
  // Factory method.
  static std::unique_ptr<Touchscreen> Create();

  // Virtual d'tor.
  virtual ~Touchscreen() = default;

  // Initializes the touchscreen device.
  virtual void Init() = 0;

  // Callback for reading the touchscreen.
  virtual void ReadCallback(lv_indev_t *indev, lv_indev_data_t *data) = 0;

  // Routes a read event to the appropriate instance.
  static void ReadCallbackRouter(lv_indev_t *indev, lv_indev_data_t *data);
};
} // namespace hal
} // namespace cdfw

#endif // CDFW_HAL_TOUCHSCREEN_H
