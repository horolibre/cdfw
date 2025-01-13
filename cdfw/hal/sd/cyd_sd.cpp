// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_CYD

// Local Headers
#include "cdfw/compat/arduino.h"
#include "cdfw/core/vfs.h"
#include "cdfw/hal/sd.h"

// Third Party Headers
#include <FS.h>
#include <SD.h>
#include <SPI.h>

// C++ Standard Library Headers
#include <filesystem>
#include <iostream>
#include <memory>

#define TO_MOUNT_POINT "/" CDFW_SD_VOLUME_NAME

namespace cdfw {
namespace hal {
namespace {
namespace ardfs = ::fs;
namespace stdfs = std::filesystem;

class SDImpl : public hal::SD {
public:
  SDImpl() : spi_(SPIClass(VSPI)), sd_(::SD) {}
  virtual ~SDImpl() { sd_.end(); }

  void Init() {
    if (!sd_.begin(SS, spi_, 80000000, TO_MOUNT_POINT)) {
      Serial.println("Error: Failed to mount card.");
      return;
    }
  }

  virtual std::uint64_t Capacity() override final {
    std::cout << "Capacity: " << sd_.cardSize() << std::endl;
    return sd_.cardSize();
  }
  virtual std::uint64_t Available() override final {
    std::cout << "Available: " << sd_.totalBytes() << std::endl;
    return sd_.totalBytes();
  }
  virtual std::uint64_t Used() override final {
    return Capacity() - Available();
  }
  virtual vfs::Path MountPoint() override final { return sd_.mountpoint(); }
  virtual vfs::Path TempDir() override final { return MountPoint() / "tmp"; }
  virtual bool Exists(const vfs::Path &path) const override final {
    return stdfs::exists(path.native());
  }

  virtual bool CreateDirs(const vfs::Path &path) override final {
    return stdfs::create_directories(path.native());
  }
  virtual bool Remove(const vfs::Path &path) override final {
    return stdfs::remove(path.native());
  }
  virtual bool RemoveAll(const vfs::Path &path) override final {
    WalkWithCB(path.native(), [](stdfs::path p) { stdfs::remove(p); });
    return Remove(path);
  }

private:
  SPIClass spi_;
  ardfs::SDFS &sd_;

  void WalkWithCB(stdfs::path p, std::function<void(stdfs::path)> cb) {
    for (const auto &entry : stdfs::directory_iterator(p)) {
      if (entry.is_directory()) {
        WalkWithCB(entry.path(), cb);
      } else {
        cb(entry.path());
      }
      cb(entry.path());
    }
  }
};
} // namespace

std::unique_ptr<hal::SD> hal::SD::Create() {
  auto sd = std::make_unique<SDImpl>();
  sd->Init();
  return sd;
}

std::shared_ptr<vfs::Volume> hal::SD::CreateVolume() {
  return vfs::Volume::Create(hal::SD::Create());
}
} // namespace hal
} // namespace cdfw

#endif // CDFW_CYD
