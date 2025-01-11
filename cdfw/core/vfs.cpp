// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/vfs.h"
#include "cdfw/compat/arduino.h"

// C++ Standard Library Headers
#include <cstdint>
#include <filesystem>
#include <memory>

namespace cdfw {
namespace vfs {
namespace {
namespace stdfs = std::filesystem;

void WalkImpl(stdfs::path p, std::string indent = "") {
  if (indent.empty()) {
    // Show the top-level directory as absolute.
    Serial.printf("%s%s/\n", indent.c_str(), p.c_str());
    indent = "└── ";
  } else {
    // Otherwise, show the directory as relative.
    Serial.printf("%s%s/\n", indent.c_str(), p.filename().c_str());
    indent = "    " + indent;
  }

  for (const auto &entry : stdfs::directory_iterator(p)) {
    if (entry.is_directory()) {
      WalkImpl(entry.path(), indent);
    } else {
      Serial.printf("%s%s (%d bytes)\n", indent.c_str(), entry.path().c_str(),
                    entry.file_size());
    }
  }
}

class VolumeImpl : public Volume {
public:
  VolumeImpl(Volume *volume) : v_(volume) {}
  virtual ~VolumeImpl() = default;

  virtual bool IsSD() override final { return v_->IsSD(); }

  virtual std::uint64_t Capacity() override final { return v_->Capacity(); }

  virtual std::uint64_t Available() override final { return v_->Available(); }

  virtual std::uint64_t Used() override final { return v_->Used(); }

  virtual stdfs::path MountPoint() override final { return v_->MountPoint(); }

private:
  Volume *v_;
};
} // namespace

std::unique_ptr<Volume> Volume::Create(Volume *volume) {
  return std::make_unique<VolumeImpl>(volume);
}

void Volume::Walk() {
  Serial.println("Walking SD card...");
  WalkImpl(MountPoint());
  Serial.println("Done walking SD card.");
}

void Volume::PrintInfo() {
  Serial.printf("SD capacity: %llu bytes\n", Capacity());
  Serial.printf("SD available: %llu bytes\n", Available());
  Serial.printf("SD used: %llu bytes\n", Used());
  Serial.printf("SD mountpoint: %s\n", MountPoint().string().c_str());
}

} // namespace vfs
} // namespace cdfw