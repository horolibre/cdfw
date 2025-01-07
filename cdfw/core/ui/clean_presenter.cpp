// Local Headers
#include "cdfw/core/ui/clean_presenter.h"
#include "cdfw/core/ui/app_presenter.h"
#include "cdfw/core/ui/clean_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class CleanPresenterImpl : public CleanPresenter {
public:
  CleanPresenterImpl(std::unique_ptr<CleanPresenterView> view,
                     std::unique_ptr<CleanModel> model)
      : app_presenter_(nullptr), view_(std::move(view)),
        model_(std::move(model)) {}
  virtual ~CleanPresenterImpl() = default;

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
  std::unique_ptr<CleanPresenterView> view_;
  std::unique_ptr<CleanModel> model_;
};
} // namespace

std::unique_ptr<CleanPresenter>
CleanPresenter::Create(std::unique_ptr<CleanPresenterView> view,
                       std::unique_ptr<CleanModel> model) {
  return std::make_unique<CleanPresenterImpl>(std::move(view),
                                              std::move(model));
}
} // namespace ui
} // namespace core
} // namespace cdfw