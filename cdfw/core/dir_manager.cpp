// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_manager.h"
#include "cdfw/core/dir_layout.h"
#include "cdfw/core/dir_writer.h"
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
DirManager::DirManager(std::shared_ptr<vfs::Volume> volume)
    : DirManager(volume, DirLayoutValidator::Create(), DirWriter::Create()) {}

DirManager::DirManager(std::shared_ptr<vfs::Volume> volume,
                       std::unique_ptr<DirLayoutValidator> validator,
                       std::shared_ptr<DirWriter> writer)
    : volume_(volume), validator_(std::move(validator)), writer_(writer) {}

void DirManager::CreateDirs(const vfs::Path &mount_dir) {
  auto layout = DirLayout(mount_dir);
  if (!validator_->Validate(*volume_, layout)) {
    writer_->Write(*volume_, layout);
  }
}
} // namespace cdfw
