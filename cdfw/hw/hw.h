// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HW_HW_H
#define CDFW_HW_HW_H

// Local Headers
#include "cdfw/hal/touchscreen.h"

namespace cdfw {
namespace hw {
namespace touchscreen {
hal::Touchscreen *Create();
} // namespace touchscreen
} // namespace hw
} // namespace cdfw

#endif // CDFW_HW_HW_H
