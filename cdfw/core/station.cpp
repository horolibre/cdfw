// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/station.h"

// Third Party Headers
#include <ArduinoJson.h>

// C++ Standard Library Headers
#include <cstdint>
#include <string>

namespace cdfw {
namespace {
class StationSerializerImpl : public StationSerializer {
public:
  StationSerializerImpl() = default;
  virtual ~StationSerializerImpl() = default;

  virtual void Serialize(JsonObject &obj,
                         const WetStation &config) override final {
    obj["name"] = config.name;
    obj["enabled"] = config.enabled;
    obj["time"] = config.time;
    obj["agitation"] = static_cast<std::uint8_t>(config.agitation);
  }

  virtual std::string Serialize(const WetStation &config) override final {
    JsonDocument doc;
    JsonObject obj = doc.add<JsonObject>();
    Serialize(obj, config);

    std::string json_str;
    serializeJson(obj, json_str);
    return json_str;
  }

  virtual void Serialize(JsonObject &obj,
                         const DryStation &config) override final {
    obj["name"] = config.name;
    obj["enabled"] = config.enabled;
    obj["time"] = config.time;
    obj["spin"] = static_cast<std::uint8_t>(config.spin);
  }

  virtual std::string Serialize(const DryStation &config) override final {
    JsonDocument doc;
    JsonObject obj = doc.add<JsonObject>();
    Serialize(obj, config);

    std::string json_str;
    serializeJson(obj, json_str);
    return json_str;
  }
};
} // namespace

std::shared_ptr<StationSerializer> StationSerializer::Create() {
  return std::make_shared<StationSerializerImpl>();
}

} // namespace cdfw
