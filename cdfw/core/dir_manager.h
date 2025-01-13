// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_DIR_MANAGER_H
#define CDFW_CORE_DIR_MANAGER_H

// Local Headers
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace stdfs = std::filesystem;

// Forward declarations.
class DirLayoutValidator;
class DirWriter;

class DirManager {
public:
  // Constructors.
  DirManager();
  DirManager(std::unique_ptr<DirLayoutValidator> validator,
             std::shared_ptr<DirWriter> writer);

  // Virtual destructor.
  virtual ~DirManager() = default;

  // Creates the app directories if they do not exist.
  void CreateDirs(const vfs::Path &mount_dir);

private:
  std::unique_ptr<DirLayoutValidator> validator_;
  std::shared_ptr<DirWriter> writer_;
};
} // namespace cdfw

#endif // CDFW_CORE_DIR_MANAGER_H
