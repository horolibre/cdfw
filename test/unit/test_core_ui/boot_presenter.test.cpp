// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/ui/boot_presenter.h"
#include "cdfw/core/ui/boot_model.h"
#include "cdfw/core/version.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <memory>
#include <string>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class MockBootModel : public BootModel {
public:
  struct Data {
    bool get_description_called = false;
    bool get_version_called = false;
  };
  MockBootModel(Data &data, std::string desc, std::string version)
      : data_(data), desc_(desc), version_(version) {}
  virtual ~MockBootModel() = default;
  virtual std::string GetDescription() override final {
    data_.get_description_called = true;
    return desc_;
  }
  virtual std::string GetVersion() override final {
    data_.get_version_called = true;
    return version_;
  }

private:
  Data &data_;
  std::string desc_;
  std::string version_;
};

class MockBootView : public BootPresenterView {
public:
  struct Data {
    std::string desc;
    std::string version;
    bool init_called = false;
    bool set_description_called = false;
    bool set_version_called = false;
  };

  MockBootView(Data &data) : data_(data) {}
  virtual ~MockBootView() = default;

  virtual void Init() override final { data_.init_called = true; }

  virtual void SetDescription(const std::string &desc) override final {
    data_.set_description_called = true;
    data_.desc = desc;
  }

  virtual void SetVersion(const std::string &version) override final {
    data_.set_version_called = true;
    data_.version = version;
  }

private:
  Data &data_;
};

class BootPresenterTests : public ::testing::Test {
protected:
  std::string desc = "sw_desc";
  std::string version = "sw_version";
  MockBootModel::Data model_data;
  MockBootView::Data view_data;
  std::shared_ptr<BootPresenter> presenter = nullptr;

  void SetUp() override final {
    model_data = MockBootModel::Data();
    view_data = MockBootView::Data();
    presenter = BootPresenter::Create(
        std::make_unique<MockBootView>(view_data),
        std::make_unique<MockBootModel>(model_data, desc, version));
  }
};

TEST_F(BootPresenterTests, InitNotCalled) {
  // Assertions for the view.
  EXPECT_FALSE(view_data.init_called);
  EXPECT_FALSE(view_data.set_description_called);
  EXPECT_FALSE(view_data.set_version_called);
  EXPECT_TRUE(view_data.desc.empty());
  EXPECT_TRUE(view_data.version.empty());

  // Assertions for the model.
  EXPECT_FALSE(model_data.get_description_called);
  EXPECT_FALSE(model_data.get_version_called);
}

TEST_F(BootPresenterTests, InitCalled) {
  presenter->Init();

  // Assertions for the view.
  EXPECT_TRUE(view_data.init_called);
  EXPECT_TRUE(view_data.set_description_called);
  EXPECT_TRUE(view_data.set_version_called);
  EXPECT_EQ(view_data.desc, desc);
  EXPECT_EQ(view_data.version, version);

  // Assertions for the model.
  EXPECT_TRUE(model_data.get_description_called);
  EXPECT_TRUE(model_data.get_version_called);
}
} // namespace
} // namespace ui
} // namespace core
} // namespace cdfw