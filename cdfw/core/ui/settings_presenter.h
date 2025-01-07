// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_SETTINGS_PRESENTER_H
#define CDFW_CORE_UI_SETTINGS_PRESENTER_H

// Local Headers
#include "cdfw/core/ui/internal/back_btn_presenter.h"
#include "cdfw/core/ui/settings_model.h"
#include "cdfw/core/wifi.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
// Forward declarations.
class AppPresenter;
class SettingsPresenter;

// Presenter defines a minimum interface for the view.
class SettingsPresenterView {
public:
  // Virtual d'tor.
  virtual ~SettingsPresenterView() = default;

  // Initializes the view.
  virtual void Init(SettingsPresenter *presenter) = 0;

  // Shows the view.
  virtual void Show() = 0;

  // ---------------------------------------------------------------------------
  // Presenter -> View Interface
  // ---------------------------------------------------------------------------

  virtual void SetWifiEnabled(bool enabled) = 0;
  virtual void SetWifiCredentials(const WifiCredentials &credentials) = 0;
  virtual void SetWifiStatus(const String &status) = 0;
};

class SettingsPresenter : public SettingsModelSubscriber,
                          public BackBtnPresenter {
public:
  // Factory method.
  static std::shared_ptr<SettingsPresenter>
  Create(std::unique_ptr<SettingsPresenterView> view,
         std::shared_ptr<SettingsModel> model);

  // Virtual d'tor.
  virtual ~SettingsPresenter() = default;

  // Initializes the presenter and its dependencies.
  virtual void Init(AppPresenter *app_presenter) = 0;

  // Show the view.
  virtual void Show() = 0;

  // ---------------------------------------------------------------------------
  // View -> Presenter Interface
  // ---------------------------------------------------------------------------

  // Inform the presenter of a change in the wifi credentials.
  virtual void OnWifiCredentialsChange(const WifiCredentials &credentials) = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_SETTINGS_PRESENTER_H
