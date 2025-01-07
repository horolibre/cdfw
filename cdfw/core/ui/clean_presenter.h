// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_CLEAN_PRESENTER_H
#define CDFW_CORE_UI_CLEAN_PRESENTER_H

// Local Headers
#include "cdfw/core/ui/clean_model.h"
#include "cdfw/core/ui/internal/back_btn_presenter.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
// Forward declaration of the presenter.
class AppPresenter;
class CleanPresenter;

// Presenter defines a minimum interface for the view.
class CleanPresenterView {
public:
  // Virtual d'tor.
  virtual ~CleanPresenterView() = default;

  // ---------------------------------------------------------------------------
  // Presenter -> View Interface
  // ---------------------------------------------------------------------------

  virtual void Init(CleanPresenter *presenter) = 0;
  virtual void Show() = 0;
};

class CleanPresenter : public BackBtnPresenter {
public:
  // Factory method.
  static std::unique_ptr<CleanPresenter>
  Create(std::unique_ptr<CleanPresenterView> view,
         std::unique_ptr<CleanModel> model);

  // Virtual d'tor.
  virtual ~CleanPresenter() = default;

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

#endif // CDFW_CORE_UI_CLEAN_PRESENTER_H
