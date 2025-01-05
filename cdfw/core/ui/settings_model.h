// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_SETTINGS_MODEL_H
#define CDFW_CORE_UI_SETTINGS_MODEL_H

// Local Headers
#include "cdfw/core/wifi.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
class SettingsModel {
public:
  // Factory method.
  static std::shared_ptr<SettingsModel> Create();

  // Virtual d'tor.
  virtual ~SettingsModel() = default;

  virtual WifiState GetWifiState() = 0;
  virtual void SetWifiState(WifiState state) = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_SETTINGS_MODEL_H
