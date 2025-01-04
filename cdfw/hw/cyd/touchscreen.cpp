// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/hw/cyd/touchscreen.h"
#include "cdfw/hal/point.h"
#include "cdfw/hal/touchscreen.h"

// Third Party Headers
#include <XPT2046_Bitbang.h>
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdint>

// Touchscreen SPI pins.
#define XPT2046_CLK 25
#define XPT2046_CS 33
#define XPT2046_IRQ 36
#define XPT2046_MISO 39
#define XPT2046_MOSI 32

namespace cdfw {
namespace hw {
namespace touchscreen {
namespace cyd {
namespace {
struct XPT2046PointAdaptor : public hal::Point {
  XPT2046PointAdaptor(TouchPoint point) : hal::Point(point.x, point.y) {}
};

hal::Point Rotate(hal::Point point) {
  if (point.x == 0 && point.y == 0) {
    return hal::Point(-1, -1);
  }
  // Currently assumes LV_DISPLAY_ROTATION_90.
  return hal::Point(point.y, TFT_HEIGHT - point.x - 1);
}

class Touchscreen : public hal::Touchscreen {
public:
  Touchscreen()
      : driver_(XPT2046_Bitbang(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK,
                                XPT2046_CS)) {}

  virtual ~Touchscreen() {}

  void Init() { driver_.begin(); }

  virtual bool Touched() override final { return driver_.getTouch().zRaw != 0; }

  virtual hal::Point GetPoint() override final {
    return Rotate(XPT2046PointAdaptor(driver_.getTouch()));
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

private:
  XPT2046_Bitbang driver_;
};
} // namespace

hal::Touchscreen *Create() {
  auto touchscreen = new cyd::Touchscreen();
  touchscreen->Init();
  return touchscreen;
}
} // namespace cyd
} // namespace touchscreen
} // namespace hw
} // namespace cdfw
