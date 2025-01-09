// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_GUI_INTERNAL_STYLES_H
#define CDFW_GUI_INTERNAL_STYLES_H

// Third Party Headers
#include <lvgl.h>

namespace cdfw {
namespace gui {
// Singleton holding the GUI styles.
struct Styles {
  // Screen style.
  lv_style_t style_scr;

  // Top bar style.
  lv_style_t style_top_bar;

  // Transparent background.
  lv_style_t style1;

  // Returns the static singleton instance.
  static Styles &GetInstance();

private:
  // Initializes the styles.
  Styles();
};
} // namespace gui
} // namespace cdfw

#endif // CDFW_GUI_INTERNAL_STYLES_H
