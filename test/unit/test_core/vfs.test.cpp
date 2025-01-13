// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "test/mocks/vfs.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <cstdint>
#include <memory>

namespace cdfw {
namespace vfs {
namespace {
TEST(VFSVolumeTests, VolumeInfo) {
  MockVolume::Data data;
  data.is_sd = false;
  std::uint32_t capacity = 100;
  std::uint32_t used = 36;
  data.capacity = capacity;
  data.used = used;
  auto volume = Volume::Create(std::make_unique<MockVolume>(data));

  EXPECT_FALSE(volume->IsSD());
  EXPECT_EQ(volume->Capacity(), capacity);
  EXPECT_EQ(volume->Used(), used);
  EXPECT_EQ(volume->Available(), capacity - used);
  EXPECT_EQ(volume->MountPoint().native(), "/mp");
  EXPECT_EQ(volume->TempDir().native(), "/mp/tmp");

  data.is_sd = true;
  EXPECT_TRUE(volume->IsSD());
}

TEST(VFSVolumeTests, Exists) {
  MockVolume::Data data;
  Path path_exists = "/foo/bar";
  data.paths.insert(path_exists);
  auto volume = Volume::Create(std::make_unique<MockVolume>(data));
  Path path_not_exists = "/foo/baz";

  EXPECT_TRUE(volume->Exists(path_exists));
  EXPECT_FALSE(volume->Exists(path_not_exists));
}

TEST(VFSVolumeTests, CreateDirs) {
  MockVolume::Data data;
  auto volume = Volume::Create(std::make_unique<MockVolume>(data));
  Path path = "/foo/bar";
  EXPECT_FALSE(volume->Exists(path));

  EXPECT_TRUE(volume->CreateDirs(path));
  EXPECT_TRUE(volume->Exists(path));
}

TEST(VFSVolumeTests, Remove_NoChildren) {
  MockVolume::Data data;
  Path path = "/foo/bar";
  data.paths.insert(path);
  auto volume = Volume::Create(std::make_unique<MockVolume>(data));
  EXPECT_TRUE(volume->Exists(path));

  EXPECT_TRUE(volume->Remove(path));
  EXPECT_FALSE(volume->Exists(path));
}

TEST(VFSVolumeTests, Remove_HasChildren) {
  MockVolume::Data data;
  Path path = "/foo/bar";
  data.paths.insert(path);
  Path path_child = path / "baz";
  data.paths.insert(path_child);
  auto volume = Volume::Create(std::make_unique<MockVolume>(data));
  EXPECT_TRUE(volume->Exists(path));
  EXPECT_TRUE(volume->Exists(path_child));

  EXPECT_FALSE(volume->Remove(path));
  EXPECT_TRUE(volume->Exists(path));
  EXPECT_TRUE(volume->Exists(path_child));
}

TEST(VFSVolumeTests, RemoveAll) {
  MockVolume::Data data;
  Path path = "/foo/bar";
  data.paths.insert(path);
  Path path_child = path / "baz";
  data.paths.insert(path_child);
  auto volume = Volume::Create(std::make_unique<MockVolume>(data));
  EXPECT_TRUE(volume->Exists(path));
  EXPECT_TRUE(volume->Exists(path_child));

  EXPECT_TRUE(volume->RemoveAll(path));
  EXPECT_FALSE(volume->Exists(path));
  EXPECT_FALSE(volume->Exists(path_child));
}
} // namespace
} // namespace vfs
} // namespace cdfw