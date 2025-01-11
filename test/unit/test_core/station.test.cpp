// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/station.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <string>

namespace cdfw {
namespace {
namespace stdfs = std::filesystem;

TEST(DisabledStationConfigTests, Default) {
  DisabledStationConfig config;

  EXPECT_EQ(config.name, "Disabled");
  EXPECT_EQ(config.type, StationType::DISABLED);
}

TEST(WetStationConfigTests, Default) {
  std::string name = "wet_default";
  WetStationConfig config(name);

  EXPECT_EQ(config.name, name);
  EXPECT_EQ(config.type, StationType::WET);
  EXPECT_EQ(config.time, 180);
  EXPECT_EQ(config.agitation, WetStationConfig::AgitationLevel::MEDIUM);
}

TEST(WetStationConfigTests, Configured) {
  std::string name = "wet_configured";
  std::uint32_t time = 1000;
  auto agitation = WetStationConfig::AgitationLevel::HIGH;
  WetStationConfig config(name, time, agitation);

  EXPECT_EQ(config.name, name);
  EXPECT_EQ(config.type, StationType::WET);
  EXPECT_EQ(config.time, time);
  EXPECT_EQ(config.agitation, agitation);
}

TEST(DryStationConfigTests, Default) {
  std::string name = "dry_default";
  DryStationConfig config(name);

  EXPECT_EQ(config.name, name);
  EXPECT_EQ(config.type, StationType::DRY);
  EXPECT_EQ(config.time, 360);
  EXPECT_EQ(config.spin, DryStationConfig::SpinType::UNIDIRECTIONAL);
}

TEST(DryStationConfigTests, Configured) {
  std::string name = "dry_configured";
  std::uint32_t time = 1000;
  auto spin = DryStationConfig::SpinType::BIDIRECTIONAL;
  DryStationConfig config(name, time, spin);

  EXPECT_EQ(config.name, name);
  EXPECT_EQ(config.type, StationType::DRY);
  EXPECT_EQ(config.time, time);
  EXPECT_EQ(config.spin, spin);
}

} // namespace
} // namespace cdfw