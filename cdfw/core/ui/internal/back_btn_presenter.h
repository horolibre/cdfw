// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_INTERNAL_BACK_BTN_PRESENTER_H
#define CDFW_CORE_UI_INTERNAL_BACK_BTN_PRESENTER_H

// Local Headers
#include "cdfw/core/ui/home_presenter.h"
#include "cdfw/core/ui/settings_presenter.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
// Interface for presenters with a back button.
class BackBtnPresenter {
public:
  // Virtual d'tor.
  virtual ~BackBtnPresenter() = default;

  // Handle back button clicked.
  virtual void OnBackClicked() = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_INTERNAL_BACK_BTN_PRESENTER_H
