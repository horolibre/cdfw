// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_NATIVE

// Local Headers
#include "cdfw/hw/native/lvgl.h"
#include "cdfw/hal/lvgl.h"
#include "cdfw/hal/touchscreen.h"

// Third Party Headers
#include "drivers/sdl/lv_sdl_mouse.h"
#include <SDL2/SDL.h>
#include <lvgl.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace hw {
namespace native {
namespace {
// SDL display and mouse.
lv_display_t *lvDisplay;
lv_indev_t *lvMouse;

class LVGLInitializer : public hal::LVGLInitializer {
public:
  LVGLInitializer() = default;
  virtual ~LVGLInitializer() = default;

  virtual void Init() override final {
    lv_init();

    lvDisplay = lv_sdl_window_create(SDL_HOR_RES, SDL_VER_RES);
    lvMouse = lv_sdl_mouse_create();
  }
};
} // namespace

std::unique_ptr<hal::LVGLInitializer> Create() {
  return std::make_unique<native::LVGLInitializer>();
}
} // namespace native
} // namespace hw
} // namespace cdfw

#endif // CDFW_NATIVE