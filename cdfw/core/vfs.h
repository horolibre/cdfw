// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_VFS_H
#define CDFW_CORE_VFS_H

// C++ Standard Library Headers
#include <cstdint>
#include <filesystem>
#include <memory>

namespace cdfw {
namespace vfs {
namespace stdfs = std::filesystem;

class Volume {
public:
  // Volume is not meant to be instantiated directly, instead you should
  // instantiate a derived class (e.g., SD). This factory method exists to allow
  // for us to inject a mock volume for testing.
  static std::unique_ptr<Volume> Create(Volume *volume);
  virtual ~Volume() = default;

  virtual bool IsSD() = 0;

  virtual std::uint64_t Capacity() = 0;
  virtual std::uint64_t Available() = 0;
  virtual std::uint64_t Used() = 0;

  virtual stdfs::path MountPoint() = 0;

  void Walk();
  void PrintInfo();
};
} // namespace vfs
} // namespace cdfw

#endif // CDFW_CORE_VFS_H
