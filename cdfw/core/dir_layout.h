// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_DIR_LAYOUT_H
#define CDFW_CORE_DIR_LAYOUT_H

// C++ Standard Library Headers
#include <filesystem>
#include <memory>

namespace cdfw {
namespace stdfs = std::filesystem;

struct DirLayout {
  const stdfs::path app_dir;
  const stdfs::path routines_dir;
  const stdfs::path data_dir;

  DirLayout(const stdfs::path &mount_dir);
};

class DirLayoutValidator {
public:
  // Factory method.
  static std::unique_ptr<DirLayoutValidator> Create();

  // Virtual destructor.
  virtual ~DirLayoutValidator() = default;

  // Validates the given directory layout.
  virtual bool Validate(const DirLayout &dir_layout) = 0;
};
} // namespace cdfw

#endif // CDFW_CORE_DIR_LAYOUT_H
