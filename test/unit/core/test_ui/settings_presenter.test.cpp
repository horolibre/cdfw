// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/settings_presenter.h"
#include "cdfw/core/arduino.h"
#include "cdfw/core/ui/settings_model.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <memory>
#include <vector>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class MockSettingsModel : public SettingsModel {
public:
  bool set_wifi_credentials_called = false;
  bool register_subscriber_called = false;
  std::vector<SettingsModelSubscriber *> subscribers;
  WifiState wifi_state;
  WifiCredentials wifi_credentials;

  MockSettingsModel(WifiState state, WifiCredentials credentials)
      : wifi_state(state), wifi_credentials(credentials),
        model_(SettingsModel::Create()) {
    model_->SetWifiState(wifi_state);
    model_->SetWifiCredentials(wifi_credentials);
  }
  virtual ~MockSettingsModel() = default;

  virtual void
  RegisterSubscriber(SettingsModelSubscriber *subscriber) override final {
    register_subscriber_called = true;
    subscribers.push_back(subscriber);
    model_->RegisterSubscriber(subscriber);
  }

  virtual WifiState GetWifiState() override final { return wifi_state; }
  virtual void SetWifiState(WifiState state) override final {
    wifi_state = state;
    model_->SetWifiState(state);
  }
  virtual WifiCredentials GetWifiCredentials() override final {
    return wifi_credentials;
  }
  virtual void
  SetWifiCredentials(const WifiCredentials &credentials) override final {
    wifi_credentials = credentials;
    model_->SetWifiCredentials(credentials);
  }

private:
  // Use a real model object for the subscriber propogation.
  std::shared_ptr<SettingsModel> model_;
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

class SettingsPresenterTests : public ::testing::Test {
protected:
  String ssid = "ssid";
  String password = "password";
  std::shared_ptr<MockSettingsModel> model;
  std::shared_ptr<SettingsPresenter> presenter;
  MockSettingsView::Data view_data;

  void SetUp() override final {
    model = std::make_shared<MockSettingsModel>(
        WifiState::DISCONNECTED, WifiCredentials{ssid, password});
    presenter = SettingsPresenter::Create(
        std::make_unique<MockSettingsView>(view_data), model);
  }
};

TEST_F(SettingsPresenterTests, InitNotCalled) {
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
  EXPECT_FALSE(model->set_wifi_credentials_called);
  EXPECT_FALSE(model->register_subscriber_called);
  EXPECT_TRUE(model->subscribers.empty());
  EXPECT_EQ(model->wifi_state, WifiState::DISCONNECTED);
  EXPECT_EQ(model->wifi_credentials.ssid, ssid);
  EXPECT_EQ(model->wifi_credentials.password, password);
}

TEST_F(SettingsPresenterTests, InitCalled_WifiDisabled) {
  model->SetWifiState(WifiState::DISABLED_);
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
  EXPECT_FALSE(model->set_wifi_credentials_called);
  EXPECT_TRUE(model->register_subscriber_called);
  EXPECT_EQ(model->subscribers.size(), 1);
  EXPECT_EQ(model->wifi_state, WifiState::DISABLED_);
  EXPECT_EQ(model->wifi_credentials.ssid, ssid);
  EXPECT_EQ(model->wifi_credentials.password, password);
}

TEST_F(SettingsPresenterTests, InitCalled_WifiDisconnected) {
  model->SetWifiState(WifiState::DISCONNECTED);
  presenter->Init();

  // Assertions for the view.
  EXPECT_TRUE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_TRUE(view_data.set_wifi_enabled_called);
  EXPECT_TRUE(view_data.set_wifi_credentials_called);
  EXPECT_TRUE(view_data.set_wifi_status_called);
  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(view_data.wifi_credentials.password, password);
  EXPECT_EQ(view_data.wifi_status, "Disconnected");

  // Assertions for the model.
  EXPECT_FALSE(model->set_wifi_credentials_called);
  EXPECT_TRUE(model->register_subscriber_called);
  EXPECT_EQ(model->subscribers.size(), 1);
  EXPECT_EQ(model->wifi_state, WifiState::DISCONNECTED);
  EXPECT_EQ(model->wifi_credentials.ssid, ssid);
  EXPECT_EQ(model->wifi_credentials.password, password);
}

TEST_F(SettingsPresenterTests, InitCalled_WifiConnected) {
  model->SetWifiState(WifiState::CONNECTED);
  presenter->Init();

  // Assertions for the view.
  EXPECT_TRUE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_TRUE(view_data.set_wifi_enabled_called);
  EXPECT_TRUE(view_data.set_wifi_credentials_called);
  EXPECT_TRUE(view_data.set_wifi_status_called);
  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_credentials.ssid, ssid);
  EXPECT_EQ(view_data.wifi_credentials.password, password);
  EXPECT_EQ(view_data.wifi_status, "Connected");

  // Assertions for the model.
  EXPECT_FALSE(model->set_wifi_credentials_called);
  EXPECT_TRUE(model->register_subscriber_called);
  EXPECT_EQ(model->subscribers.size(), 1);
  EXPECT_EQ(model->wifi_state, WifiState::CONNECTED);
  EXPECT_EQ(model->wifi_credentials.ssid, ssid);
  EXPECT_EQ(model->wifi_credentials.password, password);
}

TEST_F(SettingsPresenterTests, WifiStateChange) {
  presenter->Init();

  model->SetWifiState(WifiState::DISCONNECTED);
  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_status, "Disconnected");

  model->SetWifiState(WifiState::DISABLED_);
  EXPECT_FALSE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_status, "Disabled");

  model->SetWifiState(WifiState::CONNECTED);
  EXPECT_TRUE(view_data.wifi_enabled);
  EXPECT_EQ(view_data.wifi_status, "Connected");
}

TEST_F(SettingsPresenterTests, ShowCalled) {
  presenter->Init();
  presenter->Show();

  EXPECT_TRUE(view_data.show_called);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw