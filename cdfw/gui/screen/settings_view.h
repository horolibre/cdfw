// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_GUI_SCREEN_SETTINGS_VIEW_H
#define CDFW_GUI_SCREEN_SETTINGS_VIEW_H

// Local Headers
#include "cdfw/core/ui/settings_presenter.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace gui {
namespace screen {
class SettingsView : public core::ui::SettingsPresenterView {
public:
  // Factory method.
  static std::unique_ptr<SettingsPresenterView> Create();

  // Virtual d'tor.
  virtual ~SettingsView() = default;
};
} // namespace screen
} // namespace gui
} // namespace cdfw

#endif // CDFW_GUI_SCREEN_SETTINGS_VIEW_H
