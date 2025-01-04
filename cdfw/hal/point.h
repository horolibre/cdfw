// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HAL_POINT_H
#define CDFW_HAL_POINT_H

// Representations for points in a coordinate system.

// C++ Standard Library Headers
#include <cstdint>

namespace cdfw {
namespace hal {
// Point in a 2D coordinate system (e.g., position on a screen).
struct Point {
  std::int16_t x, y;
  Point() : x(0), y(0) {}
  Point(std::int16_t x, std::int16_t y) : x(x), y(y) {}
  virtual ~Point() = default;
};
} // namespace hal
} // namespace cdfw

#endif // CDFW_HAL_POINT_H
