// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_APP_PRESENTER_H
#define CDFW_CORE_UI_APP_PRESENTER_H

// Local Headers
#include "cdfw/core/ui/home_presenter.h"
#include "cdfw/core/ui/settings_presenter.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
// Top level presenter for the application. This presenter serves two purposes:
// (1) it handles initialization of all other presenters, and (2) it provides a
// a means for switching between presenters.
class AppPresenter {
public:
  // Factory method.
  static std::unique_ptr<AppPresenter>
  Create(std::unique_ptr<HomePresenter> home_presenter,
         std::shared_ptr<SettingsPresenter> settings_presenter);

  // Virtual d'tor.
  virtual ~AppPresenter() = default;

  // Initializes all presenters.
  virtual void Init() = 0;

  // Shows the home screen.
  virtual void ShowHome() = 0;
  virtual void ShowHomeDelayed() = 0;

  // Shows the settings screen.
  virtual void ShowSettings() = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_APP_PRESENTER_H
