// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/routine.h"
#include "cdfw/core/station.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <string>

namespace cdfw {
namespace {
namespace stdfs = std::filesystem;

TEST(RoutineConfigTests, Default) {
  // Default constructed routine has all stations disabled.
  RoutineConfig config;

  for (auto &station : config.wet_stations) {
    EXPECT_EQ(station.name, "Disabled");
    EXPECT_FALSE(station.enabled);
    EXPECT_EQ(station.time, 0);
    EXPECT_EQ(station.agitation, WetStationConfig::AgitationLevel::NONE);
  }

  EXPECT_EQ(config.dry_station.name, "Disabled");
  EXPECT_FALSE(config.dry_station.enabled);
  EXPECT_EQ(config.dry_station.time, 0);
  EXPECT_EQ(config.dry_station.spin, DryStationConfig::SpinType::NONE);
}

} // namespace
} // namespace cdfw