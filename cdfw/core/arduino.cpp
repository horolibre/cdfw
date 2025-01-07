// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef ARDUINO

// Local Headers
#include "cdfw/core/arduino.h"

// Third Party Headers
#include <SDL2/SDL.h>

// C++ Standard Library Headers
#include <cstdint>

// Global variables.
SimulatedSerial Serial;

unsigned long millis() {
  return SDL_GetTicks();
}

void delay(std::uint32_t ms) {
  SDL_Delay(ms);
}

void SimulatedSerial::begin(unsigned long) { return; }

#endif // ARDUINO