// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_layout.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <filesystem>

namespace cdfw {
namespace {
namespace stdfs = std::filesystem;

class DirLayoutValidatorTests : public ::testing::Test {
protected:
  stdfs::path tmp_dir = stdfs::temp_directory_path() / "test";
  std::shared_ptr<DirLayoutValidator> validator = DirLayoutValidator::Create();
  DirLayout layout = DirLayout(tmp_dir);

  void SetUp() override {
    stdfs::create_directories(tmp_dir);
    EXPECT_TRUE(stdfs::exists(tmp_dir));

    stdfs::create_directories(layout.app_dir.native());
    stdfs::create_directories(layout.routines_dir.native());
    stdfs::create_directories(layout.data_dir.native());
  }
};

TEST(DirLayoutTests, Layout) {
  auto tmp_dir = stdfs::temp_directory_path() / "test";
  DirLayout layout(tmp_dir);

  EXPECT_EQ(layout.app_dir, tmp_dir / "horolibre");
  EXPECT_EQ(layout.routines_dir, layout.app_dir / "routines");
  EXPECT_EQ(layout.data_dir, layout.app_dir / "data");
}

TEST_F(DirLayoutValidatorTests, PathsExist) {
  EXPECT_TRUE(validator->Validate(layout));
}

TEST_F(DirLayoutValidatorTests, AppDirDoesNotExist) {
  stdfs::remove_all(layout.app_dir.native());
  EXPECT_FALSE(validator->Validate(layout));
}

TEST_F(DirLayoutValidatorTests, RoutinesDirDoesNotExist) {
  stdfs::remove(layout.routines_dir.native());
  EXPECT_FALSE(validator->Validate(layout));
}

TEST_F(DirLayoutValidatorTests, DataDirDoesNotExist) {
  stdfs::remove(layout.data_dir.native());
  EXPECT_FALSE(validator->Validate(layout));
}
} // namespace
} // namespace cdfw