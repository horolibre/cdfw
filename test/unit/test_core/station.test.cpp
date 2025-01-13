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
TEST(WetStationConfigTests, Disabled) {
  auto config = WetStationConfig::GetDisabled();

  EXPECT_EQ(config.name, "Disabled");
  EXPECT_FALSE(config.enabled);
  EXPECT_EQ(config.time, 0);
  EXPECT_EQ(config.agitation, WetStationConfig::AgitationLevel::kNONE);
}

TEST(WetStationConfigTests, Enabled_Default) {
  std::string name = "wet_default";
  auto config = WetStationConfig::GetDefault(name);

  EXPECT_EQ(config.name, name);
  EXPECT_TRUE(config.enabled);
  EXPECT_EQ(config.time, 180);
  EXPECT_EQ(config.agitation, WetStationConfig::AgitationLevel::kMEDIUM);
}

TEST(WetStationConfigTests, Enabled_Configured) {
  std::string name = "wet_configured";
  std::uint32_t time = 1000;
  auto agitation = WetStationConfig::AgitationLevel::kHIGH;
  auto config = WetStationConfig::GetConfigured(name, time, agitation);

  EXPECT_EQ(config.name, name);
  EXPECT_TRUE(config.enabled);
  EXPECT_EQ(config.time, time);
  EXPECT_EQ(config.agitation, agitation);
}

TEST(DryStationConfigTests, Disabled) {
  auto config = DryStationConfig::GetDisabled();

  EXPECT_EQ(config.name, "Disabled");
  EXPECT_FALSE(config.enabled);
  EXPECT_EQ(config.time, 0);
  EXPECT_EQ(config.spin, DryStationConfig::SpinType::kNONE);
}

TEST(DryStationConfigTests, Enabled_Default) {
  std::string name = "dry_default";
  auto config = DryStationConfig::GetDefault(name);

  EXPECT_EQ(config.name, name);
  EXPECT_TRUE(config.enabled);
  EXPECT_EQ(config.time, 360);
  EXPECT_EQ(config.spin, DryStationConfig::SpinType::kUNIDIRECTIONAL);
}

TEST(DryStationConfigTests, Enabled_Configured) {
  std::string name = "dry_configured";
  std::uint32_t time = 1000;
  auto spin = DryStationConfig::SpinType::kBIDIRECTIONAL;
  auto config = DryStationConfig::GetConfigured(name, time, spin);

  EXPECT_EQ(config.name, name);
  EXPECT_TRUE(config.enabled);
  EXPECT_EQ(config.time, time);
  EXPECT_EQ(config.spin, spin);
}

TEST(StationSerializerTests, Serialize_WetStation) {
  std::string name = "wet_configured";
  std::uint32_t time = 1000;
  auto agitation = WetStationConfig::AgitationLevel::kHIGH;
  auto config = WetStationConfig::GetConfigured(name, time, agitation);
  auto serializer = StationSerializer::Create();
  auto json_str = serializer->Serialize(config);

  std::string expected =
      R"({"name":"wet_configured","enabled":true,"time":1000,"agitation":3})";
  EXPECT_EQ(json_str, expected);
}

TEST(StationSerializerTests, Serialize_DryStation) {
  std::string name = "dry_configured";
  std::uint32_t time = 1000;
  auto spin = DryStationConfig::SpinType::kBIDIRECTIONAL;
  auto config = DryStationConfig::GetConfigured(name, time, spin);
  auto serializer = StationSerializer::Create();
  auto json_str = serializer->Serialize(config);

  std::string expected =
      R"({"name":"dry_configured","enabled":true,"time":1000,"spin":2})";
  EXPECT_EQ(json_str, expected);
}

} // namespace
} // namespace cdfw