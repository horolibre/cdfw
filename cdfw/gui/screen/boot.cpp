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

namespace cdfw {
namespace gui {
namespace screen {
namespace boot {
void Register() {
  // Not registering the screen with the screen manager as it is a one-off.

  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xffffff),
                            LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0x003a57),
                              LV_PART_MAIN);

  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "HOROLIBRE Cleaner");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *label2 = lv_label_create(lv_screen_active());
  char str_buf[8];
  std::sprintf(str_buf, "v%s", CDFW_VERSION);
  lv_label_set_text(label2, str_buf);
  lv_obj_align(label2, LV_ALIGN_CENTER, 0, 16);
}
} // namespace boot
} // namespace screen
} // namespace gui
} // namespace cdfw
