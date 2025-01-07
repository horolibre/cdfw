// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/clean_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
class CleanModelImpl : public CleanModel {
public:
  CleanModelImpl() = default;
  virtual ~CleanModelImpl() = default;
};

std::unique_ptr<CleanModel> CleanModel::Create() {
  return std::make_unique<CleanModelImpl>();
}
} // namespace ui
} // namespace core
} // namespace cdfw
