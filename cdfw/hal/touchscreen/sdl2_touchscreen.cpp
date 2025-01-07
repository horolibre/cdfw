// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_NATIVE

// Local Headers
#include "cdfw/hal/point.h"
#include "cdfw/hal/touchscreen.h"

// Third Party Headers
#include <SDL2/SDL.h>
#include <drivers/sdl/lv_sdl_mouse.h> // From LVGL. TODO: Turn off LVGL simple include.
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdint>
#include <memory>

namespace cdfw {
namespace hal {
namespace sdl2 {
namespace {
lv_display_t *display;
lv_indev_t *mouse;

class Touchscreen : public hal::Touchscreen {
public:
  Touchscreen() = default;
  virtual ~Touchscreen() = default;

  virtual void Init() override final {
    // Create SDL display and mouse using LVGL functions; registration of the
    // display and input device are handled by LVGL automatically.
    display = lv_sdl_window_create(SDL_HOR_RES, SDL_VER_RES);
    mouse = lv_sdl_mouse_create();
  }

  virtual void ReadCallback(lv_indev_t *indev,
                            lv_indev_data_t *data) override final {
    // No nothing. The LVGL implementation of the SDL mouse driver handles this
    // automatically.
  }
};
} // namespace
} // namespace sdl2

std::unique_ptr<hal::Touchscreen> Touchscreen::Create() {
  auto ts = std::make_unique<sdl2::Touchscreen>();
  ts->Init();
  return ts;
}
} // namespace hal
} // namespace cdfw

#endif // CDFW_NATIVE