// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/home_model.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace core{
namespace ui {
namespace {
TEST(HomeModelTests, DefaultState) {
  auto model = HomeModel::Create();
  ASSERT_EQ(model->GetWifiState(), HomeModel::WifiState::DISCONNECTED);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw