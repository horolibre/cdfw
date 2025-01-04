// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_GUI_SCREEN_BOOT_VIEW_H
#define CDFW_GUI_SCREEN_BOOT_VIEW_H

// Local Headers
#include "cdfw/core/ui/boot_presenter.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace gui {
namespace screen {
class BootView : public core::ui::BootPresenterView {
public:
  // Factory method.
  static std::unique_ptr<BootPresenterView> Create();

  // Pure virtual d'tor to prevent instantiation.
  virtual ~BootView() = 0;
};
} // namespace screen
} // namespace gui
} // namespace cdfw

#endif // CDFW_GUI_SCREEN_BOOT_VIEW_H
