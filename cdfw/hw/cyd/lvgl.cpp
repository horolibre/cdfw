// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_CYD

// Local Headers
#include "cdfw/hw/cyd/lvgl.h"
#include "cdfw/hal/lvgl.h"
#include "cdfw/hal/touchscreen.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <array>
#include <memory>

namespace cdfw {
namespace hw {
namespace cyd {
namespace {
// Using the LVGL suggest 1/10th screen size for the draw buffer.
std::array<std::uint8_t, CDFW_SCR_W * CDFW_SCR_H / 10> draw_buf = {0};

class LVGLInitializer : public hal::LVGLInitializer {
public:
  LVGLInitializer() = default;
  virtual ~LVGLInitializer() = default;

  virtual void Init() override final {

    // Initialise display driver.
    lv_display_t *disp =
        lv_tft_espi_create(CDFW_SCR_W, CDFW_SCR_H, &draw_buf, draw_buf.size());
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
  }
};
} // namespace

std::unique_ptr<hal::LVGLInitializer> Create() {
  return std::make_unique<cyd::LVGLInitializer>();
}
} // namespace cyd
} // namespace hw
} // namespace cdfw

#endif // CDFW_CYD
