// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef ARDUINO

// Local Headers
#include "cdfw/compat/arduino.h"

// Third Party Headers
#include <SDL2/SDL.h>

// C++ Standard Library Headers
#include <cstdint>
#include <cstdio>
#include <iostream>

// C Standard Library Headers
#include <stdarg.h>

// Global variables.
SimulatedSerial Serial;

unsigned long millis() { return SDL_GetTicks(); }

void delay(std::uint32_t ms) { SDL_Delay(ms); }

void SimulatedSerial::begin(unsigned long) { return; }

void SimulatedSerial::printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

void SimulatedSerial::print(const char *message) { std::cout << message; }
void SimulatedSerial::println(const char *message) {
  std::cout << message << std::endl;
}

#endif // ARDUINO