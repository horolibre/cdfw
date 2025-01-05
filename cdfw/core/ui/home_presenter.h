// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_HOME_PRESENTER_H
#define CDFW_CORE_UI_HOME_PRESENTER_H

// Local Headers
#include "cdfw/core/ui/home_model.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
// Forward declaration of the presenter.
class HomePresenter;

// Presenter defines a minimum interface for the view.
class HomePresenterView {
public:
  // Virtual d'tor.
  virtual ~HomePresenterView() = default;

  // Initializes the view.
  virtual void Init() = 0;

  // Shows the view.
  virtual void Show() = 0;

  // Shows the view after a delay.
  virtual void DelayedShow() = 0;

  // Sets the color of the wifi icon.
  virtual void SetWifiColor(const lv_color_t &color) = 0;

  // Sets the visibility of the wifi icon.
  virtual void SetWifiVisible(bool visible) = 0;
};

class HomePresenter {
public:
  // Factory method.
  static std::unique_ptr<HomePresenter>
  Create(std::unique_ptr<HomePresenterView> view,
         std::unique_ptr<HomeModel> model);

  // Virtual d'tor.
  virtual ~HomePresenter() = default;

  // Initialize the presenter and its dependencies.
  virtual void Init() = 0;

  virtual void UpdateWifiIcon() = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_HOME_PRESENTER_H
