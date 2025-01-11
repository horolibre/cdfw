// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_ROUTINE_H
#define CDFW_CORE_ROUTINE_H

// A routine is the primary unit of work in the cleaner system. It is composed
// of a sequence of stations that are executed in order. Each position in the
// routine corresponds to a physical position on the cleaner turntable.
//
// Requirements:
// - The number of stations in a routine corresponds to the number of positions
//   on the cleaner turntable.
// - Stations not in use should have type StationType::DISABLED.
// - Stations 1 - 4:
//   - These stations must either StationType::WET and StationType::DISABLED.
// - Station 5:
//   - This station must be either StationType::DRY and StationType::DISABLED.

// Local Headers
#include "cdfw/core/station.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {

struct RoutineConfig {
  // Turntable positions 1 - 4.
  WetStationConfig wet_stations[4];

  // Turntable position 5.
  DryStationConfig dry_station;

  virtual ~RoutineConfig() = default;

  // Returns the factory default routine configuration.
  static RoutineConfig GetDefault(void);

  // Returns a routine with all stations disabled.
  static RoutineConfig GetDisabled(void) { return RoutineConfig(); }

protected:
  RoutineConfig();
};

class RoutineSerializer {
public:
  // Factory method.
  static std::shared_ptr<RoutineSerializer> Create();

  // Virtual destructor.
  virtual ~RoutineSerializer() = default;

  // Serializes the given routine configuration.
  virtual std::string Serialize(const RoutineConfig &config) = 0;
};
} // namespace cdfw

#endif // CDFW_CORE_ROUTINE_H
