// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HAL_SD_H
#define CDFW_HAL_SD_H

// Interface for SD access.

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace hal {
// Representation of the SD device.
class SD {
public:
  // Factory method.
  static std::unique_ptr<SD> Create();

  // Virtual d'tor.
  virtual ~SD() = default;

  virtual std::uint64_t GetCapacity() = 0;
  virtual std::uint64_t GetAvailable() = 0;
  virtual std::uint64_t GetUsed() = 0;
};
} // namespace hal
} // namespace cdfw

#endif // CDFW_HAL_FS_H
