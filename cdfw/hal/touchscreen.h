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

namespace cdfw {
namespace hal {
class Touchscreen {
public:
  virtual ~Touchscreen() = default;
  virtual bool Touched() = 0;
  virtual Point GetPoint() = 0;

  // Callback for reading the touchscreen.
  virtual void ReadCallback(lv_indev_t *indev, lv_indev_data_t *data) = 0;

  // Routes a read event to the appropriate instance.
  static void ReadCallbackRouter(lv_indev_t *indev, lv_indev_data_t *data);

  // private:
  //   Touchscreen(Touchscreen const&) = default;
  //   Touchscreen& operator=(Touchscreen const&) = default;
};
} // namespace hal
} // namespace cdfw

#endif // CDFW_HAL_TOUCHSCREEN_H
