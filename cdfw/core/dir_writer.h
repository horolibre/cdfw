// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_DIR_WRITER_H
#define CDFW_CORE_DIR_WRITER_H

// Local Headers
#include "cdfw/core/dir_layout.h"
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
class DirWriterStrategy {
public:
  // Factory method.
  static std::shared_ptr<DirWriterStrategy> Create();

  // Virtual destructor.
  virtual ~DirWriterStrategy() = default;

  // Creates a directory at the given path.
  virtual void Write(vfs::Volume &volume, const vfs::Path &path) = 0;
};

class DirWriter {
public:
  // Factory method.
  static std::shared_ptr<DirWriter>
  Create(std::shared_ptr<DirWriterStrategy> strategy);
  static std::shared_ptr<DirWriter> Create();

  // Virtual destructor.
  virtual ~DirWriter() = default;

  // Writes the directories corresponding to the given layout.
  virtual void Write(vfs::Volume &volume, const DirLayout &dir_layout) = 0;
};
} // namespace cdfw

#endif // CDFW_CORE_DIR_WRITER_H
