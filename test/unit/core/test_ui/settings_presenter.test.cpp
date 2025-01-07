// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/settings_presenter.h"
#include "cdfw/core/arduino.h"
#include "cdfw/core/ui/settings_model.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace core {
namespace ui {
namespace {
String ssid = "ssid";
String password = "password";

class MockSettingsModel : public SettingsModel {
public:
  struct Data {
    bool set_wifi_credentials_called = false;
    WifiState wifi_state = WifiState::DISCONNECTED;
    WifiCredentials wifi_credentials = {ssid, password};
  };

  MockSettingsModel(Data &data) : data_(data) {}
  virtual ~MockSettingsModel() = default;

  virtual WifiState GetWifiState() override final { return data_.wifi_state; }
  virtual void SetWifiState(WifiState state) override final {
    data_.wifi_state = state;
  }
  virtual WifiCredentials GetWifiCredentials() override final {
    return data_.wifi_credentials;
  }
  virtual void
  SetWifiCredentials(const WifiCredentials &credentials) override final {
    data_.wifi_credentials = credentials;
  }

private:
  Data &data_;
};

class MockSettingsView : public SettingsPresenterView {
public:
  struct Data {
    bool init_called = false;
    bool show_called = false;
    bool set_wifi_enabled_called = false;
    bool set_wifi_credentials_called = false;
    bool set_wifi_status_called = false;
    bool wifi_enabled = false;
    WifiCredentials wifi_credentials;
    String wifi_status;
  };

  MockSettingsView(Data &data) : data_(data) {}
  virtual ~MockSettingsView() = default;

  virtual void Init() override final { data_.init_called = true; }

  virtual void Show() override final { data_.show_called = true; }

  virtual void SetWifiEnabled(bool enabled) override final {
    data_.set_wifi_enabled_called = true;
    data_.wifi_enabled = enabled;
  }

  virtual void
  SetWifiCredentials(const WifiCredentials &credentials) override final {
    data_.set_wifi_credentials_called = true;
    data_.wifi_credentials = credentials;
  }

  virtual void SetWifiStatus(const String &status) override final {
    data_.set_wifi_status_called = true;
    data_.wifi_status = status;
  }

private:
  Data &data_;
};

TEST(SettingsPresenterTests, InitNotCalled) {
  MockSettingsModel::Data model_data;
  MockSettingsView::Data view_data;
  auto presenter = SettingsPresenter::Create(
      std::make_unique<MockSettingsView>(view_data),
      std::make_unique<MockSettingsModel>(model_data));

  // Assertions for the view.
  EXPECT_FALSE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_FALSE(view_data.set_wifi_enabled_called);
  EXPECT_FALSE(view_data.set_wifi_credentials_called);
  EXPECT_FALSE(view_data.set_wifi_status_called);
  EXPECT_FALSE(view_data.wifi_enabled);
  EXPECT_TRUE(view_data.wifi_credentials.ssid.empty());
  EXPECT_TRUE(view_data.wifi_credentials.password.empty());
  EXPECT_TRUE(view_data.wifi_status.empty());

  // Assertions for the model.
  EXPECT_EQ(model_data.set_wifi_credentials_called, false);
  EXPECT_EQ(model_data.wifi_state, WifiState::DISCONNECTED);
  EXPECT_EQ(model_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(model_data.wifi_credentials.password, password);
}

TEST(SettingsPresenterTests, InitCalled_WifiDisabled) {
  MockSettingsModel::Data model_data;
  model_data.wifi_state = WifiState::DISABLED_;
  MockSettingsView::Data view_data;
  auto presenter = SettingsPresenter::Create(
      std::make_unique<MockSettingsView>(view_data),
      std::make_unique<MockSettingsModel>(model_data));
  presenter->Init();

  // Assertions for the view.
  EXPECT_TRUE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_TRUE(view_data.set_wifi_enabled_called);
  EXPECT_TRUE(view_data.set_wifi_credentials_called);
  EXPECT_TRUE(view_data.set_wifi_status_called);
  EXPECT_FALSE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(view_data.wifi_credentials.password, password);
  EXPECT_EQ(view_data.wifi_status, "Disabled");

  // Assertions for the model.
  EXPECT_EQ(model_data.set_wifi_credentials_called, false);
  EXPECT_EQ(model_data.wifi_state, WifiState::DISABLED_);
  EXPECT_EQ(model_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(model_data.wifi_credentials.password, password);
}

TEST(SettingsPresenterTests, InitCalled_WifiDisconnected) {
  MockSettingsModel::Data model_data;
  MockSettingsView::Data view_data;
  auto presenter = SettingsPresenter::Create(
      std::make_unique<MockSettingsView>(view_data),
      std::make_unique<MockSettingsModel>(model_data));
  presenter->Init();

  EXPECT_TRUE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_TRUE(view_data.set_wifi_enabled_called);
  EXPECT_TRUE(view_data.set_wifi_credentials_called);
  EXPECT_TRUE(view_data.set_wifi_status_called);
  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(view_data.wifi_credentials.password, password);
  EXPECT_EQ(view_data.wifi_status, "Disconnected");

  EXPECT_EQ(model_data.set_wifi_credentials_called, false);
  EXPECT_EQ(model_data.wifi_state, WifiState::DISCONNECTED);
  EXPECT_EQ(model_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(model_data.wifi_credentials.password, password);
}

TEST(SettingsPresenterTests, InitCalled_WifiConnected) {
  MockSettingsModel::Data model_data;
  model_data.wifi_state = WifiState::CONNECTED;
  MockSettingsView::Data view_data;
  auto presenter = SettingsPresenter::Create(
      std::make_unique<MockSettingsView>(view_data),
      std::make_unique<MockSettingsModel>(model_data));
  presenter->Init();

  EXPECT_TRUE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_TRUE(view_data.set_wifi_enabled_called);
  EXPECT_TRUE(view_data.set_wifi_credentials_called);
  EXPECT_TRUE(view_data.set_wifi_status_called);
  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(view_data.wifi_credentials.password, password);
  EXPECT_EQ(view_data.wifi_status, "Connected");

  EXPECT_EQ(model_data.set_wifi_credentials_called, false);
  EXPECT_EQ(model_data.wifi_state, WifiState::CONNECTED);
  EXPECT_EQ(model_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(model_data.wifi_credentials.password, password);
}

TEST(SettingsPresenterTests, InitCalled_WifiStateChange) {
  MockSettingsModel::Data model_data;
  MockSettingsView::Data view_data;
  auto presenter = SettingsPresenter::Create(
      std::make_unique<MockSettingsView>(view_data),
      std::make_unique<MockSettingsModel>(model_data));
  presenter->Init();

  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_status, "Disconnected");

  model_data.wifi_state = WifiState::DISABLED_;
  EXPECT_FALSE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_status, "Disabled");

  model_data.wifi_state = WifiState::DISCONNECTED;
  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_status, "Connected");
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw