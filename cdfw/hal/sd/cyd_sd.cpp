// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_CYD

// Local Headers
#include "cdfw/core/arduino.h"
#include "cdfw/hal/sd.h"

// Third Party Headers
#include <FS.h>
#include <SD.h>
#include <SPI.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace hal {
namespace {
class SDImpl : public hal::SD {
public:
  SDImpl() : spi_(SPIClass(VSPI)), sd_(::SD) {}
  virtual ~SDImpl() = default;

  void Init() {
    if (!sd_.begin(SS, spi_, 80000000)) {
      Serial.println("Error: Failed to mount card.");
      return;
    }
  }

  virtual std::uint64_t GetCapacity() override final { return sd_.cardSize(); }

  virtual std::uint64_t GetAvailable() override final {
    return sd_.totalBytes();
  }

  virtual std::uint64_t GetUsed() override final {
    return GetCapacity() - GetAvailable();
  }

private:
  SPIClass spi_;
  fs::SDFS &sd_;
};
} // namespace

std::unique_ptr<hal::SD> hal::SD::Create() {
  auto sd = std::make_unique<SDImpl>();
  sd->Init();
  return sd;
}
} // namespace hal
} // namespace cdfw

#endif // CDFW_CYD
