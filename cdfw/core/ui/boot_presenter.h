// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_UI_BOOT_PRESENTER_H
#define CDFW_CORE_UI_BOOT_PRESENTER_H

// Local Headers
#include "cdfw/core/arduino.h"
#include "cdfw/core/ui/boot_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
// Forward declaration of the presenter.
class BootPresenter;

// Presenter defines a minimum interface for the view.
class BootPresenterView {
public:
  // Virtual d'tor.
  virtual ~BootPresenterView() = default;

  // ---------------------------------------------------------------------------
  // Presenter -> View Interface
  // ---------------------------------------------------------------------------

  virtual void Init() = 0;
  virtual void SetDescription(const String &desc) = 0;
  virtual void SetVersion(const String &version) = 0;
};

class BootPresenter {
public:
  // Factory method.
  static std::unique_ptr<BootPresenter>
  Create(std::unique_ptr<BootPresenterView> view,
         std::unique_ptr<BootModel> model);

  // Virtual d'tor.
  virtual ~BootPresenter() = default;

  // Initialize the presenter and its dependencies.
  // Note: For the boot presenter, the view is shown as soon as it is
  // initialized.
  virtual void Init() = 0;
};
} // namespace ui
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_UI_BOOT_PRESENTER_H
