// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/routines_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
class RoutinesModelImpl : public RoutinesModel {
public:
  RoutinesModelImpl() = default;
  virtual ~RoutinesModelImpl() = default;
};

std::unique_ptr<RoutinesModel> RoutinesModel::Create() {
  return std::make_unique<RoutinesModelImpl>();
}
} // namespace ui
} // namespace core
} // namespace cdfw
