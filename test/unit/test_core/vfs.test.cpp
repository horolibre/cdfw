// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/vfs.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <cstdint>
#include <filesystem>
#include <string>

namespace cdfw {
namespace vfs {
namespace {
namespace stdfs = std::filesystem;

class MockVolume : public Volume {
public:
  bool is_sd = false;
  std::uint64_t capacity = 0;
  std::uint64_t available = 0;
  std::uint64_t used = 0;
  std::string mount_point = "mp";

  MockVolume() = default;
  virtual ~MockVolume() = default;

  virtual bool IsSD() override final { return is_sd; }

  virtual std::uint64_t Capacity() override final { return capacity; }
  virtual std::uint64_t Available() override final { return available; }
  virtual std::uint64_t Used() override final { return used; }

  virtual vfs::Path MountPoint() override final { return "/sd"; }
  virtual vfs::Path TempDir() override final { return "/sd/tmp"; }
};

TEST(VFSVolumeTests, IsSD) {
  MockVolume mock_volume;
  auto volume = Volume::Create(&mock_volume);
  EXPECT_FALSE(volume->IsSD());
  mock_volume.is_sd = true;
  EXPECT_TRUE(volume->IsSD());
}
} // namespace
} // namespace vfs
} // namespace cdfw