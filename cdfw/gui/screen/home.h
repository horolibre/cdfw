// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_GUI_SCREEN_HOME_H
#define CDFW_GUI_SCREEN_HOME_H

// Local Headers
#include "cdfw/core/ui/home_model.h"

namespace cdfw {
namespace gui {
namespace screen {
class HomeView {
public:
  // Factory method.
  static std::unique_ptr<HomeView> Register();

  // Virtual d'tor.
  virtual ~HomeView() = default;

  virtual void DelayedShow() = 0;
  virtual void Show() = 0;
  virtual void SetWifiIcon(const char *icon) = 0;
};
} // namespace screen
} // namespace gui
} // namespace cdfw

#endif // CDFW_GUI_SCREEN_HOME_H
