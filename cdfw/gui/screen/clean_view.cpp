// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/clean_view.h"
#include "cdfw/core/ui/clean_presenter.h"
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
void AddBackButton(lv_obj_t *parent, core::ui::CleanPresenter *presenter) {
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
        auto pres =
            static_cast<core::ui::CleanPresenter *>(lv_event_get_user_data(e));
        pres->OnBackClicked();
      },
      LV_EVENT_PRESSED, presenter);
}

class CleanViewImpl : public CleanView {
public:
  CleanViewImpl() : scr_(nullptr) {}
  virtual ~CleanViewImpl() = default;

  void Init(core::ui::CleanPresenter *presenter) override final {
    scr_ = lv_obj_create(NULL);
    // lv_obj_add_style(scr_, &Styles::GetInstance().style_scr, 0);

    auto win = lv_win_create(scr_);
    {
      lv_obj_set_size(win, lv_disp_get_hor_res(NULL),
                      lv_disp_get_ver_res(NULL));

      auto btn = lv_win_add_button(win, LV_SYMBOL_LEFT, 40);
      lv_obj_add_event_cb(
          btn,
          [](lv_event_t *e) {
            auto pres = static_cast<core::ui::CleanPresenter *>(
                lv_event_get_user_data(e));
            pres->OnBackClicked();
          },
          LV_EVENT_PRESSED, presenter);
      lv_win_add_title(win, "Clean");

      auto header = lv_win_get_header(win);
      lv_obj_set_height(header, 40);
    }
  }

  void Show() override final { lv_scr_load(scr_); }

private:
  lv_obj_t *scr_;
};
} // namespace

std::unique_ptr<core::ui::CleanPresenterView> CleanView::Create() {
  auto view = std::make_unique<CleanViewImpl>();
  return view;
}
} // namespace screen
} // namespace gui
} // namespace cdfw
