// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/settings_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class SettingsModelImpl : public SettingsModel {
public:
  SettingsModelImpl() : state_(WifiState::DISCONNECTED) {}
  virtual ~SettingsModelImpl() = default;

  virtual WifiState GetWifiState() override final { return state_; }

  virtual void SetWifiState(WifiState state) override final { state_ = state; };

private:
  WifiState state_;
};
} // namespace

std::shared_ptr<SettingsModel> SettingsModel::Create() {
  return std::make_shared<SettingsModelImpl>();
}
} // namespace ui
} // namespace core
} // namespace cdfw