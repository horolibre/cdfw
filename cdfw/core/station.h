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

enum class StationType : std::uint8_t {
  DISABLED = 0, // Indicates an inactive station.
  WET = 1,
  DRY = 2
};

// ---------------------------------------------------------------------------
// Abstract Station Config Types
// ---------------------------------------------------------------------------

// Every station has a name and a type.
struct BaseStationConfig {
  std::string name;
  StationType type;

protected:
  BaseStationConfig() = delete;
  BaseStationConfig(std::string name, StationType type)
      : name(name), type(type) {}
};

// Non-disabled stations have a time.
struct TimedStationConfig : BaseStationConfig {
  std::uint32_t time; // Time in seconds.

protected:
  TimedStationConfig() = delete;
  TimedStationConfig(std::string name, StationType type, std::uint32_t time)
      : BaseStationConfig(name, type), time(time) {}
};

// ---------------------------------------------------------------------------
// Concrete Station Config Types
// ---------------------------------------------------------------------------

// Represents a disabled station.
// Note: There only needs be one instance of this in the system at most.
// However, this is currently just a statement for an optimization in the future
// and not something enforced.
struct DisabledStationConfig : BaseStationConfig {
  DisabledStationConfig()
      : BaseStationConfig("Disabled", StationType::DISABLED) {}
};

// Represents for clean and rinse stations.
struct WetStationConfig : TimedStationConfig {
  enum class AgitationLevel : std::uint8_t {
    NONE = 0, // No agitation.
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
  };

  AgitationLevel agitation;

  WetStationConfig(std::string name, std::uint32_t time,
                   AgitationLevel agitation)
      : TimedStationConfig(name, StationType::WET, time), agitation(agitation) {
  }

  // By default we assume:
  // - 3 minutes for the wet station.
  // - Medium agitation.
  WetStationConfig(std::string name)
      : TimedStationConfig(name, StationType::WET, 180),
        agitation(AgitationLevel::MEDIUM) {}
};

// Represents for dry stations.
struct DryStationConfig : TimedStationConfig {
  enum class SpinType : std::uint8_t {
    NONE = 0,           // No spinning.
    UNIDIRECTIONAL = 1, // Spin in one direction.
    BIDIRECTIONAL = 2   // Spin in both directions.
  };

  SpinType spin;

  DryStationConfig(std::string name, std::uint32_t time, SpinType spin)
      : TimedStationConfig(name, StationType::DRY, time), spin(spin) {}

  // By default we assume:
  // - 6 minutes for the dry station.
  // - Uni-directional spin.
  DryStationConfig(std::string name)
      : TimedStationConfig(name, StationType::DRY, 360),
        spin(SpinType::UNIDIRECTIONAL) {}
};
} // namespace cdfw

#endif // CDFW_CORE_STATION_H
