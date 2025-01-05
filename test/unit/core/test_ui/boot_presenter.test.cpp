// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/boot_model.h"
#include "cdfw/core/ui/boot_presenter.h"
#include "cdfw/core/version.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace core{
namespace ui {
namespace {
class MockBootModel : public BootModel {
public:
  MockBootModel() = default;
  virtual ~MockBootModel() = default;

  virtual String GetDescription() { return "sw_desc"; }

  virtual String GetVersion() { return "sw_version"; }
};

class MockBootView : public BootPresenterView {
public:
  struct Data {
    String desc;
    String version;
    bool init_called = false;
    bool show_called = false;
  };

  MockBootView(Data &data) : data_(data) {}
  virtual ~MockBootView() = default;

  virtual void Init(const String &desc, const String &version) override final {
    data_.init_called = true;
    data_.desc = desc;
    data_.version = version;
  }

  virtual void Show() override final {
    data_.show_called = true;
  }

private:
  Data &data_;
};

TEST(BootPresenterTests, InitNotCalled) {
  MockBootView::Data view_data;
  auto presenter = BootPresenter::Create(
    std::make_unique<MockBootView>(view_data),
    std::make_unique<MockBootModel>());

  ASSERT_EQ(view_data.desc, String());
  ASSERT_EQ(view_data.version, String());
  ASSERT_FALSE(view_data.init_called);
  ASSERT_FALSE(view_data.show_called);
}

TEST(BootPresenterTests, InitCalled) {
  MockBootView::Data view_data;
  auto presenter = BootPresenter::Create(
    std::make_unique<MockBootView>(view_data),
    std::make_unique<MockBootModel>());
  presenter->Init();

  ASSERT_EQ(view_data.desc, "sw_desc");
  ASSERT_EQ(view_data.version, "sw_version");
  ASSERT_TRUE(view_data.init_called);
  // The boot presenter shows the view as soon as it is initialized.
  ASSERT_TRUE(view_data.show_called);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw