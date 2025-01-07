// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_WIFI_H
#define CDFW_CORE_WIFI_H

// Local Headers
#include "cdfw/core/arduino.h"

namespace cdfw {
namespace core {
// Underscore suffix to avoid conflict with a macro defined by the Arduino
// SDK.
enum class WifiState { DISABLED_, DISCONNECTED, CONNECTED };

struct WifiCredentials {
  String ssid;
  String password;

  WifiCredentials() : ssid(""), password("") {}
  WifiCredentials(const String &ssid, const String &password)
      : ssid(ssid), password(password) {}
};
} // namespace core
} // namespace cdfw

#endif // CDFW_CORE_WIFI_H
