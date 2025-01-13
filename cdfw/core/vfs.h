// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_VFS_H
#define CDFW_CORE_VFS_H

// C++ Standard Library Headers
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <type_traits>

namespace cdfw {
namespace vfs {
namespace stdfs = std::filesystem;

class Volume {
public:
  // Volume is not meant to be instantiated directly, instead you should
  // instantiate a derived class (e.g., SD). This factory method exists to allow
  // for us to inject a mock volume for testing.
  static std::unique_ptr<Volume> Create(Volume *volume);
  virtual ~Volume() = default;

  virtual bool IsSD() = 0;

  virtual std::uint64_t Capacity() = 0;
  virtual std::uint64_t Available() = 0;
  virtual std::uint64_t Used() = 0;

  virtual stdfs::path MountPoint() = 0;

  void Walk();
  void PrintInfo();
};

// Thin wrapper around std::filesystem::path to provide an interface for mocks.
class Path {
public:
  typedef char value_type;
  static constexpr value_type preferred_separator = '/';

  // constructors and destructor
  Path() noexcept {}
  Path(const Path &p) : p_(p.p_) {}
  Path(Path &&p) noexcept : p_(std::move(p.p_)) {}
  Path(std::string &&s) noexcept : p_(std::move(s)) {}
  Path(const std::string &s) : p_(s) {}
  Path(const char *s) : p_(s) {}
  Path(const stdfs::path &p) : p_(p) {}
  Path(stdfs::path &&p) noexcept : p_(std::move(p)) {}
  ~Path() = default;

  // append
  Path &operator/=(const Path &p) {
    p_ /= p.p_;
    return *this;
  }

  // modifiers
  friend Path operator/(const Path &lhs, const Path &rhs) {
    Path result(lhs);
    result /= rhs;
    return result;
  }

  // comparators
  friend bool operator==(const Path &lhs, const Path &rhs) noexcept {
    return lhs.p_ == rhs.p_;
  }

  // native format
  const value_type *c_str() const noexcept { return p_.c_str(); }
  const std::string &native() const noexcept { return p_.native(); }
  operator std::string() const { return p_.native(); }

  // query
  // bool is_absolute() const { return p_.is_absolute(); }
  // bool is_relative() const { return p_.is_relative(); }
  bool Exists() const;

private:
  stdfs::path p_;
};
} // namespace vfs
} // namespace cdfw

#endif // CDFW_CORE_VFS_H
