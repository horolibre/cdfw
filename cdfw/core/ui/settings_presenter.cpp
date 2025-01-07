// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/settings_presenter.h"
#include "cdfw/core/ui/settings_model.h"
#include "cdfw/core/wifi.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <map>
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class SettingsPresenterImpl : public SettingsPresenter {
public:
  SettingsPresenterImpl(std::unique_ptr<SettingsPresenterView> view,
                        std::unique_ptr<SettingsModel> model)
      : view_(std::move(view)), model_(std::move(model)) {}
  virtual ~SettingsPresenterImpl() = default;

  virtual void Init() override final {
    view_->Init();
    OnWifiStateChange(model_->GetWifiState());
    OnWifiCredentialsChange(model_->GetWifiCredentials());
  }

  virtual void OnWifiStateChange(WifiState state) override final {
    model_->SetWifiState(state);
    view_->SetWifiEnabled(state != WifiState::DISABLED_);
    std::map<WifiState, String> state_map = {
        {WifiState::DISABLED_, "Disabled"},
        {WifiState::DISCONNECTED, "Disconnected"},
        {WifiState::CONNECTED, "Connected"}};
    view_->SetWifiStatus(state_map[state]);
  }

  virtual void
  OnWifiCredentialsChange(const WifiCredentials &credentials) override final {
    model_->SetWifiCredentials(credentials);
    view_->SetWifiCredentials(credentials);
  }

private:
  std::unique_ptr<SettingsPresenterView> view_;
  std::unique_ptr<SettingsModel> model_;
};
} // namespace

std::shared_ptr<SettingsPresenter>
SettingsPresenter::Create(std::unique_ptr<SettingsPresenterView> view,
                          std::unique_ptr<SettingsModel> model) {
  return std::make_shared<SettingsPresenterImpl>(std::move(view),
                                                 std::move(model));
}
} // namespace ui
} // namespace core
} // namespace cdfw
