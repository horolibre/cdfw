// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_layout.h"

// C++ Standard Library Headers
#include <filesystem>

namespace cdfw {
namespace stdfs = std::filesystem;

DirLayout::DirLayout(const stdfs::path &mount_dir)
    : app_dir(mount_dir / "horolibre"), routines_dir(app_dir / "routines"),
      data_dir(app_dir / "data") {}

} // namespace cdfw