// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HW_CYD_LVGL_H
#define CDFW_HW_CYD_LVGL_H

#ifdef CDFW_CYD

// Local Headers
#include "cdfw/hal/lvgl.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace hw {
namespace cyd {
std::unique_ptr<hal::LVGLInitializer> Create();
} // namespace cyd
} // namespace hw
} // namespace cdfw

#endif // CDFW_CYD

#endif // CDFW_HW_CYD_LVGL_H
