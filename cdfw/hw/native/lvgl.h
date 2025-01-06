// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HW_NATIVE_LVGL_H
#define CDFW_HW_NATIVE_LVGL_H

#ifdef CDFW_NATIVE

// Local Headers
#include "cdfw/hal/lvgl.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace hw {
namespace native {
std::unique_ptr<hal::LVGLInitializer> Create();
} // namespace native
} // namespace hw
} // namespace cdfw

#endif // CDFW_NATIVE

#endif // CDFW_HW_NATIVE_LVGL_H