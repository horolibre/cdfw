// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_CYD

// Local Headers
#include "cdfw/hal/point.h"
#include "cdfw/hal/touchscreen.h"

// Third Party Headers
#include <XPT2046_Bitbang.h>
#include <lvgl.h>

// C++ Standard Library Headers
#include <array>
#include <cstdint>
#include <memory>

// Touchscreen SPI pins.
#define XPT2046_CLK 25
#define XPT2046_CS 33
#define XPT2046_IRQ 36
#define XPT2046_MISO 39
#define XPT2046_MOSI 32

namespace cdfw {
namespace hal {
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

  virtual void Init() override final {
    // Initialize the touchscreen driver.
    driver_.begin();

    // Register the display with LVGL.
    // Using the LVGL suggest 1/10th screen size for the draw buffer.
    // Note: The buffer must be aligned to LV_DRAW_BUF_ALIGN, otherwise setting
    // the displauy buffer will fail.
    alignas(LV_DRAW_BUF_ALIGN) static std::array<std::uint8_t,
                                                 CDFW_SCR_W * CDFW_SCR_H / 10>
        draw_buf = {0};
    lv_display_t *disp =
        lv_tft_espi_create(CDFW_SCR_W, CDFW_SCR_H, &draw_buf, draw_buf.size());
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

    // Register input device with LVGL.
    auto indev = lv_indev_create();
    lv_indev_set_user_data(indev, this);
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, &cdfw::hal::Touchscreen::ReadCallbackRouter);
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

  // Returns true if the touchscreen is currently being touched.
  bool Touched() { return driver_.getTouch().zRaw != 0; }

  // Returns the current touch point.
  hal::Point GetPoint() {
    return Rotate(XPT2046PointAdaptor(driver_.getTouch()));
  }
};
} // namespace
} // namespace cyd

std::unique_ptr<hal::Touchscreen> Touchscreen::Create() {
  auto ts = std::make_unique<cyd::Touchscreen>();
  ts->Init();
  return ts;
}
} // namespace hal
} // namespace cdfw

#endif // CDFW_CYD