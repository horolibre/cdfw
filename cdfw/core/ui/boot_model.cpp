// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/boot_model.h"
#include "cdfw/core/version.h"

// C++ Standard Library Headers
#include <memory>
#include <string>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class BootModelImpl : public BootModel {
public:
  BootModelImpl() = default;
  virtual ~BootModelImpl() = default;

  virtual std::string GetDescription() { return "HOROLIBRE Cleaner"; }

  virtual std::string GetVersion() { return CDFW_VERSION; }
};
} // namespace

std::unique_ptr<BootModel> BootModel::Create() {
  return std::make_unique<BootModelImpl>();
}
} // namespace ui
} // namespace core
} // namespace cdfw