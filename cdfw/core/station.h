// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_STATION_H
#define CDFW_CORE_STATION_H

// A station is the base element of a cleaning routine.
// Stations fall into two categories: wet (e.g., clean, rinse) and dry.

// C++ Standard Library Headers
#include <cstdint>
#include <string>

namespace cdfw {

// ---------------------------------------------------------------------------
// Abstract Station Config Type
// ---------------------------------------------------------------------------

// Every station has a name and a type.
struct StationConfig {
  std::string name;
  bool enabled;
  std::uint32_t time; // Time in seconds.

  virtual ~StationConfig() = default;

protected:
  StationConfig() = delete;
  StationConfig(std::string name, bool enabled, std::uint32_t time)
      : name(name), enabled(enabled), time(time) {}
};

// ---------------------------------------------------------------------------
// Concrete Station Config Types
// ---------------------------------------------------------------------------

// Represents a disabled station.

// Represents for clean and rinse stations.
struct WetStationConfig : StationConfig {
  enum class AgitationLevel : std::uint8_t {
    NONE = 0, // No agitation.
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
  };

  AgitationLevel agitation;

  virtual ~WetStationConfig() = default;

  // Default constructor creates a disabled station.
  WetStationConfig()
      : StationConfig("Disabled", false, 0), agitation(AgitationLevel::NONE) {}

  WetStationConfig(std::string name, std::uint32_t time,
                   AgitationLevel agitation)
      : StationConfig(name, true, time), agitation(agitation) {}

  // By default we assume:
  // - 3 minutes for the wet station.
  // - Medium agitation.
  WetStationConfig(std::string name)
      : StationConfig(name, true, 180), agitation(AgitationLevel::MEDIUM) {}
};

// Represents for dry stations.
struct DryStationConfig : StationConfig {
  enum class SpinType : std::uint8_t {
    NONE = 0,           // No spinning.
    UNIDIRECTIONAL = 1, // Spin in one direction.
    BIDIRECTIONAL = 2   // Spin in both directions.
  };

  SpinType spin;

  virtual ~DryStationConfig() = default;

  // Default constructor creates a disabled station.
  DryStationConfig()
      : StationConfig("Disabled", false, 0), spin(SpinType::NONE) {}

  DryStationConfig(std::string name, std::uint32_t time, SpinType spin)
      : StationConfig(name, true, time), spin(spin) {}

  // By default we assume:
  // - 6 minutes for the dry station.
  // - Uni-directional spin.
  DryStationConfig(std::string name)
      : StationConfig(name, true, 360), spin(SpinType::UNIDIRECTIONAL) {}
};

class StationSerializer {
public:
  // Factory method.
  static std::shared_ptr<StationSerializer> Create();

  // Virtual destructor.
  virtual ~StationSerializer() = default;

  // Serializes/Deserializes the given wet station configuration.
  virtual std::string Serialize(const WetStationConfig &config) = 0;

  // Serializes the given dry station configuration.
  virtual std::string Serialize(const DryStationConfig &config) = 0;
};

} // namespace cdfw

#endif // CDFW_CORE_STATION_H
