// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/home_model.h"
#include "cdfw/core/ui/settings_model.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace core {
namespace ui {
namespace {
TEST(HomeModelTests, DefaultState) {
  auto settings_model = SettingsModel::Create();
  auto home_model = HomeModel::Create(settings_model);
  ASSERT_EQ(home_model->GetWifiState(), WifiState::DISCONNECTED);
}

TEST(HomeModelTests, ReflectsSettingsState) {
  auto settings_model = SettingsModel::Create();
  auto home_model = HomeModel::Create(settings_model);

  settings_model->SetWifiState(WifiState::CONNECTED);
  ASSERT_EQ(home_model->GetWifiState(), WifiState::CONNECTED);

  settings_model->SetWifiState(WifiState::DISCONNECTED);
  ASSERT_EQ(home_model->GetWifiState(), WifiState::DISCONNECTED);

  settings_model->SetWifiState(WifiState::DISABLED_);
  ASSERT_EQ(home_model->GetWifiState(), WifiState::DISABLED_);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw