// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_manager.h"
#include "cdfw/core/dir_layout.h"
#include "cdfw/core/dir_writer.h"

// C++ Standard Library Headers
#include <filesystem>
#include <memory>

namespace cdfw {
namespace stdfs = std::filesystem;
DirManager::DirManager()
    : DirManager(DirLayoutValidator::Create(), DirWriter::Create()) {}

DirManager::DirManager(std::unique_ptr<DirLayoutValidator> validator,
                       std::shared_ptr<DirWriter> writer)
    : validator_(std::move(validator)), writer_(writer) {}

void DirManager::CreateDirs(const stdfs::path &mount_dir) {
  auto layout = DirLayout(mount_dir);
  if (!validator_->Validate(layout)) {
    writer_->Write(layout);
  }
}
} // namespace cdfw
