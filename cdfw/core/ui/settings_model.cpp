// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/settings_model.h"

// C++ Standard Library Headers
#include <list>
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class SettingsModelImpl : public SettingsModel {
public:
  SettingsModelImpl() : state_(WifiState::DISCONNECTED), credentials_() {}
  virtual ~SettingsModelImpl() = default;

  virtual void
  RegisterSubscriber(SettingsModelSubscriber *subscriber) override final {
    subscribers_.push_back(subscriber);
  }

  virtual WifiState GetWifiState() override final { return state_; }

  virtual void SetWifiState(WifiState state) override final {
    state_ = state;
    for (auto subscriber : subscribers_) {
      subscriber->WifiStateChanged();
    }
  };

  virtual WifiCredentials GetWifiCredentials() override final {
    return credentials_;
  }

  virtual void
  SetWifiCredentials(const WifiCredentials &credentials) override final {
    credentials_ = credentials;
  }

private:
  WifiState state_;
  WifiCredentials credentials_;
  std::list<SettingsModelSubscriber *> subscribers_;
};
} // namespace

std::shared_ptr<SettingsModel> SettingsModel::Create() {
  return std::make_shared<SettingsModelImpl>();
}
} // namespace ui
} // namespace core
} // namespace cdfw