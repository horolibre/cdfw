// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_BOOT_MODEL_H
#define CDFW_CORE_UI_BOOT_MODEL_H

// Local Headers
#include "cdfw/core/arduino.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
class BootModel {
public:
  // Factory method.
  static std::unique_ptr<BootModel> Create();

  // Virtual d'tor.
  virtual ~BootModel() = default;

  virtual String GetDescription() = 0;
  virtual String GetVersion() = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_BOOT_MODEL_H
