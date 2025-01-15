// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_STATION_H
#define CDFW_CORE_STATION_H

// A station is the base element of a cleaning routine.
// Stations fall into two categories: wet (e.g., clean, rinse) and dry.

// Third Party Headers
#include <ArduinoJson.h>

// C++ Standard Library Headers
#include <cstdint>
#include <memory>
#include <string>

namespace cdfw {

// ---------------------------------------------------------------------------
// Abstract Station Config Type
// ---------------------------------------------------------------------------

// Every station has a name and a type.
struct Station {
  std::string name;
  bool enabled;
  std::uint32_t time; // Time in seconds.

  virtual ~Station() = default;

protected:
  Station() = default;
  Station(std::string name, bool enabled, std::uint32_t time)
      : name(name), enabled(enabled), time(time) {}
};

// ---------------------------------------------------------------------------
// Concrete Station Config Types
// ---------------------------------------------------------------------------

// Represents a disabled station.

// Represents for clean and rinse stations.
struct WetStation : Station {
  enum class AgitationLevel : std::uint8_t {
    kNONE = 0, // No agitation.
    kLOW = 1,
    kMEDIUM = 2,
    kHIGH = 3
  };

  AgitationLevel agitation;

  virtual ~WetStation() = default;

  static WetStation GetDefault(std::string name) {
    return WetStation(name);
  }
  static WetStation GetDisabled() { return WetStation(); }
  static WetStation GetConfigured(std::string name, std::uint32_t time,
                                        AgitationLevel agitation) {
    return WetStation(name, time, agitation);
  }

private:
  // Default constructor creates a disabled station.
  WetStation()
      : Station("Disabled", false, 0), agitation(AgitationLevel::kNONE) {}

  // Constructor for a configured station.
  WetStation(std::string name, std::uint32_t time,
                   AgitationLevel agitation)
      : Station(name, true, time), agitation(agitation) {}

  // By default we assume:
  // - 3 minutes for the wet station.
  // - Medium agitation.
  WetStation(std::string name)
      : Station(name, true, 180), agitation(AgitationLevel::kMEDIUM) {}
};

// Represents for dry stations.
struct DryStation : Station {
  enum class SpinType : std::uint8_t {
    kNONE = 0,           // No spinning.
    kUNIDIRECTIONAL = 1, // Spin in one direction.
    kBIDIRECTIONAL = 2   // Spin in both directions.
  };

  SpinType spin;

  virtual ~DryStation() = default;

  static DryStation GetDefault(std::string name) {
    return DryStation(name);
  }
  static DryStation GetDisabled() { return DryStation(); }
  static DryStation GetConfigured(std::string name, std::uint32_t time,
                                        SpinType spin) {
    return DryStation(name, time, spin);
  }

private:
  // Default constructor creates a disabled station.
  DryStation()
      : Station("Disabled", false, 0), spin(SpinType::kNONE) {}

  // Constructor for a configured station.
  DryStation(std::string name, std::uint32_t time, SpinType spin)
      : Station(name, true, time), spin(spin) {}

  // By default we assume:
  // - 6 minutes for the dry station.
  // - Uni-directional spin.
  DryStation(std::string name)
      : Station(name, true, 360), spin(SpinType::kUNIDIRECTIONAL) {}
};

class StationSerializer {
public:
  // Factory method.
  static std::shared_ptr<StationSerializer> Create();

  // Virtual destructor.
  virtual ~StationSerializer() = default;

  // Serializes/Deserializes the given wet station configuration.
  virtual void Serialize(JsonObject &obj, const WetStation &config) = 0;
  virtual std::string Serialize(const WetStation &config) = 0;

  // Serializes the given dry station configuration.
  virtual void Serialize(JsonObject &dobj, const DryStation &config) = 0;
  virtual std::string Serialize(const DryStation &config) = 0;
};

} // namespace cdfw

#endif // CDFW_CORE_STATION_H
