// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/home_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class HomeModelImpl : public HomeModel {
public:
  HomeModelImpl() = default;
  virtual ~HomeModelImpl() = default;

  virtual WifiState GetWifiState() override final {
    return WifiState::DISCONNECTED;
  }
};
} // namespace

std::unique_ptr<HomeModel> HomeModel::Create() {
  return std::make_unique<HomeModelImpl>();
}
} // namespace ui
} // namespace core
} // namespace cdfw