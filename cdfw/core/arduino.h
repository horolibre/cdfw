// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_ARDUINO_H
#define CDFW_CORE_ARDUINO_H

#ifdef ARDUINO
// Third Party Headers
#include <Arduino.h>

#else // ARDUINO
// No Arduino framework available, so we need to simulate it.

// C++ Standard Library Headers
#include <cstdint>
#include <string>

// TYPES

using String = std::string;

// FREE FUNCTIONS

unsigned long millis();
void delay(std::uint32_t ms);

// CLASSES

class SimulatedSerial {
public:
  void begin(unsigned long baud);
  // void print(const char *message);
  // void println(const char *message);
};

// GLOBAL VARIABLES

extern SimulatedSerial Serial;

#endif // ARDUINO

#endif // CDFW_CORE_ARDUINO_H
