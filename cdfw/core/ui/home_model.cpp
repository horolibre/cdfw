// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/home_model.h"
#include "cdfw/core/wifi.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class HomeModelImpl : public HomeModel {
public:
  HomeModelImpl(std::shared_ptr<SettingsModel> settings)
      : settings_(settings) {}
  virtual ~HomeModelImpl() = default;

  virtual WifiState GetWifiState() override final {
    return settings_->GetWifiState();
  }

private:
  std::shared_ptr<SettingsModel> settings_;
};
} // namespace

std::unique_ptr<HomeModel>
HomeModel::Create(std::shared_ptr<SettingsModel> settings) {
  return std::make_unique<HomeModelImpl>(settings);
}
} // namespace ui
} // namespace core
} // namespace cdfw