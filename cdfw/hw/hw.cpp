// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/hw/hw.h"
#include "cdfw/hw/cyd/touchscreen.h"

namespace cdfw {
namespace hw {
namespace touchscreen {
hal::Touchscreen *Create() { return cyd::Create(); }
} // namespace touchscreen
} // namespace hw
} // namespace cdfw