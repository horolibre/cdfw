// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_NATIVE

// Local Headers
#include "cdfw/compat/arduino.h"
#include "cdfw/core/vfs.h"
#include "cdfw/hal/sd.h"

// C++ Standard Library Headers
#include <filesystem>
#include <iostream>
#include <memory>

namespace cdfw {
namespace hal {
namespace {
namespace stdfs = std::filesystem;

class SDImpl : public hal::SD {
public:
  SDImpl() = default;
  virtual ~SDImpl() = default;

  void Init() {
    mp_dir_ = stdfs::temp_directory_path() / CDFW_SD_VOLUME_NAME;
    stdfs::create_directories(mp_dir_);
  }

  virtual std::uint64_t Capacity() override final {
    return stdfs::space(mp_dir_).capacity;
  }

  virtual std::uint64_t Available() override final {
    return stdfs::space(mp_dir_).available;
  }

  virtual std::uint64_t Used() override final {
    return Capacity() - Available();
  }

  virtual vfs::Path MountPoint() override final { return mp_dir_.string(); }

  virtual vfs::Path TempDir() override final { return MountPoint() / "tmp"; }

private:
  stdfs::path mp_dir_;
};
} // namespace

std::unique_ptr<hal::SD> hal::SD::Create() {
  auto sd = std::make_unique<SDImpl>();
  sd->Init();
  return sd;
}
} // namespace hal
} // namespace cdfw

#endif // CDFW_NATIVE
