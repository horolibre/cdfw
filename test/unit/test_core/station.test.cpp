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
class StationSerializerTests : public ::testing::Test {
protected:
  std::shared_ptr<StationSerializer> serializer = StationSerializer::Create();
};

TEST(WetStationTests, Disabled) {
  auto station = WetStation::GetDisabled();

  EXPECT_EQ(station.name, "Disabled");
  EXPECT_FALSE(station.enabled);
  EXPECT_EQ(station.time, 0);
  EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kNONE);
}

TEST(WetStationTests, Enabled_Default) {
  std::string name = "wet_default";
  auto station = WetStation::GetDefault(name);

  EXPECT_EQ(station.name, name);
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 180);
  EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kMEDIUM);
}

TEST(WetStationTests, Enabled_Configured) {
  std::string name = "wet_configured";
  std::uint32_t time = 1000;
  auto agitation = WetStation::AgitationLevel::kHIGH;
  auto station = WetStation::GetConfigured(name, time, agitation);

  EXPECT_EQ(station.name, name);
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, time);
  EXPECT_EQ(station.agitation, agitation);
}

TEST(DryStationTests, Disabled) {
  auto station = DryStation::GetDisabled();

  EXPECT_EQ(station.name, "Disabled");
  EXPECT_FALSE(station.enabled);
  EXPECT_EQ(station.time, 0);
  EXPECT_EQ(station.spin, DryStation::SpinType::kNONE);
}

TEST(DryStationTests, Enabled_Default) {
  std::string name = "dry_default";
  auto station = DryStation::GetDefault(name);

  EXPECT_EQ(station.name, name);
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 360);
  EXPECT_EQ(station.spin, DryStation::SpinType::kUNIDIRECTIONAL);
}

TEST(DryStationTests, Enabled_Configured) {
  std::string name = "dry_configured";
  std::uint32_t time = 1000;
  auto spin = DryStation::SpinType::kBIDIRECTIONAL;
  auto station = DryStation::GetConfigured(name, time, spin);

  EXPECT_EQ(station.name, name);
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, time);
  EXPECT_EQ(station.spin, spin);
}

TEST_F(StationSerializerTests, Serialize_WetStation) {
  std::string name = "wet_configured";
  std::uint32_t time = 1000;
  auto agitation = WetStation::AgitationLevel::kHIGH;
  auto station = WetStation::GetConfigured(name, time, agitation);
  auto json_str = serializer->Serialize(station);

  std::string expected =
      R"({"name":"wet_configured","enabled":true,"time":1000,"agitation":3})";
  EXPECT_EQ(json_str, expected);
}

TEST_F(StationSerializerTests, Serialize_DryStation) {
  std::string name = "dry_configured";
  std::uint32_t time = 1000;
  auto spin = DryStation::SpinType::kBIDIRECTIONAL;
  auto station = DryStation::GetConfigured(name, time, spin);
  auto json_str = serializer->Serialize(station);

  std::string expected =
      R"({"name":"dry_configured","enabled":true,"time":1000,"spin":2})";
  EXPECT_EQ(json_str, expected);
}

TEST_F(StationSerializerTests, Deserialize_WetStation_Disabled) {
  std::string input =
      R"({"name":"wet_configured","enabled":false,"time":1000,"agitation":3})";
  auto station = serializer->DeserializeWet(input);

  EXPECT_EQ(station.name, "Disabled");
  EXPECT_FALSE(station.enabled);
  EXPECT_EQ(station.time, 0);
  EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kNONE);
}

TEST_F(StationSerializerTests, Deserialize_WetStation_Configured) {
  // WetStation::AgitationLevel::kNONE
  std::string input =
      R"({"name":"wet_agg_none","enabled":true,"time":10,"agitation":0})";
  auto station = serializer->DeserializeWet(input);

  EXPECT_EQ(station.name, "wet_agg_none");
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 10);
  EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kNONE);

  // WetStation::AgitationLevel::kLOW
  input = R"({"name":"wet_agg_low","enabled":true,"time":20,"agitation":1})";
  station = serializer->DeserializeWet(input);

  EXPECT_EQ(station.name, "wet_agg_low");
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 20);
  EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kLOW);

  // WetStation::AgitationLevel::kMEDIUM
  input = R"({"name":"wet_agg_med","enabled":true,"time":30,"agitation":2})";
  station = serializer->DeserializeWet(input);

  EXPECT_EQ(station.name, "wet_agg_med");
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 30);
  EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kMEDIUM);

  // WetStation::AgitationLevel::kHIGH
  input = R"({"name":"wet_agg_high","enabled":true,"time":40,"agitation":3})";
  station = serializer->DeserializeWet(input);

  EXPECT_EQ(station.name, "wet_agg_high");
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 40);
  EXPECT_EQ(station.agitation, WetStation::AgitationLevel::kHIGH);
}

TEST_F(StationSerializerTests, Deserialize_DryStation_Disabled) {
  std::string input =
      R"({"name":"dry_configured","enabled":false,"time":1000,"spin":1})";
  auto station = serializer->DeserializeDry(input);

  EXPECT_EQ(station.name, "Disabled");
  EXPECT_FALSE(station.enabled);
  EXPECT_EQ(station.time, 0);
  EXPECT_EQ(station.spin, DryStation::SpinType::kNONE);
}

TEST_F(StationSerializerTests, Deserialize_DryStation_Configured) {
  // DryStation::SpinType::kNONE
  std::string input =
      R"({"name":"dry_spin_none","enabled":true,"time":20,"spin":0})";
  auto station = serializer->DeserializeDry(input);

  EXPECT_EQ(station.name, "dry_spin_none");
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 20);
  EXPECT_EQ(station.spin, DryStation::SpinType::kNONE);

  // DryStation::SpinType::kUNIDIRECTIONAL
  input = R"({"name":"dry_spin_uni","enabled":true,"time":40,"spin":1})";
  station = serializer->DeserializeDry(input);

  EXPECT_EQ(station.name, "dry_spin_uni");
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 40);
  EXPECT_EQ(station.spin, DryStation::SpinType::kUNIDIRECTIONAL);

  // DryStation::SpinType::kBIDIRECTIONAL
  input = R"({"name":"dry_spin_bi","enabled":true,"time":60,"spin":2})";
  station = serializer->DeserializeDry(input);

  EXPECT_EQ(station.name, "dry_spin_bi");
  EXPECT_TRUE(station.enabled);
  EXPECT_EQ(station.time, 60);
  EXPECT_EQ(station.spin, DryStation::SpinType::kBIDIRECTIONAL);
}

TEST_F(StationSerializerTests, RoundTrip_WetStation) {
  auto expected = WetStation::GetConfigured("Clean", 123,
                                            WetStation::AgitationLevel::kHIGH);
  auto actual = serializer->DeserializeWet(serializer->Serialize(expected));

  EXPECT_EQ(actual.name, expected.name);
  EXPECT_EQ(actual.enabled, expected.enabled);
  EXPECT_EQ(actual.time, expected.time);
  EXPECT_EQ(actual.agitation, expected.agitation);
}

TEST_F(StationSerializerTests, RoundTrip_DryStation) {
  auto expected = DryStation::GetConfigured(
      "Dry", 123, DryStation::SpinType::kUNIDIRECTIONAL);
  auto actual = serializer->DeserializeDry(serializer->Serialize(expected));

  EXPECT_EQ(actual.name, expected.name);
  EXPECT_EQ(actual.enabled, expected.enabled);
  EXPECT_EQ(actual.time, expected.time);
  EXPECT_EQ(actual.spin, expected.spin);
}

} // namespace
} // namespace cdfw