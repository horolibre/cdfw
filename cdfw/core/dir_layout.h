// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_DIR_LAYOUT_H
#define CDFW_CORE_DIR_LAYOUT_H

// Local Headers
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
struct DirLayout {
  const vfs::Path app_dir;
  const vfs::Path routines_dir;
  const vfs::Path data_dir;

  DirLayout(const vfs::Path &mount_dir);
};

class DirLayoutValidator {
public:
  // Factory method.
  static std::unique_ptr<DirLayoutValidator> Create();

  // Virtual destructor.
  virtual ~DirLayoutValidator() = default;

  // Validates the given directory layout.
  virtual bool Validate(const vfs::Volume &volume,
                        const DirLayout &dir_layout) = 0;
};
} // namespace cdfw

#endif // CDFW_CORE_DIR_LAYOUT_H
