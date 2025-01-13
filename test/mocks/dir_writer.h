// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_TEST_MOCKS_DIR_WRITER_H
#define CDFW_TEST_MOCKS_DIR_WRITER_H

// Local Headers
#include "cdfw/core/dir_writer.h"
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <memory>
#include <vector>

namespace cdfw {
class MockDirWriterStrategy : public DirWriterStrategy {
public:
  std::vector<vfs::Path> paths;

  MockDirWriterStrategy() = default;
  ~MockDirWriterStrategy() = default;

  virtual void Write(vfs::Volume &volume,
                     const vfs::Path &path) override final {
    paths.push_back(path);
  }
};
} // namespace cdfw

#endif // CDFW_TEST_MOCKS_DIR_WRITER_H
