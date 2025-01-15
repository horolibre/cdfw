// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/routines_view.h"
#include "cdfw/core/ui/routines_presenter.h"
#include "cdfw/gui/internal/color.h"
#include "cdfw/gui/internal/styles.h"

// Third Party Headers
#include <lvgl.h>

// C++ Standard Library Headers
#include <memory>
#include <string>

namespace cdfw {
namespace gui {
namespace screen {
namespace {
struct BackEventPayload {
  lv_obj_t *menu;
  core::ui::RoutinesPresenter *presenter;
};

void BackEventHandler(lv_event_t *e) {
  auto obj = static_cast<lv_obj_t *>(lv_event_get_target(e));
  auto payload = static_cast<BackEventPayload *>(lv_event_get_user_data(e));

  if (lv_menu_back_button_is_root(payload->menu, obj)) {
    payload->presenter->OnBackClicked();
  }
}

lv_style_t *GetLineStyle(lv_obj_t *obj) {
  static lv_style_t style_line;
  lv_style_init(&style_line);
  lv_style_set_line_width(&style_line, 1);
  lv_style_set_line_color(
      &style_line, lv_color_darken(lv_obj_get_style_bg_color(obj, 0), 15));
  lv_style_set_line_rounded(&style_line, true);
  return &style_line;
}

void AddLine(lv_obj_t *obj) {
  static lv_point_precise_t line_points[] = {{10, 0}, {295, 0}};
  static lv_style_t *style_line = GetLineStyle(obj);

  auto line = lv_line_create(obj);
  lv_line_set_points(line, line_points, 2); /*Set the points*/
  lv_obj_add_style(line, style_line, 0);
  lv_obj_center(line);
}

class RoutinesViewImpl : public RoutinesView {
public:
  RoutinesViewImpl() : scr_(nullptr) {}
  virtual ~RoutinesViewImpl() = default;

  void Init(core::ui::RoutinesPresenter *presenter) override final {
    scr_ = lv_obj_create(NULL);
    // lv_obj_add_style(scr_, &Styles::GetInstance().style_scr, 0);

    // Initialize base menu object. Routines are presented as a menu.
    auto menu = lv_menu_create(scr_);
    {
      lv_obj_set_size(menu, lv_display_get_horizontal_resolution(NULL),
                      lv_display_get_vertical_resolution(NULL));
      lv_obj_center(menu);
      lv_menu_set_mode_root_back_button(menu, LV_MENU_ROOT_BACK_BUTTON_ENABLED);
      lv_menu_set_mode_header(menu, LV_MENU_HEADER_TOP_FIXED);
      // lv_obj_set_style_bg_color(menu, color::MED_BLUE, 0);
      lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
      if (lv_color_brightness(bg_color) > 127) {
        lv_obj_set_style_bg_color(
            menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 15), 0);
      } else {
        lv_obj_set_style_bg_color(
            menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 50), 0);
      }

      auto header = lv_menu_get_main_header(menu);
      lv_obj_set_flex_align(header, LV_FLEX_ALIGN_SPACE_BETWEEN,
                            LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

      auto back_btn = lv_menu_get_main_header_back_button(menu);
      lv_obj_set_size(back_btn, 40, 40);
      lv_obj_set_flex_align(back_btn, LV_FLEX_ALIGN_CENTER,
                            LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
      static BackEventPayload payload = {menu, presenter};
      lv_obj_add_event_cb(menu, BackEventHandler, LV_EVENT_CLICKED, &payload);

      // Sole purpose of this object is to balance the back_btn so that the
      // title is centered.
      auto header_balance_obj = lv_obj_create(header);
      lv_obj_set_style_bg_opa(header_balance_obj, LV_OPA_TRANSP, 0);
      lv_obj_set_style_border_opa(header_balance_obj, LV_OPA_TRANSP, 0);
      lv_obj_set_size(header_balance_obj, 40, 40);
    }

    // Initialize main menu page.
    auto main_page = lv_menu_page_create(menu, "Routines");
    lv_menu_separator_create(main_page);
    auto routines_section = lv_menu_section_create(main_page);
    {
      lv_obj_set_style_pad_hor(
          main_page,
          lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
      // Set the initial menu page.
      lv_menu_set_page(menu, main_page);
    }

    // For each routine, create a sub-page and add a corresponding menu item to
    // the main page.
    std::string routines[] = {"Routine A", "Routine B", "Routine C",
                              "Routine D", "Routine E"};
    bool first_routine = true;
    for (auto &routine : routines) {
      if (!first_routine) {
        AddLine(routines_section);
      } else {
        first_routine = false;
      }

      auto sub_page = lv_menu_page_create(menu, routine.c_str());
      {
        lv_obj_set_style_pad_hor(
            sub_page,
            lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

        lv_menu_separator_create(sub_page);
        auto section = lv_menu_section_create(sub_page);
        auto label = lv_label_create(section);
        lv_label_set_text(label, "TODO");

        // Add menu item to main page.
        auto cont = lv_menu_cont_create(routines_section);
        label = lv_label_create(cont);
        lv_label_set_text(label, routine.c_str());
        lv_obj_set_flex_grow(label, 1);
        label = lv_label_create(cont);
        lv_label_set_text(label, LV_SYMBOL_RIGHT);
        lv_obj_set_style_text_color(
            label,
            lv_color_darken(lv_obj_get_style_bg_color(routines_section, 0), 50),
            0);

        lv_menu_set_load_page_event(menu, cont, sub_page);
      }
    }
  }

  void Show() override final { lv_scr_load(scr_); }

private:
  lv_obj_t *scr_;
};
} // namespace

std::unique_ptr<core::ui::RoutinesPresenterView> RoutinesView::Create() {
  auto view = std::make_unique<RoutinesViewImpl>();
  return view;
}
} // namespace screen
} // namespace gui
} // namespace cdfw
