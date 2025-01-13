// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_TEST_MOCKS_VFS_H
#define CDFW_TEST_MOCKS_VFS_H

// Local Headers
#include "cdfw/core/vfs.h"

// C++ Standard Library Headers
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <memory>
#include <set>
#include <string>

namespace cdfw {
namespace vfs {
namespace stdfs = std::filesystem;

class MockPath : public Path {
public:
  MockPath() noexcept {}
  // Path(const Path &p) : p_(p.p_) {}
  // Path(Path &&p) noexcept : p_(std::move(p.p_)) {}
  // MockPath(std::string &&s) noexcept : p_(std::move(s)) {}
  // Path(const std::string &s) : p_(s) {}
  MockPath(const char *s) : Path(s) {}
  // Path(const stdfs::path &p) : p_(p) {}
  // Path(stdfs::path &&p) noexcept : p_(std::move(p)) {}
  virtual ~MockPath() = default;

  // query
  stdfs::path GetPath() { return p_; }
};

class MockVolume : public Volume {
public:
  struct Data {
    bool is_sd;
    std::uint64_t capacity;
    std::uint64_t used;
    MockPath mount_point;
    std::set<vfs::Path> paths;

    Data() { Reset(); }

    void Reset() {
      is_sd = false;
      capacity = 0;
      used = 0;
      mount_point = MockPath("/mp");
      paths.clear();
      paths.insert(
          mount_point.native()); // Volume mount point is always present.
    }
  };
  Data &data;

  MockVolume(Data &data) : data(data) {}
  virtual ~MockVolume() = default;

  virtual bool IsSD() override final { return data.is_sd; }

  virtual std::uint64_t Capacity() override final { return data.capacity; }
  virtual std::uint64_t Available() override final {
    return Capacity() - Used();
  }
  virtual std::uint64_t Used() override final { return data.used; }

  virtual vfs::Path MountPoint() override final { return data.mount_point; }
  virtual vfs::Path TempDir() override final {
    return data.mount_point / "tmp";
  }
  virtual bool Exists(const vfs::Path &path) const override final {
    for (const auto &p : data.paths) {
      if (p == path) {
        return true;
      }
    }
    return false;
  }

  virtual bool CreateDirs(const vfs::Path &path) override final {
    auto p = stdfs::path(path.native());
    // Starting at the child, walk up the tree to the root.
    auto root = p.root_path();
    while (p != root) {
      data.paths.insert(p);
      p = p.parent_path();
    }
    return true;
  }

  virtual bool Remove(const vfs::Path &path) override final {
    // Reverse iterate through the data.paths set so that children are
    // encountered first. If the requested path has children, do not remove.
    for (auto it = data.paths.rbegin(), end = data.paths.rend(); it != end;
         ++it) {
      if (*it == path) {
        data.paths.erase(--(it.base()));
        return true;
      } else if (it->native().find(path.native()) == 0) {
        return false;
      }
    }

    return false;
  }
  virtual bool RemoveAll(const vfs::Path &path) override final {
    // Loop through the data.paths set; any entry that starts with the given
    // path should be removed from the set.
    for (auto it = data.paths.begin(), end = data.paths.end(); it != end;) {
      if (it->native().find(path.native()) == 0) {
        it = data.paths.erase(it);
      } else {
        ++it;
      }
    }
    return true;
  }
};
} // namespace vfs
} // namespace cdfw

#endif // CDFW_TEST_MOCKS_VFS_H
