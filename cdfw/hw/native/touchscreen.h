// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HW_NATIVE_TOUCHSCREEN_H
#define CDFW_HW_NATIVE_TOUCHSCREEN_H

#ifdef CDFW_NATIVE

// Local Headers
#include "cdfw/hal/touchscreen.h"

namespace cdfw {
namespace hw {
namespace touchscreen {
namespace native {
hal::Touchscreen *Create();
} // namespace native
} // namespace touchscreen
} // namespace hw
} // namespace cdfw

#endif // CDFW_NATIVE

#endif // CDFW_HW_NATIVE_TOUCHSCREEN_H
