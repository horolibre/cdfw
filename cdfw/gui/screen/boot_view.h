// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_GUI_SCREEN_BOOT_VIEW_H
#define CDFW_GUI_SCREEN_BOOT_VIEW_H

namespace cdfw {
namespace gui {
namespace screen {
class BootView {
public:
  // Factory method.
  static void Register();

  // Virtual d'tor.
  virtual ~BootView() = default;
};
} // namespace screen
} // namespace gui
} // namespace cdfw

#endif // CDFW_GUI_SCREEN_BOOT_VIEW_H
