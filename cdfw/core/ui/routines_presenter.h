// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_ROUTINES_PRESENTER_H
#define CDFW_CORE_UI_ROUTINES_PRESENTER_H

// Local Headers
#include "cdfw/core/ui/internal/back_btn_presenter.h"
#include "cdfw/core/ui/routines_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
// Forward declaration of the presenter.
class AppPresenter;
class RoutinesPresenter;

// Presenter defines a minimum interface for the view.
class RoutinesPresenterView {
public:
  // Virtual d'tor.
  virtual ~RoutinesPresenterView() = default;

  // ---------------------------------------------------------------------------
  // Presenter -> View Interface
  // ---------------------------------------------------------------------------

  virtual void Init(RoutinesPresenter *presenter) = 0;
  virtual void Show() = 0;
};

class RoutinesPresenter : public BackBtnPresenter {
public:
  // Factory method.
  static std::unique_ptr<RoutinesPresenter>
  Create(std::unique_ptr<RoutinesPresenterView> view,
         std::unique_ptr<RoutinesModel> model);

  // Virtual d'tor.
  virtual ~RoutinesPresenter() = default;

  // ---------------------------------------------------------------------------
  // AppPresenter -> Presenter Interface
  // ---------------------------------------------------------------------------

  virtual void Init(AppPresenter *app_presenter) = 0;
  virtual void Show() = 0;

  // ---------------------------------------------------------------------------
  // View -> Presenter Interface
  // ---------------------------------------------------------------------------

  // TODO
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_ROUTINES_PRESENTER_H
