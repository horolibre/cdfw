// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/hal/sd.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <memory>
#include <string>

namespace cdfw {
namespace hal {
namespace {
class SDTests : public ::testing::Test {
protected:
  std::unique_ptr<SD> sd = nullptr;
  vfs::Path tmp_dir;

  void SetUp() override final {
    sd = SD::Create();
    tmp_dir = sd->TempDir();
  }

  void TearDown() override final {
    if (sd->Exists(tmp_dir)) {
      sd->RemoveAll(tmp_dir);
    }
  }
};

TEST_F(SDTests, Type_SanityCheck) { EXPECT_TRUE(sd->IsSD()); }

TEST_F(SDTests, Size_SanityCheck) {
  EXPECT_GT(sd->Capacity(), 0);
  EXPECT_GT(sd->Available(), 0); // Seems safe to assume the SD is not full.
  EXPECT_GE(sd->Capacity(), sd->Available());
  EXPECT_GE(sd->Capacity(), sd->Used());
  EXPECT_TRUE(true);
}

TEST_F(SDTests, MountPoint) { EXPECT_EQ(sd->MountPoint().filename(), "sd"); }

TEST_F(SDTests, TempDir) { EXPECT_EQ(sd->TempDir().filename(), "tmp"); }

TEST_F(SDTests, CreateDirs_And_Exists) {
  vfs::Path p_a = tmp_dir / "a";
  vfs::Path p_child = p_a / "child";
  vfs::Path p_b = tmp_dir / "b";
  vfs::Path path_not_exists = tmp_dir / "c";
  EXPECT_FALSE(sd->Exists(p_a));
  EXPECT_FALSE(sd->Exists(p_child));
  EXPECT_FALSE(sd->Exists(p_b));
  EXPECT_FALSE(sd->Exists(path_not_exists));

  sd->CreateDirs(p_a);
  sd->CreateDirs(p_child);
  sd->CreateDirs(p_b);
  EXPECT_TRUE(sd->Exists(p_a));
  EXPECT_TRUE(sd->Exists(p_child));
  EXPECT_TRUE(sd->Exists(p_b));
  EXPECT_FALSE(sd->Exists(path_not_exists));
}

TEST_F(SDTests, Remove) {
  vfs::Path p = tmp_dir / "a";
  sd->CreateDirs(p);
  EXPECT_TRUE(sd->Exists(p));

  sd->Remove(p);
  EXPECT_FALSE(sd->Exists(p));
}

TEST_F(SDTests, RemoveAll) {
  vfs::Path p_a = tmp_dir / "a";
  vfs::Path p_child = p_a / "child";
  vfs::Path p_b = tmp_dir / "b";
  sd->CreateDirs(p_a);
  sd->CreateDirs(p_child);
  sd->CreateDirs(p_b);
  EXPECT_TRUE(sd->Exists(p_a));
  EXPECT_TRUE(sd->Exists(p_child));
  EXPECT_TRUE(sd->Exists(p_b));

  sd->RemoveAll(p_a);
  EXPECT_FALSE(sd->Exists(p_a));
  EXPECT_FALSE(sd->Exists(p_child));
  EXPECT_TRUE(sd->Exists(p_b));
}
} // namespace
} // namespace hal
} // namespace cdfw