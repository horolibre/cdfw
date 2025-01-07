// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/home_view.h"
#include "cdfw/core/ui/home_presenter.h"
#include "cdfw/gui/internal/color.h"
#include "cdfw/gui/internal/styles.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace gui {
namespace screen {
namespace {
int click_cnt = 0;

void wifi_btn_cb(lv_event_t *e) {
  auto view = static_cast<HomeView *>(lv_event_get_user_data(e));
  if (click_cnt == 0) {
    view->SetWifiColor(lv_palette_main(LV_PALETTE_GREEN));
  } else if (click_cnt == 1) {
    view->SetWifiVisible(false);
  } else {
    view->SetWifiVisible(true);
    click_cnt = 0;
  }
  ++click_cnt;
}

void AddNavButton(const lv_style_t &style, lv_obj_t *parent, const char *icon,
                  lv_event_cb_t cb, core::ui::HomePresenter *user_data) {
  lv_obj_t *btn = lv_button_create(parent);
  lv_obj_set_size(btn, 80, 80);
  lv_obj_add_style(btn, &style, 0);

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, icon);
  lv_obj_center(label);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);
  lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, user_data);
}

void AddNavButtons(lv_obj_t *parent, core::ui::HomePresenter *presenter) {
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_radius(&style, 20);

  AddNavButton(
      style, parent, LV_SYMBOL_PLAY,
      [](lv_event_t *e) {
        // TODO
      },
      presenter);
  AddNavButton(
      style, parent, LV_SYMBOL_EDIT,
      [](lv_event_t *e) {
        // TODO
      },
      presenter);
  AddNavButton(
      style, parent, LV_SYMBOL_SETTINGS,
      [](lv_event_t *e) {
        auto pres =
            static_cast<core::ui::HomePresenter *>(lv_event_get_user_data(e));
        pres->OnSettingsClicked();
      },
      presenter);
}

class HomeViewImpl : public HomeView {
public:
  HomeViewImpl() : scr_(nullptr), wifi_btn_(nullptr), wifi_label_(nullptr) {}
  virtual ~HomeViewImpl() = default;

  void Init(core::ui::HomePresenter *presenter) override final {
    scr_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr_, color::DARK_BLUE, LV_PART_MAIN);
    lv_obj_set_style_text_color(scr_, lv_color_white(), LV_PART_MAIN);

    // Add status bar.
    {
      // Top bar object.
      lv_obj_t *tb = lv_obj_create(scr_);
      lv_obj_set_size(tb, 320, 40);
      lv_obj_add_style(tb, &Styles::GetInstance().style1, 0);
      lv_obj_align(tb, LV_ALIGN_TOP_MID, 0, 0);
      // lv_obj_remove_flag(tb, LV_OBJ_FLAG_SCROLLABLE);

      // Title centered in top bar.
      {
        lv_obj_t *label = lv_label_create(scr_);
        lv_label_set_text(label, "HL Cleaner Pro");
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 13);
      }

      // Status icons/buttons on the right.
      {
        // Wifi button.
        wifi_btn_ = lv_button_create(scr_);

        lv_obj_set_size(wifi_btn_, 40, 40);
        lv_obj_set_pos(wifi_btn_, 280, 0);
        lv_obj_add_style(wifi_btn_, &Styles::GetInstance().style1, 0);

        wifi_label_ = lv_label_create(wifi_btn_);
        lv_label_set_text(wifi_label_, LV_SYMBOL_WIFI);
        lv_obj_center(wifi_label_);
        lv_obj_set_style_text_color(
            wifi_label_, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);

        lv_obj_add_event_cb(wifi_btn_, wifi_btn_cb, LV_EVENT_CLICKED, this);
      }
    }

    // Add nav button panel.
    {
      lv_obj_t *panel = lv_obj_create(scr_);
      lv_obj_set_size(panel, 320, 200);
      lv_obj_add_style(panel, &Styles::GetInstance().style1, 0);
      lv_obj_set_style_bg_color(panel, color::MED_BLUE, LV_PART_MAIN);
      lv_obj_align(panel, LV_ALIGN_BOTTOM_MID, 0, 0);
      lv_obj_set_layout(panel, LV_LAYOUT_FLEX);
      lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
      lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_SPACE_EVENLY,
                            LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

      AddNavButtons(panel, presenter);
    }
  }

  void Show() override final { lv_scr_load(scr_); }

  void SetWifiColor(const lv_color_t &color) override final {
    lv_obj_set_style_text_color(wifi_label_, color, LV_PART_MAIN);
  }

  void SetWifiVisible(bool visible) override final {
    if (visible) {
      lv_obj_remove_flag(wifi_btn_, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_add_flag(wifi_btn_, LV_OBJ_FLAG_HIDDEN);
    }
  }

  void DelayedShow() override final {
    // Queue timed animation to show the home screen.
    lv_screen_load_anim(scr_, LV_SCR_LOAD_ANIM_FADE_IN, /*time*/ 200,
                        /*delay*/ 1500,
                        /*auto_del*/ true);
  }

private:
  lv_obj_t *scr_;
  lv_obj_t *wifi_btn_;
  lv_obj_t *wifi_label_;
};
} // namespace

std::unique_ptr<core::ui::HomePresenterView> HomeView::Create() {
  auto view = std::make_unique<HomeViewImpl>();
  return view;
}
} // namespace screen
} // namespace gui
} // namespace cdfw
