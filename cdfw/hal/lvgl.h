// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HAL_LVGL_H
#define CDFW_HAL_LVGL_H

namespace cdfw {
namespace hal {
class LVGLInitializer {
public:
  virtual ~LVGLInitializer() = default;
  virtual void Init() = 0;
};
} // namespace hal
} // namespace cdfw

#endif // CDFW_HAL_LVGL_H
