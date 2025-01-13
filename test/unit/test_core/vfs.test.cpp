// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "test/mocks/vfs.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace vfs {
namespace {
TEST(VFSVolumeTests, IsSD) {
  MockVolume::Data data;
  auto volume = Volume::Create(std::make_unique<MockVolume>(data));
  EXPECT_FALSE(volume->IsSD());
  data.is_sd = true;
  EXPECT_TRUE(volume->IsSD());
}
} // namespace
} // namespace vfs
} // namespace cdfw