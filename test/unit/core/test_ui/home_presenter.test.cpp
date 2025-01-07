// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/home_presenter.h"
#include "cdfw/core/ui/app_presenter.h"
#include "cdfw/core/ui/home_model.h"

// Third Party Headers
#include <gtest/gtest.h>
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdint>
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class MockHomeModel : public HomeModel {
public:
  MockHomeModel(WifiState &wifi_state) : wifi_state_(wifi_state) {}
  virtual ~MockHomeModel() = default;
  virtual WifiState GetWifiState() override final { return wifi_state_; }

private:
  WifiState &wifi_state_;
};

class MockHomeView : public HomePresenterView {
public:
  struct Data {
    bool init_called;
    bool show_called;
    bool delayed_show_called;
    bool set_wifi_color_called;
    bool set_wifi_visible_called;
    bool wifi_visible;
    lv_color_t wifi_color;

    Data() { Reset(); }

    void Reset() {
      init_called = false;
      show_called = false;
      delayed_show_called = false;
      set_wifi_color_called = false;
      set_wifi_visible_called = false;
      wifi_visible = true;
      wifi_color = lv_palette_main(LV_PALETTE_RED);
    }
  };

  MockHomeView(Data &data) : data_(data) {}
  virtual ~MockHomeView() = default;

  virtual void Init(HomePresenter *presenter) override final {
    data_.init_called = true;
  }
  virtual void Show() override final { data_.show_called = true; }
  virtual void DelayedShow() override final {
    data_.delayed_show_called = true;
  }
  virtual void SetWifiColor(const lv_color_t &color) override final {
    data_.set_wifi_color_called = true;
    data_.wifi_color = color;
  }
  virtual void SetWifiVisible(bool visible) override final {
    data_.set_wifi_visible_called = true;
    data_.wifi_visible = visible;
  }

private:
  Data &data_;
};

class MockAppPresenter : public AppPresenter {
public:
  virtual ~MockAppPresenter() = default;

  virtual void Init() override final {}
  virtual void ShowHome() override final {}
  virtual void ShowHomeDelayed() override final {}
  virtual void ShowClean() override final {}
  virtual void ShowRoutines() override final {}
  virtual void ShowSettings() override final {}
};

struct WifiColors {
  std::uint16_t connected = lv_color_to_u16(lv_palette_main(LV_PALETTE_GREEN));
  std::uint16_t disconnected = lv_color_to_u16(lv_palette_main(LV_PALETTE_RED));
};

class HomePresenterTests : public ::testing::Test {
protected:
  std::unique_ptr<HomePresenter> presenter = nullptr;
  std::unique_ptr<MockAppPresenter> app_presenter = nullptr;
  MockHomeView::Data view_data;
  WifiState wifi_state = WifiState::DISCONNECTED;
  WifiColors wifi_colors;

  void SetUp() override final {
    view_data = MockHomeView::Data();
    presenter =
        HomePresenter::Create(std::make_unique<MockHomeView>(view_data),
                              std::make_unique<MockHomeModel>(wifi_state));
    app_presenter = std::make_unique<MockAppPresenter>();
  }
};

TEST_F(HomePresenterTests, InitNotCalled) {
  // Assertions for the view.
  EXPECT_FALSE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_FALSE(view_data.delayed_show_called);
  EXPECT_FALSE(view_data.set_wifi_color_called);
  EXPECT_FALSE(view_data.set_wifi_visible_called);
  EXPECT_TRUE(view_data.wifi_visible);
  EXPECT_EQ(lv_color_to_u16(view_data.wifi_color), wifi_colors.disconnected);
}

TEST_F(HomePresenterTests, InitCalled) {
  presenter->Init(app_presenter.get());

  EXPECT_TRUE(view_data.init_called);
  EXPECT_FALSE(view_data.show_called);
  EXPECT_FALSE(view_data.delayed_show_called);
  EXPECT_TRUE(view_data.set_wifi_color_called);
  EXPECT_TRUE(view_data.set_wifi_visible_called);
  EXPECT_TRUE(view_data.wifi_visible);
  EXPECT_EQ(lv_color_to_u16(view_data.wifi_color), wifi_colors.disconnected);
}

TEST_F(HomePresenterTests, UpdateWifiIcon) {
  presenter->Init(app_presenter.get());

  // DISCONNECTED -> CONNECTED
  // Note: Disconnect is the default state.
  wifi_state = WifiState::CONNECTED;
  presenter->UpdateWifiIcon();
  EXPECT_TRUE(view_data.set_wifi_color_called);
  EXPECT_TRUE(view_data.set_wifi_visible_called);
  EXPECT_TRUE(view_data.wifi_visible);
  EXPECT_EQ(lv_color_to_u16(view_data.wifi_color), wifi_colors.connected);

  // CONNECTED -> DISCONNECTED
  wifi_state = WifiState::DISCONNECTED;
  view_data.Reset();
  presenter->UpdateWifiIcon();
  EXPECT_TRUE(view_data.set_wifi_color_called);
  EXPECT_TRUE(view_data.set_wifi_visible_called);
  EXPECT_TRUE(view_data.wifi_visible);
  EXPECT_EQ(lv_color_to_u16(view_data.wifi_color), wifi_colors.disconnected);

  // DISCONNECTED -> DISABLED
  wifi_state = WifiState::DISABLED_;
  view_data.Reset();
  presenter->UpdateWifiIcon();
  EXPECT_TRUE(view_data.set_wifi_visible_called);
  EXPECT_FALSE(view_data.wifi_visible);

  // DISABLED -> CONNECTED
  wifi_state = WifiState::CONNECTED;
  view_data.Reset();
  presenter->UpdateWifiIcon();
  EXPECT_TRUE(view_data.set_wifi_color_called);
  EXPECT_TRUE(view_data.set_wifi_visible_called);
  EXPECT_TRUE(view_data.wifi_visible);
  EXPECT_EQ(lv_color_to_u16(view_data.wifi_color), wifi_colors.connected);

  // CONNECTED -> DISABLED
  wifi_state = WifiState::DISABLED_;
  view_data.Reset();
  presenter->UpdateWifiIcon();
  EXPECT_TRUE(view_data.set_wifi_visible_called);
  EXPECT_FALSE(view_data.wifi_visible);

  // DISABLED -> DISCONNECTED
  wifi_state = WifiState::DISCONNECTED;
  view_data.Reset();
  presenter->UpdateWifiIcon();
  EXPECT_TRUE(view_data.set_wifi_color_called);
  EXPECT_TRUE(view_data.set_wifi_visible_called);
  EXPECT_TRUE(view_data.wifi_visible);
  EXPECT_EQ(lv_color_to_u16(view_data.wifi_color), wifi_colors.disconnected);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw