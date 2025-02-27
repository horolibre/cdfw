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
#include <string>

namespace cdfw {

struct Routine {
  std::string name;

  // Turntable positions 1 - 4.
  WetStation wet_stations[4];

  // Turntable position 5.
  DryStation dry_station;

  virtual ~Routine() = default;

  // Returns the factory default routine configuration.
  static Routine GetDefault(void);

  // Returns a routine with all stations disabled.
  static Routine GetDisabled(void) { return Routine(); }

  // Returns a routine with the given configuration.
  static Routine GetConfigured(std::string name, WetStation wet1,
                               WetStation wet2, WetStation wet3,
                               WetStation wet4, DryStation dry) {
    return Routine{name, wet1, wet2, wet3, wet4, dry};
  }

protected:
  Routine();
  Routine(std::string name, WetStation wet1, WetStation wet2, WetStation wet3,
          WetStation wet4, DryStation dry)
      : name(name), wet_stations{wet1, wet2, wet3, wet4}, dry_station(dry) {}
};

class RoutineSerializer {
public:
  // Factory method.
  static std::shared_ptr<RoutineSerializer> Create();

  // Virtual destructor.
  virtual ~RoutineSerializer() = default;

  // Serializes the given routine.
  virtual std::string Serialize(const Routine &config) = 0;

  // Deserializes the given routine representation.
  virtual Routine Deserialize(const std::string &obj) = 0;
};
} // namespace cdfw

#endif // CDFW_CORE_ROUTINE_H
