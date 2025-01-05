// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/home_presenter.h"
#include "cdfw/core/ui/home_model.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class MockHomeModel : public HomeModel {
public:
  WifiState wifi_state_;

  MockHomeModel() : wifi_state_(WifiState::DISCONNECTED) {}
  virtual ~MockHomeModel() = default;

  virtual WifiState GetWifiState() override final { return wifi_state_; }
};

class MockHomeView : public HomePresenterView {
public:
  struct Data {
    bool init_called = false;
    bool show_called = false;
    bool delayed_show_called = false;
    bool set_wifi_color_called = false;
    bool set_wifi_visible_called = false;
    bool wifi_visible = true;
    lv_color_t wifi_color = lv_palette_main(LV_PALETTE_RED);
  };

  MockHomeView(Data &data) : data_(data) {}
  virtual ~MockHomeView() = default;

  virtual void Init() override final { data_.init_called = true; }

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

TEST(HomePresenterTests, InitNotCalled) {
  MockHomeView::Data view_data;
  auto presenter =
      HomePresenter::Create(std::make_unique<MockHomeView>(view_data),
                            std::make_unique<MockHomeModel>());

  ASSERT_FALSE(view_data.init_called);
  ASSERT_FALSE(view_data.show_called);
  ASSERT_FALSE(view_data.delayed_show_called);
  ASSERT_FALSE(view_data.set_wifi_color_called);
  ASSERT_FALSE(view_data.set_wifi_visible_called);
  ASSERT_TRUE(view_data.wifi_visible);
  // ASSERT_EQ(view_data.wifi_color, lv_palette_main(LV_PALETTE_RED));
}

TEST(HomePresenterTests, InitCalled) {
  MockHomeView::Data view_data;
  auto presenter =
      HomePresenter::Create(std::make_unique<MockHomeView>(view_data),
                            std::make_unique<MockHomeModel>());
  presenter->Init();

  ASSERT_TRUE(view_data.init_called);
  ASSERT_FALSE(view_data.show_called);
  ASSERT_TRUE(view_data.delayed_show_called);
  ASSERT_TRUE(view_data.set_wifi_color_called);
  ASSERT_TRUE(view_data.set_wifi_visible_called);
  ASSERT_TRUE(view_data.wifi_visible);
  // ASSERT_EQ(view_data.wifi_color, lv_palette_main(LV_PALETTE_RED));
}

TEST(HomePresenterTests, UpdateWifiIcon_Connected) {
  MockHomeView::Data view_data;
  auto model = std::make_unique<MockHomeModel>();
  WifiState &wifi_state_ = model->wifi_state_;
  auto presenter = HomePresenter::Create(
      std::make_unique<MockHomeView>(view_data), std::move(model));
  presenter->Init();
  wifi_state_ = WifiState::CONNECTED;
  presenter->UpdateWifiIcon();

  ASSERT_TRUE(view_data.set_wifi_color_called);
  ASSERT_TRUE(view_data.set_wifi_visible_called);
  ASSERT_TRUE(view_data.wifi_visible);
  // ASSERT_EQ(view_data.wifi_color, lv_palette_main(LV_PALETTE_RED));
}

TEST(HomePresenterTests, UpdateWifiIcon_Disabled) {
  MockHomeView::Data view_data;
  auto model = std::make_unique<MockHomeModel>();
  WifiState &wifi_state_ = model->wifi_state_;
  auto presenter = HomePresenter::Create(
      std::make_unique<MockHomeView>(view_data), std::move(model));
  presenter->Init();

  wifi_state_ = WifiState::DISABLED_;
  presenter->UpdateWifiIcon();

  ASSERT_TRUE(view_data.set_wifi_color_called);
  ASSERT_TRUE(view_data.set_wifi_visible_called);
  ASSERT_FALSE(view_data.wifi_visible);
  // ASSERT_EQ(view_data.wifi_color, lv_palette_main(LV_PALETTE_RED));
}

} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw