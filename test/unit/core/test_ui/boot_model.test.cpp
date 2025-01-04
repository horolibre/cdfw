// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/boot_model.h"
#include "cdfw/core/version.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace core{
namespace ui {
namespace {
TEST(BootModelTests, DefaultState) {
  auto model = BootModel::Create();
  ASSERT_EQ(model->GetDescription(), "HOROLIBRE Cleaner");
  ASSERT_EQ(model->GetVersion(), CDFW_VERSION);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw