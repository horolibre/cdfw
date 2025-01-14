// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/gui/screen/settings_view.h"
#include "cdfw/core/ui/settings_presenter.h"
#include "cdfw/core/version.h"
#include "cdfw/core/wifi.h"
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
  core::ui::SettingsPresenter *presenter;
};

void BackEventHandler(lv_event_t *e) {
  auto obj = static_cast<lv_obj_t *>(lv_event_get_target(e));
  auto payload = static_cast<BackEventPayload *>(lv_event_get_user_data(e));

  if (lv_menu_back_button_is_root(payload->menu, obj)) {
    payload->presenter->OnBackClicked();
  }
}

void AddMenuSeparator(lv_obj_t *obj) {
  for (int i = 0; i < 1; i++) {
    lv_menu_separator_create(obj);
  }
}

lv_style_t *GetLineStyle(lv_obj_t *obj) {
  static lv_style_t style_line;
  lv_style_init(&style_line);
  lv_style_set_line_width(&style_line, 1);
  lv_style_set_line_color(
      &style_line, lv_color_darken(lv_obj_get_style_bg_color(obj, 0), 30));
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

class SettingsViewImpl : public SettingsView {
public:
  SettingsViewImpl() : scr_(nullptr) {}
  virtual ~SettingsViewImpl() = default;

  void Init(core::ui::SettingsPresenter *presenter) override final {
    scr_ = lv_obj_create(NULL);
    // lv_obj_add_style(scr_, &Styles::GetInstance().style_scr, 0);

    // Initialize base menu object.
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
      // lv_obj_add_style(header, &Styles::GetInstance().style_top_bar, 0);
      // lv_obj_set_style_bg_color(header, color::DARK_BLUE, 0);
      // lv_obj_set_style_bg_opa(header, LV_OPA_COVER, 0);
      // We can let the header self-size by commenting out the line below.
      // lv_obj_set_size(header, lv_display_get_horizontal_resolution(NULL),
      // 40); lv_obj_set_style_text_align(header, LV_TEXT_ALIGN_CENTER, 0);
      lv_obj_set_flex_align(header, LV_FLEX_ALIGN_SPACE_BETWEEN,
                            LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
      // debug: show header border
      // lv_obj_set_style_border_opa(header, LV_OPA_COVER, 0);
      // lv_obj_set_style_border_width(header, 1, 0);
      // lv_obj_set_style_border_color(header, lv_color_white(), 0);

      auto back_btn = lv_menu_get_main_header_back_button(menu);
      lv_obj_set_size(back_btn, 40, 40);
      lv_obj_set_flex_align(back_btn, LV_FLEX_ALIGN_CENTER,
                            LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
      static BackEventPayload payload = {menu, presenter};
      lv_obj_add_event_cb(menu, BackEventHandler, LV_EVENT_CLICKED, &payload);
      // debug: show back_btn border
      // lv_obj_set_style_border_opa(back_btn, LV_OPA_COVER, 0);
      // lv_obj_set_style_border_width(back_btn, 1, 0);
      // lv_obj_set_style_border_color(back_btn, lv_color_white(), 0);

      // Sole purpose of this object is to balance the back_btn so that the
      // title is centered.
      auto header_balance_obj = lv_obj_create(header);
      lv_obj_set_style_bg_opa(header_balance_obj, LV_OPA_TRANSP, 0);
      lv_obj_set_style_border_opa(header_balance_obj, LV_OPA_TRANSP, 0);
      lv_obj_set_size(header_balance_obj, 40, 40);
    }

    // Now we work through the sub-pages.

    // Setup Wi-Fi sub page.
    auto sub_page_wifi = lv_menu_page_create(menu, "Wi-Fi");
    {
      lv_obj_set_style_pad_hor(
          sub_page_wifi,
          lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

      AddMenuSeparator(sub_page_wifi);
      auto section = lv_menu_section_create(sub_page_wifi);
      {
        // Menu item for enabling/disabling Wi-Fi.
        auto cont = lv_menu_cont_create(section);
        auto img = lv_image_create(cont);
        lv_image_set_src(img, LV_SYMBOL_WIFI);
        auto label = lv_label_create(cont);
        lv_label_set_text(label, "Wi-Fi");
        lv_obj_set_flex_grow(label, 1);
        auto toggle = lv_switch_create(cont);
        lv_obj_add_state(toggle, LV_STATE_CHECKED);
        lv_obj_add_event_cb(
            toggle,
            [](lv_event_t *e) {
              lv_event_code_t code = lv_event_get_code(e);
              auto obj = static_cast<lv_obj_t *>(lv_event_get_target(e));
              if (code == LV_EVENT_PRESSED) {
                auto pres = static_cast<core::ui::SettingsPresenter *>(
                    lv_event_get_user_data(e));
                pres->OnWifiEnabled(!lv_obj_has_state(obj, LV_STATE_CHECKED));
              }
            },
            LV_EVENT_PRESSED, presenter);
      }

      AddMenuSeparator(sub_page_wifi);
      section = lv_menu_section_create(sub_page_wifi);
      {
        // Menu item for connecting to a Wi-Fi network.
        // TODO: Currently this is just a switch for playing with GUI event
        // propagation, but otherwise the switch does nothing. Real
        // implementation interfacing with business logic that uses the WiFi
        // library will be added later.
        // BUG: Set WiFi enabled, connect, disable, re-enable. WiFi icon is red
        // (disconnected) despite WiFi being enabled and connected.
        auto cont = lv_menu_cont_create(section);
        auto label = lv_label_create(cont);
        lv_label_set_text(label, "Connect");
        lv_obj_set_flex_grow(label, 1);
        auto toggle = lv_switch_create(cont);
        lv_obj_add_event_cb(
            toggle,
            [](lv_event_t *e) {
              lv_event_code_t code = lv_event_get_code(e);
              auto obj = static_cast<lv_obj_t *>(lv_event_get_target(e));
              if (code == LV_EVENT_PRESSED) {
                auto pres = static_cast<core::ui::SettingsPresenter *>(
                    lv_event_get_user_data(e));
                pres->OnWifiConnectRequest(
                    !lv_obj_has_state(obj, LV_STATE_CHECKED));
              }
            },
            LV_EVENT_PRESSED, presenter);
      }
    }

    // Setup Display sub page.
    auto sub_page_display = lv_menu_page_create(menu, "Display");
    {
      lv_obj_set_style_pad_hor(
          sub_page_display,
          lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

      AddMenuSeparator(sub_page_wifi);
      auto section = lv_menu_section_create(sub_page_display);
      {
        // Menu item for enabling/disabling auto brightness.
        // TODO: Implement functionality.
        auto cont = lv_menu_cont_create(section);
        auto img = lv_image_create(cont);
        // TODO: Find a better icon (e.g., sun).
        lv_image_set_src(img, LV_SYMBOL_CHARGE);
        auto label = lv_label_create(cont);
        lv_label_set_text(label, "Auto adjust brightness");
        lv_obj_set_flex_grow(label, 1);
        auto toggle = lv_switch_create(cont);
        lv_obj_add_state(toggle, LV_STATE_CHECKED);
      }
    }

    // Setup About sub page.
    auto sub_page_about = lv_menu_page_create(menu, "About");
    {
      // Software Information sub page.
      auto sub_page_software_info =
          lv_menu_page_create(menu, "Software Information");
      {
        lv_obj_set_style_pad_hor(
            sub_page_software_info,
            lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

        AddMenuSeparator(sub_page_software_info);
        auto section = lv_menu_section_create(sub_page_software_info);

        // Software info menu item.
        auto cont = lv_menu_cont_create(section);
        auto label = lv_label_create(cont);
        // TODO: Should we get version from a model like the boot view? If not,
        // then why are we doing it in the boot view?
        std::uint8_t buf_size = 8;
        char str_buf[buf_size];
        std::snprintf(str_buf, buf_size, "v%s", CDFW_VERSION);
        lv_label_set_text(label, str_buf);
      }

      // License Information sub page.
      auto sub_page_license_info =
          lv_menu_page_create(menu, "License Information");
      {
        lv_obj_set_style_pad_hor(
            sub_page_license_info,
            lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

        AddMenuSeparator(sub_page_license_info);
        auto section = lv_menu_section_create(sub_page_license_info);

        // License info menu item.
        auto cont = lv_menu_cont_create(section);
        auto label = lv_label_create(cont);
        lv_label_set_text(label, "GNU General Public License (GPL) v3.0\n"
                                 "Copyright (c) 2025 Ian Dinwoodie");
      }

      // Organize the About sub page.
      lv_obj_set_style_pad_hor(
          sub_page_about,
          lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
      AddMenuSeparator(sub_page_about);
      auto section = lv_menu_section_create(sub_page_about);
      {
        // Software Information menu item.
        auto cont = lv_menu_cont_create(section);
        auto label = lv_label_create(cont);
        lv_label_set_text(label, "Software Information");
        lv_menu_set_load_page_event(menu, cont, sub_page_software_info);

        AddLine(section);

        // License Information menu item.
        cont = lv_menu_cont_create(section);
        label = lv_label_create(cont);
        lv_label_set_text(label, "License Information");
        lv_menu_set_load_page_event(menu, cont, sub_page_license_info);
      }
    }

    // Initialize main menu page.
    auto main_page = lv_menu_page_create(menu, "Settings");
    {
      lv_obj_set_style_pad_hor(
          main_page,
          lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
      // lv_obj_set_style_bg_color(sub_page_wifi, lv_color_hex(0x4D5B74),
      // LV_PART_MAIN | LV_STATE_DEFAULT);

      AddMenuSeparator(main_page);
      auto section = lv_menu_section_create(main_page);
      {
        // Wi-Fi menu item.
        auto cont = lv_menu_cont_create(section);
        auto img = lv_image_create(cont);
        lv_image_set_src(img, LV_SYMBOL_WIFI);
        auto label = lv_label_create(cont);
        lv_label_set_text(label, "Wi-Fi");
        lv_menu_set_load_page_event(menu, cont, sub_page_wifi);

        // Display menu item.
        cont = lv_menu_cont_create(section);
        img = lv_image_create(cont);
        // TODO: Find a better icon (e.g., monitor).
        lv_image_set_src(img, LV_SYMBOL_IMAGE);
      }

      AddMenuSeparator(main_page);
      section = lv_menu_section_create(main_page);
      {
        // About menu item.
        auto cont = lv_menu_cont_create(section);
        auto label = lv_label_create(cont);
        lv_label_set_text(label, "About");
        lv_menu_set_load_page_event(menu, cont, sub_page_about);
      }

      // Set the initial menu page.
      lv_menu_set_page(menu, main_page);
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

  virtual void SetWifiStatus(const std::string &status) override final {
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
