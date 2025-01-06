// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef ARDUINO

// Local Headers
#include "cdfw/core/arduino.h"

// C++ Standard Library Headers
#include <chrono>
#include <cstdint>

// Global variables.
SimulatedSerial Serial;

namespace {
std::chrono::milliseconds GetCurrentTime() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
}

// Record time at start of program.
std::chrono::milliseconds start_time = GetCurrentTime();
} // namespace

unsigned long millis() {
  auto current_time = GetCurrentTime();
  auto elapsed_time = current_time - start_time;
  return elapsed_time.count();
}

void delay(std::uint32_t ms) {
  auto end_time = GetCurrentTime() + std::chrono::milliseconds(ms);
  while (GetCurrentTime() < end_time) {
    // Wait until enough time has passed.
  }
}

void SimulatedSerial::begin(unsigned long) { return; }

#endif // ARDUINO