// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_HOME_MODEL_H
#define CDFW_CORE_UI_HOME_MODEL_H

// Local Headers
#include "cdfw/core/ui/settings_model.h"
#include "cdfw/core/wifi.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
class HomeModel {
public:
  // Factory method.
  static std::unique_ptr<HomeModel>
  Create(std::shared_ptr<SettingsModel> settings);

  // Virtual d'tor.
  virtual ~HomeModel() = default;

  virtual WifiState GetWifiState() = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_HOME_MODEL_H
