// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/routine.h"
#include "cdfw/core/station.h"

// Third Party Headers
#include <ArduinoJson.h>

// C++ Standard Library Headers
#include <cstdint>
#include <string>

namespace cdfw {
namespace {
class RoutineSerializerImpl : public RoutineSerializer {
public:
  RoutineSerializerImpl() : station_serializer_(StationSerializer::Create()) {}
  virtual ~RoutineSerializerImpl() = default;

  virtual std::string Serialize(const RoutineConfig &config) override final {
    JsonDocument doc;
    for (std::size_t i = 0; i < 4; ++i) {
      station_serializer_->Serialize(doc, config.wet_stations[i]);
    }
    station_serializer_->Serialize(doc, config.dry_station);

    std::string json_str;
    serializeJson(doc, json_str);
    return json_str;
  }

private:
  std::shared_ptr<StationSerializer> station_serializer_;
};
} // namespace

std::shared_ptr<RoutineSerializer> RoutineSerializer::Create() {
  return std::make_shared<RoutineSerializerImpl>();
}

RoutineConfig RoutineConfig::GetDefault(void) {
  RoutineConfig config;
  std::string names[4] = {"Clean", "Rinse 1", "Rinse 2", "Rinse 3"};
  for (std::size_t i = 0; i < 4; ++i) {
    config.wet_stations[i] = WetStationConfig::GetDefault(names[i]);
  }
  config.dry_station = DryStationConfig::GetDefault("Dry");
  return config;
}

RoutineConfig::RoutineConfig()
    : wet_stations{WetStationConfig::GetDisabled(),
                   WetStationConfig::GetDisabled(),
                   WetStationConfig::GetDisabled(),
                   WetStationConfig::GetDisabled()},
      dry_station(DryStationConfig::GetDisabled()) {}

} // namespace cdfw
