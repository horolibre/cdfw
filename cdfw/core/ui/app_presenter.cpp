// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/app_presenter.h"
#include "cdfw/core/ui/home_presenter.h"
#include "cdfw/core/ui/settings_presenter.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class AppPresenterImpl : public AppPresenter {
public:
  AppPresenterImpl(std::unique_ptr<HomePresenter> home_presenter,
                   std::shared_ptr<SettingsPresenter> settings_presenter)
      : home_presenter_(std::move(home_presenter)),
        settings_presenter_(settings_presenter) {}
  ~AppPresenterImpl() = default;

  virtual void Init() override final {
    home_presenter_->Init();
    settings_presenter_->Init(this);
  }

  virtual void ShowHome() override final { home_presenter_->Show(); }
  virtual void ShowHomeDelayed() override final {
    // TODO
  }
  virtual void ShowSettings() override final { settings_presenter_->Show(); }

private:
  std::unique_ptr<HomePresenter> home_presenter_;
  std::shared_ptr<SettingsPresenter> settings_presenter_;
};
} // namespace

std::unique_ptr<AppPresenter>
AppPresenter::Create(std::unique_ptr<HomePresenter> home_presenter,
                     std::shared_ptr<SettingsPresenter> settings_presenter) {
  return std::make_unique<AppPresenterImpl>(std::move(home_presenter),
                                            settings_presenter);
}
} // namespace ui
} // namespace core
} // namespace cdfw
