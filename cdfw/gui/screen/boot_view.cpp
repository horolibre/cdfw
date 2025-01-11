// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/boot_view.h"
#include "cdfw/core/ui/boot_presenter.h"
#include "cdfw/core/version.h"
#include "cdfw/gui/internal/color.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>

namespace cdfw {
namespace gui {
namespace screen {
namespace {
class BootViewImpl : public BootView {
public:
  BootViewImpl() : desc_lbl_(nullptr), ver_lbl_(nullptr) {}
  virtual ~BootViewImpl() = default;

  virtual void Init() override final {
    // We use the default screen for the boot screen.
    auto scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, color::DARK_BLUE, LV_PART_MAIN);
    lv_obj_set_style_text_color(scr, lv_color_white(), LV_PART_MAIN);

    desc_lbl_ = lv_label_create(scr);
    lv_obj_align(desc_lbl_, LV_ALIGN_CENTER, 0, 0);

    ver_lbl_ = lv_label_create(scr);
    lv_obj_align(ver_lbl_, LV_ALIGN_CENTER, 0, 16);
  }

  virtual void SetDescription(const std::string &desc) override final {
    lv_label_set_text(desc_lbl_, desc.c_str());
  }

  virtual void SetVersion(const std::string &version) override final {
    std::uint8_t buf_size = 8;
    char str_buf[buf_size];
    std::snprintf(str_buf, buf_size, "v%s", version.c_str());
    lv_label_set_text(ver_lbl_, str_buf);
  }

private:
  lv_obj_t *desc_lbl_;
  lv_obj_t *ver_lbl_;
};
} // namespace

std::unique_ptr<core::ui::BootPresenterView> BootView::Create() {
  auto view = std::make_unique<BootViewImpl>();
  return view;
}
} // namespace screen
} // namespace gui
} // namespace cdfw
