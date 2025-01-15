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
class RoutineSerializerTests : public ::testing::Test {
protected:
  std::shared_ptr<RoutineSerializer> serializer = RoutineSerializer::Create();
};

TEST(RoutineTests, Disabled) {
  Routine routine = Routine::GetDisabled();

  EXPECT_EQ(routine.name, "Disabled");
  for (auto &station : routine.wet_stations) {
    EXPECT_EQ(station.name, "Disabled");
    EXPECT_FALSE(station.enabled);
    EXPECT_EQ(station.time, 0);
    EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kNONE);
  }
  EXPECT_EQ(routine.dry_station.name, "Disabled");
  EXPECT_FALSE(routine.dry_station.enabled);
  EXPECT_EQ(routine.dry_station.time, 0);
  EXPECT_EQ(routine.dry_station.spin, DryStation::SpinType::kNONE);
}

TEST(RoutineTests, Default) {
  Routine routine = Routine::GetDefault();

  EXPECT_EQ(routine.name, "Default");
  std::string names[4] = {"Clean", "Rinse 1", "Rinse 2", "Rinse 3"};
  for (std::size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(routine.wet_stations[i].name, names[i]);
    EXPECT_TRUE(routine.wet_stations[i].enabled);
    EXPECT_EQ(routine.wet_stations[i].time, 180);
    EXPECT_EQ(routine.wet_stations[i].agitation,
              WetStation::AgitationLevel::kMEDIUM);
  }
  EXPECT_EQ(routine.dry_station.name, "Dry");
  EXPECT_TRUE(routine.dry_station.enabled);
  EXPECT_EQ(routine.dry_station.time, 360);
  EXPECT_EQ(routine.dry_station.spin, DryStation::SpinType::kUNIDIRECTIONAL);
}

TEST(RoutineTests, Configured) {
  Routine routine = Routine::GetConfigured(
      "routine_configured",
      WetStation::GetConfigured("wet_1", 1, WetStation::AgitationLevel::kNONE),
      WetStation::GetConfigured("wet_2", 2, WetStation::AgitationLevel::kLOW),
      WetStation::GetConfigured("wet_3", 3,
                                WetStation::AgitationLevel::kMEDIUM),
      WetStation::GetConfigured("wet_4", 4, WetStation::AgitationLevel::kHIGH),
      DryStation::GetConfigured("dry", 5,
                                DryStation::SpinType::kBIDIRECTIONAL));

  EXPECT_EQ(routine.name, "routine_configured");
  // wet_1 assertions
  EXPECT_EQ(routine.wet_stations[0].name, "wet_1");
  EXPECT_TRUE(routine.wet_stations[0].enabled);
  EXPECT_EQ(routine.wet_stations[0].time, 1);
  EXPECT_EQ(routine.wet_stations[0].agitation,
            WetStation::AgitationLevel::kNONE);
  // wet_2 assertions
  EXPECT_EQ(routine.wet_stations[1].name, "wet_2");
  EXPECT_TRUE(routine.wet_stations[1].enabled);
  EXPECT_EQ(routine.wet_stations[1].time, 2);
  EXPECT_EQ(routine.wet_stations[1].agitation,
            WetStation::AgitationLevel::kLOW);
  // wet_3 assertions
  EXPECT_EQ(routine.wet_stations[2].name, "wet_3");
  EXPECT_TRUE(routine.wet_stations[2].enabled);
  EXPECT_EQ(routine.wet_stations[2].time, 3);
  EXPECT_EQ(routine.wet_stations[2].agitation,
            WetStation::AgitationLevel::kMEDIUM);
  // wet_4 assertions
  EXPECT_EQ(routine.wet_stations[3].name, "wet_4");
  EXPECT_TRUE(routine.wet_stations[3].enabled);
  EXPECT_EQ(routine.wet_stations[3].time, 4);
  EXPECT_EQ(routine.wet_stations[3].agitation,
            WetStation::AgitationLevel::kHIGH);
  // dry assertions
  EXPECT_EQ(routine.dry_station.name, "dry");
  EXPECT_TRUE(routine.dry_station.enabled);
  EXPECT_EQ(routine.dry_station.time, 5);
  EXPECT_EQ(routine.dry_station.spin, DryStation::SpinType::kBIDIRECTIONAL);
}

TEST_F(RoutineSerializerTests, Serialize_Disabled) {
  Routine routine = Routine::GetDisabled();
  std::string json = serializer->Serialize(routine);

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

TEST_F(RoutineSerializerTests, Serialize_Default) {
  Routine routine = Routine::GetDefault();
  std::string json = serializer->Serialize(routine);

  std::string expected =
      "{\"name\":\"Default\",\"wet_stations\":[{\"name\":\"Clean\",\"enabled\":"
      "true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "1\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "2\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "3\",\"enabled\":true,\"time\":180,\"agitation\":2}],\"dry_station\":{"
      "\"name\":\"Dry\",\"enabled\":true,\"time\":360,\"spin\":1}}";
  EXPECT_EQ(json, expected);
}

TEST_F(RoutineSerializerTests, Serialize_Configured) {
  Routine routine = Routine::GetDefault();
  routine.name = "routine_configured";
  routine.wet_stations[0] = WetStation::GetConfigured(
      "Clean", 1000, WetStation::AgitationLevel::kHIGH);
  routine.dry_station = DryStation::GetConfigured(
      "Dry", 1000, DryStation::SpinType::kBIDIRECTIONAL);
  std::string json = serializer->Serialize(routine);

  std::string expected =
      "{\"name\":\"routine_configured\",\"wet_stations\":[{\"name\":\"Clean\","
      "\"enabled\":true,\"time\":1000,\"agitation\":3},{\"name\":\"Rinse "
      "1\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "2\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "3\",\"enabled\":true,\"time\":180,\"agitation\":2}],\"dry_station\":{"
      "\"name\":\"Dry\",\"enabled\":true,\"time\":1000,\"spin\":2}}";
  EXPECT_EQ(json, expected);
}

TEST_F(RoutineSerializerTests, Deserialize_Disabled) {
  std::string input =
      "{\"name\":\"Disabled\",\"wet_stations\":[{\"name\":\"Disabled\","
      "\"enabled"
      "\":false,\"time\":0,\"agitation\":0},{\"name\":\"Disabled\",\"enabled\":"
      "false,\"time\":0,\"agitation\":0},{\"name\":\"Disabled\",\"enabled\":"
      "false,\"time\":0,\"agitation\":0},{\"name\":\"Disabled\",\"enabled\":"
      "false,\"time\":0,\"agitation\":0}],\"dry_station\":{\"name\":\"Disabled"
      "\",\"enabled\":false,\"time\":0,\"spin\":0}}";
  Routine routine = serializer->Deserialize(input);
  Routine expected = Routine::GetDisabled();

  EXPECT_EQ(routine.name, expected.name);
  for (std::size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(routine.wet_stations[i].name, expected.wet_stations[i].name);
    EXPECT_EQ(routine.wet_stations[i].enabled,
              expected.wet_stations[i].enabled);
    EXPECT_EQ(routine.wet_stations[i].time, expected.wet_stations[i].time);
    EXPECT_EQ(routine.wet_stations[i].agitation,
              expected.wet_stations[i].agitation);
  }
  EXPECT_EQ(routine.dry_station.name, expected.dry_station.name);
  EXPECT_EQ(routine.dry_station.enabled, expected.dry_station.enabled);
  EXPECT_EQ(routine.dry_station.time, expected.dry_station.time);
  EXPECT_EQ(routine.dry_station.spin, expected.dry_station.spin);
}

TEST_F(RoutineSerializerTests, Deserialize_Default) {
  std::string input =
      "{\"name\":\"Default\",\"wet_stations\":[{\"name\":\"Clean\",\"enabled\":"
      "true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "1\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "2\",\"enabled\":true,\"time\":180,\"agitation\":2},{\"name\":\"Rinse "
      "3\",\"enabled\":true,\"time\":180,\"agitation\":2}],\"dry_station\":{"
      "\"name\":\"Dry\",\"enabled\":true,\"time\":360,\"spin\":1}}";
  Routine routine = serializer->Deserialize(input);
  Routine expected = Routine::GetDefault();

  EXPECT_EQ(routine.name, expected.name);
  for (std::size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(routine.wet_stations[i].name, expected.wet_stations[i].name);
    EXPECT_EQ(routine.wet_stations[i].enabled,
              expected.wet_stations[i].enabled);
    EXPECT_EQ(routine.wet_stations[i].time, expected.wet_stations[i].time);
    EXPECT_EQ(routine.wet_stations[i].agitation,
              expected.wet_stations[i].agitation);
  }
  EXPECT_EQ(routine.dry_station.name, expected.dry_station.name);
  EXPECT_EQ(routine.dry_station.enabled, expected.dry_station.enabled);
  EXPECT_EQ(routine.dry_station.time, expected.dry_station.time);
  EXPECT_EQ(routine.dry_station.spin, expected.dry_station.spin);
}

TEST_F(RoutineSerializerTests, Deserialize_Configured) {
  std::string input =
      "{\"name\":\"routine_configured\",\"wet_stations\":[{\"name\":\"Clean\","
      "\"enabled\":true,\"time\":20,\"agitation\":0},{\"name\":\"Rinse "
      "1\",\"enabled\":true,\"time\":40,\"agitation\":1},{\"name\":\"Rinse "
      "2\",\"enabled\":true,\"time\":60,\"agitation\":2},{\"name\":\"Rinse "
      "3\",\"enabled\":true,\"time\":80,\"agitation\":3}],\"dry_station\":{"
      "\"name\":\"Dry\",\"enabled\":true,\"time\":100,\"spin\":2}}";
  Routine routine = serializer->Deserialize(input);
  Routine expected = Routine::GetConfigured(
      "routine_configured",
      WetStation::GetConfigured("Clean", 20, WetStation::AgitationLevel::kNONE),
      WetStation::GetConfigured("Rinse 1", 40,
                                WetStation::AgitationLevel::kLOW),
      WetStation::GetConfigured("Rinse 2", 60,
                                WetStation::AgitationLevel::kMEDIUM),
      WetStation::GetConfigured("Rinse 3", 80,
                                WetStation::AgitationLevel::kHIGH),
      DryStation::GetConfigured("Dry", 100,
                                DryStation::SpinType::kBIDIRECTIONAL));

  EXPECT_EQ(routine.name, expected.name);
  for (std::size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(routine.wet_stations[i].name, expected.wet_stations[i].name);
    EXPECT_EQ(routine.wet_stations[i].enabled,
              expected.wet_stations[i].enabled);
    EXPECT_EQ(routine.wet_stations[i].time, expected.wet_stations[i].time);
    EXPECT_EQ(routine.wet_stations[i].agitation,
              expected.wet_stations[i].agitation);
  }
  EXPECT_EQ(routine.dry_station.name, expected.dry_station.name);
  EXPECT_EQ(routine.dry_station.enabled, expected.dry_station.enabled);
  EXPECT_EQ(routine.dry_station.time, expected.dry_station.time);
  EXPECT_EQ(routine.dry_station.spin, expected.dry_station.spin);
}

} // namespace
} // namespace cdfw