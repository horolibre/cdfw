// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_layout.h"
#include "test/mocks/vfs.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <filesystem>

namespace cdfw {
namespace {
namespace stdfs = std::filesystem;

class DirLayoutValidatorTests : public ::testing::Test {
protected:
  vfs::MockVolume::Data data;
  vfs::MockVolume volume = vfs::MockVolume(data);
  vfs::Path tmp_dir = volume.TempDir() / "test";
  std::shared_ptr<DirLayoutValidator> validator = DirLayoutValidator::Create();
  DirLayout layout = DirLayout(tmp_dir);

  void SetUp() override {
    volume.CreateDirs(tmp_dir);
    EXPECT_TRUE(volume.Exists(tmp_dir));

    volume.CreateDirs(layout.app_dir);
    volume.CreateDirs(layout.routines_dir);
    volume.CreateDirs(layout.data_dir);
    EXPECT_TRUE(volume.Exists(layout.app_dir));
    EXPECT_TRUE(volume.Exists(layout.routines_dir));
    EXPECT_TRUE(volume.Exists(layout.data_dir));
  }
};

TEST(DirLayoutTests, Layout) {
  auto tmp_dir = vfs::Path("foo");
  DirLayout layout(tmp_dir);

  EXPECT_EQ(layout.app_dir, tmp_dir / "horolibre");
  EXPECT_EQ(layout.routines_dir, layout.app_dir / "routines");
  EXPECT_EQ(layout.data_dir, layout.app_dir / "data");
}

TEST_F(DirLayoutValidatorTests, PathsExist) {
  EXPECT_TRUE(validator->Validate(volume, layout));
}

TEST_F(DirLayoutValidatorTests, AppDirDoesNotExist) {
  volume.RemoveAll(layout.app_dir);
  EXPECT_FALSE(validator->Validate(volume, layout));
}

TEST_F(DirLayoutValidatorTests, RoutinesDirDoesNotExist) {
  volume.Remove(layout.routines_dir);
  EXPECT_FALSE(validator->Validate(volume, layout));
}

TEST_F(DirLayoutValidatorTests, DataDirDoesNotExist) {
  volume.Remove(layout.data_dir);
  EXPECT_FALSE(validator->Validate(volume, layout));
}
} // namespace
} // namespace cdfw