// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_layout.h"
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace {
class DirLayoutValidatorImpl : public DirLayoutValidator {
public:
  DirLayoutValidatorImpl() = default;
  virtual ~DirLayoutValidatorImpl() = default;

  bool Validate(const vfs::Volume &volume,
                const DirLayout &dir_layout) override final {
    return volume.Exists(dir_layout.app_dir) &&
           volume.Exists(dir_layout.routines_dir) &&
           volume.Exists(dir_layout.data_dir);
  }
};
} // namespace

DirLayout::DirLayout(const vfs::Path &mount_dir)
    : app_dir(mount_dir / "horolibre"), routines_dir(app_dir / "routines"),
      data_dir(app_dir / "data") {}

std::unique_ptr<DirLayoutValidator> DirLayoutValidator::Create() {
  return std::make_unique<DirLayoutValidatorImpl>();
}

} // namespace cdfw