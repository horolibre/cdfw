// Local Headers
#include "cdfw/core/ui/home_presenter.h"
#include "cdfw/core/ui/app_presenter.h"
#include "cdfw/core/ui/home_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class HomePresenterImpl : public HomePresenter {
public:
  HomePresenterImpl(std::unique_ptr<HomePresenterView> view,
                    std::unique_ptr<HomeModel> model)
      : app_presenter_(nullptr), view_(std::move(view)),
        model_(std::move(model)) {}
  virtual ~HomePresenterImpl() = default;

  virtual void Init(AppPresenter *app_presenter) override final {
    // Record the app presenter.
    app_presenter_ = app_presenter;

    // Setup the view.
    view_->Init(this);
    UpdateWifiIcon();
  }

  virtual void Show() override final { view_->Show(); }

  virtual void DelayedShow() override final { view_->DelayedShow(); }

  virtual void UpdateWifiIcon() override final {
    switch (model_->GetWifiState()) {
    case WifiState::CONNECTED:
      view_->SetWifiColor(lv_palette_main(LV_PALETTE_GREEN));
      view_->SetWifiVisible(true);
      break;
    case WifiState::DISABLED_:
      view_->SetWifiVisible(false);
      break;
    default: // Assume Wifi is disconnected.
      view_->SetWifiColor(lv_palette_main(LV_PALETTE_RED));
      view_->SetWifiVisible(true);
      break;
    }
  }

  virtual void OnSettingsClicked() override final {
    app_presenter_->ShowSettings();
  }

private:
  AppPresenter *app_presenter_;
  std::unique_ptr<HomePresenterView> view_;
  std::unique_ptr<HomeModel> model_;
};
} // namespace

std::unique_ptr<HomePresenter>
HomePresenter::Create(std::unique_ptr<HomePresenterView> view,
                      std::unique_ptr<HomeModel> model) {
  return std::make_unique<HomePresenterImpl>(std::move(view), std::move(model));
}
} // namespace ui
} // namespace core
} // namespace cdfw
