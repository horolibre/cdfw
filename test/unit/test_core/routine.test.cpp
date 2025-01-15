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
TEST(RoutineTests, Disabled) {
  Routine config = Routine::GetDisabled();

  for (auto &station : config.wet_stations) {
    EXPECT_EQ(station.name, "Disabled");
    EXPECT_FALSE(station.enabled);
    EXPECT_EQ(station.time, 0);
    EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kNONE);
  }

  EXPECT_EQ(config.dry_station.name, "Disabled");
  EXPECT_FALSE(config.dry_station.enabled);
  EXPECT_EQ(config.dry_station.time, 0);
  EXPECT_EQ(config.dry_station.spin, DryStation::SpinType::kNONE);
}

TEST(RoutineTests, Default) {
  Routine config = Routine::GetDefault();

  std::string names[4] = {"Clean", "Rinse 1", "Rinse 2", "Rinse 3"};
  for (std::size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(config.wet_stations[i].name, names[i]);
    EXPECT_TRUE(config.wet_stations[i].enabled);
    EXPECT_EQ(config.wet_stations[i].time, 180);
    EXPECT_EQ(config.wet_stations[i].agitation,
              WetStation::AgitationLevel::kMEDIUM);
  }

  EXPECT_EQ(config.dry_station.name, "Dry");
  EXPECT_TRUE(config.dry_station.enabled);
  EXPECT_EQ(config.dry_station.time, 360);
  EXPECT_EQ(config.dry_station.spin, DryStation::SpinType::kUNIDIRECTIONAL);
}

TEST(RoutineSerializerTests, Serialize_Disabled) {
  auto serializer = RoutineSerializer::Create();
  Routine config = Routine::GetDisabled();
  std::string json = serializer->Serialize(config);

  std::string expected =
      "{\"name\":\"Disabled\",\"wet_stations\":[{\"name\":\"Disabled\","
      "\"enabled"
      "\":false,\"time\":0,\"agitation\":0},{\"name\":\"Disabled\",\"enabled\":"
      "false,\"time\":0,\"agitation\":0},{\"name\":\"Disabled\",\"enabled\":"
      "false,\"time\":0,\"agitation\":0},{\"name\":\"Disabled\",\"enabled\":"
      "false,\"time\":0,\"agitation\":0}],\"dry_station\":{\"name\":\"Disabled"
      "\",\"enabled\":false,\"time\":0,\"spin\":0}}";
  EXPECT_EQ(json, expected);
}

TEST(RoutineSerializerTests, Serialize_Default) {
  auto serializer = RoutineSerializer::Create();
  Routine config = Routine::GetDefault();
  std::string json = serializer->Serialize(config);

  std::string expected =
      "{\"name\":\"Default\",\"wet_stations\":[{\"name\":\"Clean\",\"enabled\":"
      "true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "1\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "2\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "3\",\"enabled\":true,\"time\":180,\"agitation\":2}],\"dry_station\":{"
      "\"name\":\"Dry\",\"enabled\":true,\"time\":360,\"spin\":1}}";
  EXPECT_EQ(json, expected);
}

TEST(RoutineSerializerTests, Serialize_Configured) {
  auto serializer = RoutineSerializer::Create();
  Routine config = Routine::GetDefault();
  config.name = "routine_configured";
  config.wet_stations[0] = WetStation::GetConfigured(
      "Clean", 1000, WetStation::AgitationLevel::kHIGH);
  config.dry_station = DryStation::GetConfigured(
      "Dry", 1000, DryStation::SpinType::kBIDIRECTIONAL);
  std::string json = serializer->Serialize(config);

  std::string expected =
      "{\"name\":\"routine_configured\",\"wet_stations\":[{\"name\":\"Clean\","
      "\"enabled\":true,\"time\":1000,\"agitation\":3},{\"name\":\"Rinse "
      "1\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "2\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "3\",\"enabled\":true,\"time\":180,\"agitation\":2}],\"dry_station\":{"
      "\"name\":\"Dry\",\"enabled\":true,\"time\":1000,\"spin\":2}}";
  EXPECT_EQ(json, expected);
}

} // namespace
} // namespace cdfw