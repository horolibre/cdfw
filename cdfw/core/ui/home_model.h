// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_HOME_MODEL_H
#define CDFW_CORE_UI_HOME_MODEL_H

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
class HomeModel {
public:
  // Factory method.
  static std::unique_ptr<HomeModel> Create();

  // Virtual d'tor.
  virtual ~HomeModel() = default;

  enum class WifiState { DISABLED, DISCONNECTED, CONNECTED };
  virtual WifiState GetWifiState() = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_HOME_MODEL_H
