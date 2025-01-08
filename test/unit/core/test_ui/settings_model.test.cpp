// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/settings_model.h"
#include "cdfw/core/arduino.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class MockSettingsModelSubscriber : public SettingsModelSubscriber {
public:
  bool wifi_state_changed_called = false;
  WifiState wifi_state = WifiState::DISCONNECTED;

  virtual void WifiStateChanged() override final {
    wifi_state_changed_called = true;
  }
};

class SettingsModelTests : public ::testing::Test {
protected:
  std::shared_ptr<SettingsModel> model = nullptr;
  std::unique_ptr<MockSettingsModelSubscriber> subscriber = nullptr;

  void SetUp() override final {
    model = SettingsModel::Create();
    subscriber = std::make_unique<MockSettingsModelSubscriber>();
    model->RegisterSubscriber(subscriber.get());
  }
};

TEST_F(SettingsModelTests, DefaultState) {
  EXPECT_EQ(model->GetWifiState(), WifiState::DISCONNECTED);
  EXPECT_TRUE(model->GetWifiCredentials().ssid.empty());
  EXPECT_TRUE(model->GetWifiCredentials().password.empty());
  EXPECT_FALSE(subscriber->wifi_state_changed_called);
}

TEST_F(SettingsModelTests, SetWifiState_NotifiesSubscribers) {
  auto wifi_state = WifiState::CONNECTED;
  model->SetWifiState(wifi_state);

  EXPECT_EQ(model->GetWifiState(), wifi_state);
  EXPECT_TRUE(subscriber->wifi_state_changed_called);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw