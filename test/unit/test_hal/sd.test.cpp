// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/hal/sd.h"

// Third Party Headers
#include <gtest/gtest.h>

namespace cdfw {
namespace hal {
namespace {
TEST(SDTests, SizingSanityCheck) {
  auto sd = SD::Create();
  EXPECT_GT(sd->GetCapacity(), 0);
  EXPECT_GT(sd->GetAvailable(), 0); // Seems safe to assume the SD is not full.
  EXPECT_GE(sd->GetCapacity(), sd->GetAvailable());
  EXPECT_GE(sd->GetCapacity(), sd->GetUsed());
}
} // namespace
} // namespace hal
} // namespace cdfw