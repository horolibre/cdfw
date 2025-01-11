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
/*
class RoutineSerializerImpl : public StationSerializer {
public:
RoutineSerializerImpl() = default;
virtual ~RoutineSerializerImpl() = default;

virtual std::string Serialize(const RoutineConfig &config) override final {
JsonDocument doc;
doc["name"] = config.name;
doc["enabled"] = config.enabled;
doc["time"] = config.time;
doc["agitation"] = static_cast<std::uint8_t>(config.agitation);

std::string json_str;
serializeJson(doc, json_str);
return json_str;
}

virtual std::string Serialize(const RoutineConfig &config) override final {
JsonDocument doc;
doc["name"] = config.name;
doc["enabled"] = config.enabled;
doc["time"] = config.time;
doc["spin"] = static_cast<std::uint8_t>(config.spin);

std::string json_str;
serializeJson(doc, json_str);
return json_str;
}
};
*/
} // namespace

/*
std::shared_ptr<StationSerializer> StationSerializer::Create() {
  return std::make_shared<StationSerializerImpl>();
}
*/

RoutineConfig RoutineConfig::GetDefault(void) {
  RoutineConfig config;
  std::string names[4] = {"Clean", "Rinse 1", "Rinse 2", "Rinse 3"};
  for (std::size_t i = 0; i < 4; ++i) {
    config.wet_stations[i] = WetStationConfig(names[i]);
  }
  config.dry_station = DryStationConfig("Dry");
  return config;
}

} // namespace cdfw
