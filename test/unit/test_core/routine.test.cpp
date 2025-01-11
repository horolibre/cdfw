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

TEST(RoutineConfigTests, Disabled) {
  RoutineConfig config = RoutineConfig::GetDisabled();

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

TEST(RoutineConfigTests, Default) {
  RoutineConfig config = RoutineConfig::GetDefault();

  std::string names[4] = {"Clean", "Rinse 1", "Rinse 2", "Rinse 3"};
  for (std::size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(config.wet_stations[i].name, names[i]);
    EXPECT_TRUE(config.wet_stations[i].enabled);
    EXPECT_EQ(config.wet_stations[i].time, 180);
    EXPECT_EQ(config.wet_stations[i].agitation,
              WetStationConfig::AgitationLevel::MEDIUM);
  }

  EXPECT_EQ(config.dry_station.name, "Dry");
  EXPECT_TRUE(config.dry_station.enabled);
  EXPECT_EQ(config.dry_station.time, 360);
  EXPECT_EQ(config.dry_station.spin,
            DryStationConfig::SpinType::UNIDIRECTIONAL);
}

} // namespace
} // namespace cdfw