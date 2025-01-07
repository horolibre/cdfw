// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/internal/styles.h"

// Third Party Headers
#include <lvgl.h>

namespace cdfw {
namespace gui {
Styles &Styles::GetInstance() {
  static Styles instance;
  return instance;
}

Styles::Styles() {
  lv_style_init(&style1);
  lv_style_set_radius(&style1, 0);
  lv_style_set_bg_opa(&style1, LV_OPA_TRANSP);
  lv_style_set_border_opa(&style1, LV_OPA_TRANSP);
}
} // namespace gui
} // namespace cdfw
