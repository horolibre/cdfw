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

  virtual std::string Serialize(const Routine &config) override final {
    JsonDocument doc;
    doc["name"] = config.name;

    JsonArray wet_stations = doc["wet_stations"].to<JsonArray>();
    for (std::size_t i = 0; i < 4; ++i) {
      JsonObject wet_station = wet_stations.add<JsonObject>();
      station_serializer_->Serialize(wet_station, config.wet_stations[i]);
    }

    JsonObject dry_station = doc["dry_station"].to<JsonObject>();
    station_serializer_->Serialize(dry_station, config.dry_station);

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

Routine Routine::GetDefault(void) {
  Routine config;
  config.name = "Default";
  std::string wet_names[4] = {"Clean", "Rinse 1", "Rinse 2", "Rinse 3"};
  for (std::size_t i = 0; i < 4; ++i) {
    config.wet_stations[i] = WetStation::GetDefault(wet_names[i]);
  }
  config.dry_station = DryStation::GetDefault("Dry");
  return config;
}

Routine::Routine()
    : name("Disabled"), wet_stations{WetStation::GetDisabled(),
                                     WetStation::GetDisabled(),
                                     WetStation::GetDisabled(),
                                     WetStation::GetDisabled()},
      dry_station(DryStation::GetDisabled()) {}

} // namespace cdfw
