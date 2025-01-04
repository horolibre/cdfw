// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/boot.h"
#include "cdfw/core/version.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdio>
#include <memory>

namespace cdfw {
namespace gui {
namespace screen {
namespace {
class BootViewImpl : public BootView {
public:
  BootViewImpl() : scr_(nullptr) {}
  virtual ~BootViewImpl() = default;

  void Init() {
    // We use the default screen for the boot screen.
    scr_ = lv_screen_active();
    lv_obj_set_style_bg_color(scr_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_color(scr_, lv_color_hex(0x003a57), LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(scr_);
    lv_label_set_text(label, "HOROLIBRE Cleaner");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label2 = lv_label_create(scr_);
    char str_buf[8];
    std::sprintf(str_buf, "v%s", CDFW_VERSION);
    lv_label_set_text(label2, str_buf);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 16);
  }

  void Show() { lv_scr_load(scr_); }

private:
  lv_obj_t *scr_;
};
} // namespace

void BootView::Register() {
  auto view = std::make_unique<BootViewImpl>();
  view->Init();
  view->Show();
}
} // namespace screen
} // namespace gui
} // namespace cdfw
