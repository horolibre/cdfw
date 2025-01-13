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

  void SetUp() override final { sd = SD::Create(); }
};

TEST_F(SDTests, Type_SanityCheck) { EXPECT_TRUE(sd->IsSD()); }

TEST_F(SDTests, Size_SanityCheck) {
  EXPECT_GT(sd->Capacity(), 0);
  EXPECT_GT(sd->Available(), 0); // Seems safe to assume the SD is not full.
  EXPECT_GE(sd->Capacity(), sd->Available());
  EXPECT_GE(sd->Capacity(), sd->Used());
  EXPECT_TRUE(true);
}

TEST_F(SDTests, Root) { EXPECT_EQ(sd->MountPoint().filename(), "sd"); }

} // namespace
} // namespace hal
} // namespace cdfw