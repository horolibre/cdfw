// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/hw/hw.h"
#ifdef CDFW_CYD
#include "cdfw/hw/cyd/lvgl.h"
#include "cdfw/hw/cyd/touchscreen.h"
#elif defined(CDFW_NATIVE)
#include "cdfw/hw/native/lvgl.h"
#include "cdfw/hw/native/touchscreen.h"
#endif // CDFW_CYD

namespace cdfw {
namespace hw {
namespace lvgl {
namespace {
std::unique_ptr<hal::LVGLInitializer> lvgl_initializer = nullptr;
}
void Init() {
  lvgl_initializer =
#ifdef CDFW_CYD
      cyd::Create();
#elif defined(CDFW_NATIVE)
      native::Create();
#endif // CDFW_CYD
  lvgl_initializer->Init();
}
} // namespace lvgl

namespace touchscreen {
hal::Touchscreen *Create() {
#ifdef CDFW_CYD
  return cyd::Create();
#elif defined(CDFW_NATIVE)
  return native::Create();
#endif // CDFW_CYD
}
} // namespace touchscreen
} // namespace hw
} // namespace cdfw