// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifdef CDFW_NATIVE

// Local Headers
#include "cdfw/hal/sd.h"

// C++ Standard Library Headers
#include <filesystem>
#include <memory>

namespace cdfw {
namespace hal {
namespace {
class SDImpl : public hal::SD {
public:
  SDImpl() = default;
  virtual ~SDImpl() = default;

  void Init() { tmp_dir_ = std::filesystem::temp_directory_path(); }

  virtual std::uint64_t GetCapacity() override final {
    return std::filesystem::space(tmp_dir_).capacity;
  }

  virtual std::uint64_t GetAvailable() override final {
    return std::filesystem::space(tmp_dir_).available;
  }

  virtual std::uint64_t GetUsed() override final {
    return GetCapacity() - GetAvailable();
  }

private:
  std::filesystem::path tmp_dir_;
};
} // namespace

std::unique_ptr<hal::SD> hal::SD::Create() {
  auto sd = std::make_unique<SDImpl>();
  sd->Init();
  return sd;
}
} // namespace hal
} // namespace cdfw

#endif // CDFW_NATIVE
