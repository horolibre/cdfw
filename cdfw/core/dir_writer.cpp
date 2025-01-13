// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_writer.h"
#include "cdfw/core/dir_layout.h"
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <filesystem>
#include <memory>

namespace cdfw {
namespace {
namespace stdfs = std::filesystem;

class DirWriterStrategyImpl : public DirWriterStrategy {
public:
  DirWriterStrategyImpl() = default;
  ~DirWriterStrategyImpl() = default;

  void Write(const vfs::Path &path) override final {
    stdfs::create_directories(path.native());
  }
};

class DirWriterImpl : public DirWriter {
public:
  DirWriterImpl(std::shared_ptr<DirWriterStrategy> strategy)
      : strategy_(strategy) {}
  ~DirWriterImpl() = default;

  void Write(const DirLayout &dir_layout) override final {
    strategy_->Write(dir_layout.app_dir);
    strategy_->Write(dir_layout.routines_dir);
    strategy_->Write(dir_layout.data_dir);
  }

private:
  std::shared_ptr<DirWriterStrategy> strategy_;
};

} // namespace

std::shared_ptr<DirWriterStrategy> DirWriterStrategy::Create() {
  return std::make_shared<DirWriterStrategyImpl>();
}

std::shared_ptr<DirWriter>
DirWriter::Create(std::shared_ptr<DirWriterStrategy> strategy) {
  return std::make_shared<DirWriterImpl>(strategy);
}

std::shared_ptr<DirWriter> DirWriter::Create() {
  return std::make_shared<DirWriterImpl>(DirWriterStrategy::Create());
}
} // namespace cdfw