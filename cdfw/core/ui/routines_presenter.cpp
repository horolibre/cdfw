// Local Headers
#include "cdfw/core/ui/routines_presenter.h"
#include "cdfw/core/ui/app_presenter.h"
#include "cdfw/core/ui/routines_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class RoutinesPresenterImpl : public RoutinesPresenter {
public:
  RoutinesPresenterImpl(std::unique_ptr<RoutinesPresenterView> view,
                        std::unique_ptr<RoutinesModel> model)
      : app_presenter_(nullptr), view_(std::move(view)),
        model_(std::move(model)) {}
  virtual ~RoutinesPresenterImpl() = default;

  virtual void Init(AppPresenter *app_presenter) override final {
    // Record the app presenter.
    app_presenter_ = app_presenter;

    // Setup the view.
    view_->Init(this);
  }

  virtual void Show() override final { view_->Show(); }

  virtual void OnBackClicked() override final { app_presenter_->ShowHome(); }

private:
  AppPresenter *app_presenter_;
  std::unique_ptr<RoutinesPresenterView> view_;
  std::unique_ptr<RoutinesModel> model_;
};
} // namespace

std::unique_ptr<RoutinesPresenter>
RoutinesPresenter::Create(std::unique_ptr<RoutinesPresenterView> view,
                          std::unique_ptr<RoutinesModel> model) {
  return std::make_unique<RoutinesPresenterImpl>(std::move(view),
                                                 std::move(model));
}
} // namespace ui
} // namespace core
} // namespace cdfw