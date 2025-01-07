// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/settings_view.h"
#include "cdfw/core/ui/settings_presenter.h"
#include "cdfw/core/wifi.h"
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
void back_btn_cb(lv_event_t *e) {
  // TODO
}

void AddBackButton(lv_obj_t *parent, core::ui::SettingsPresenter *presenter) {
  lv_obj_t *btn = lv_button_create(parent);
  lv_obj_set_size(btn, 40, 40);
  lv_obj_set_pos(btn, 0, 0);
  lv_obj_add_style(btn, &Styles::GetInstance().style1, 0);

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, LV_SYMBOL_LEFT);
  lv_obj_center(label);

  lv_obj_add_event_cb(
      btn,
      [](lv_event_t *e) {
        auto pres = static_cast<core::ui::SettingsPresenter *>(
            lv_event_get_user_data(e));
        pres->OnBackClicked();
      },
      LV_EVENT_CLICKED, presenter);
}

class SettingsViewImpl : public SettingsView {
public:
  SettingsViewImpl() : scr_(nullptr) {}
  virtual ~SettingsViewImpl() = default;

  void Init(core::ui::SettingsPresenter *presenter) override final {
    scr_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr_, color::DARK_BLUE, LV_PART_MAIN);
    lv_obj_set_style_text_color(scr_, lv_color_white(), LV_PART_MAIN);

    // Add nav bar.
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
        lv_label_set_text(label, "Settings");
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 13);
      }

      AddBackButton(scr_, presenter);
    }

    // Add wifi settings panel.
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
    }
  }

  void Show() override final { lv_scr_load(scr_); }

  virtual void SetWifiEnabled(bool enabled) override final {
    // TODO
  }

  virtual void
  SetWifiCredentials(const core::WifiCredentials &credentials) override final {
    // TODO
  }

  virtual void SetWifiStatus(const String &status) override final {
    // TODO
  }

private:
  lv_obj_t *scr_;
};
} // namespace

std::unique_ptr<core::ui::SettingsPresenterView> SettingsView::Create() {
  auto view = std::make_unique<SettingsViewImpl>();
  return view;
}
} // namespace screen
} // namespace gui
} // namespace cdfw
