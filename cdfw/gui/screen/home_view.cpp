// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/home_view.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <cstdint>

namespace cdfw {
namespace gui {
namespace screen {
namespace {
static void btn_event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *btn = static_cast<lv_obj_t *>(lv_event_get_target(e));
  if (code == LV_EVENT_CLICKED) {
    static uint8_t cnt = 0;
    cnt++;

    /*Get the first child of the button which is the label and change its text*/
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "Button: %d", cnt);
  }
}

class HomeViewImpl : public HomeView {
public:
  HomeViewImpl() : scr_(nullptr) {}
  virtual ~HomeViewImpl() = default;

  void Init() {
    scr_ = lv_obj_create(NULL);
    lv_obj_t *btn = lv_button_create(scr_);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);
  }

  void Show() override final { lv_scr_load(scr_); }

  void SetWifiIcon(const char *icon) override final {}

  void DelayedShow() override final {
    // Queue timed animation to show the home screen.
    lv_screen_load_anim(scr_, LV_SCR_LOAD_ANIM_FADE_OUT, /*time*/ 200,
                        /*delay*/ 1500,
                        /*auto_del*/ true);
  }

private:
  lv_obj_t *scr_;
};
} // namespace

std::unique_ptr<HomeView> HomeView::Register() {
  auto view = std::make_unique<HomeViewImpl>();
  view->Init();
  return view;
}
} // namespace screen
} // namespace gui
} // namespace cdfw
