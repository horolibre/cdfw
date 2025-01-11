// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_HAL_SD_H
#define CDFW_HAL_SD_H

// Interface for SD access.

// Local Headers
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <memory>

#define CDFW_SD_VOLUME_NAME "sd"

namespace cdfw {
namespace hal {
// Representation of the SD device.
class SD : public vfs::Volume {
public:
  // Factory method.
  static std::unique_ptr<SD> Create();

  // Virtual d'tor.
  virtual ~SD() = default;

  virtual bool IsSD() override final { return true; }
};
} // namespace hal
} // namespace cdfw

#endif // CDFW_HAL_FS_H
