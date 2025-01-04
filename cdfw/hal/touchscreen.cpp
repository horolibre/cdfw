// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/hal/touchscreen.h"

namespace cdfw {
namespace hal {
void Touchscreen::ReadCallbackRouter(lv_indev_t *indev, lv_indev_data_t *data) {
  auto ts = static_cast<Touchscreen *>(lv_indev_get_user_data(indev));
  ts->ReadCallback(indev, data);
}
} // namespace hal
} // namespace cdfw