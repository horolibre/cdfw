// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_NATIVE

// Local Headers
#include "cdfw/hw/native/touchscreen.h"
#include "cdfw/hal/point.h"
#include "cdfw/hal/touchscreen.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdint>

namespace cdfw {
namespace hw {
namespace touchscreen {
namespace native {
namespace {
hal::Point Rotate(hal::Point point) {
  if (point.x == 0 && point.y == 0) {
    return hal::Point(-1, -1);
  }
  // Currently assumes LV_DISPLAY_ROTATION_90.
  return hal::Point(point.y, CDFW_SCR_H - point.x - 1);
}

class Touchscreen : public hal::Touchscreen {
public:
  Touchscreen() {}

  virtual ~Touchscreen() {}

  void Init() {}

  virtual bool Touched() override final { return false; }

  virtual hal::Point GetPoint() override final {
    return Rotate(hal::Point(0, 0));
  }

  virtual void ReadCallback(lv_indev_t *indev,
                            lv_indev_data_t *data) override final {
    if (Touched()) {
      hal::Point p = GetPoint();
      data->point.x = p.x;
      data->point.y = p.y;
      data->state = LV_INDEV_STATE_PRESSED;
    } else {
      data->state = LV_INDEV_STATE_RELEASED;
    }
  }
};
} // namespace

hal::Touchscreen *Create() {
  auto touchscreen = new native::Touchscreen();
  touchscreen->Init();
  return touchscreen;
}
} // namespace native
} // namespace touchscreen
} // namespace hw
} // namespace cdfw

#endif // CDFW_NATIVE