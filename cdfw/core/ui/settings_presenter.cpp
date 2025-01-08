// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/settings_presenter.h"
#include "cdfw/core/ui/app_presenter.h"
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
                        std::shared_ptr<SettingsModel> model)
      : app_presenter_(nullptr), view_(std::move(view)), model_(model) {}
  virtual ~SettingsPresenterImpl() = default;

  virtual void Init(AppPresenter *app_presenter) override final {
    // Record the app presenter.
    app_presenter_ = app_presenter;

    // Setup the view.
    view_->Init(this);
    view_->SetWifiCredentials(model_->GetWifiCredentials());
    SetViewWifiState(model_->GetWifiState());

    // Register the presenter as a subscriber to the model.
    model_->RegisterSubscriber(this);
  }

  virtual void Show() override final { view_->Show(); }

  virtual void WifiStateChanged() override final {
    const WifiState &state = model_->GetWifiState();
    SetViewWifiState(state);
  }

  virtual void
  OnWifiCredentialsChange(const WifiCredentials &credentials) override final {
    model_->SetWifiCredentials(credentials);
  }

  virtual void OnBackClicked() override final { app_presenter_->ShowHome(); }

private:
  AppPresenter *app_presenter_;
  std::unique_ptr<SettingsPresenterView> view_;
  std::shared_ptr<SettingsModel> model_;

  void SetViewWifiState(const WifiState &state) {
    view_->SetWifiEnabled(state != WifiState::DISABLED_);
    std::map<WifiState, String> state_map = {
        {WifiState::DISABLED_, "Disabled"},
        {WifiState::DISCONNECTED, "Disconnected"},
        {WifiState::CONNECTED, "Connected"}};
    view_->SetWifiStatus(state_map[state]);
  }
};
} // namespace

std::shared_ptr<SettingsPresenter>
SettingsPresenter::Create(std::unique_ptr<SettingsPresenterView> view,
                          std::shared_ptr<SettingsModel> model) {
  return std::make_shared<SettingsPresenterImpl>(std::move(view), model);
}
} // namespace ui
} // namespace core
} // namespace cdfw
