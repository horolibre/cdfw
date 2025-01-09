// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/internal/styles.h"
#include "cdfw/gui/internal/color.h"

// Third Party Headers
#include <lvgl.h>

namespace cdfw {
namespace gui {
Styles &Styles::GetInstance() {
  static Styles instance;
  return instance;
}

Styles::Styles() {
  lv_style_init(&style_scr);
  lv_style_set_radius(&style_scr, 0);
  lv_style_set_border_opa(&style_scr, LV_OPA_TRANSP);
  lv_style_set_bg_color(&style_scr, color::MED_BLUE);
  lv_style_set_text_color(&style_scr, lv_color_white());

  lv_style_init(&style_top_bar);
  lv_style_set_radius(&style_top_bar, 0);
  lv_style_set_border_opa(&style_top_bar, LV_OPA_TRANSP);
  lv_style_set_bg_color(&style_top_bar, color::DARK_BLUE);

  lv_style_init(&style1);
  lv_style_set_radius(&style1, 0);
  lv_style_set_bg_opa(&style1, LV_OPA_TRANSP);
  lv_style_set_border_opa(&style1, LV_OPA_TRANSP);
}
} // namespace gui
} // namespace cdfw
