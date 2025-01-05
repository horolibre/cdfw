// Local Headers
#include "cdfw/core/ui/boot_presenter.h"
#include "cdfw/core/ui/boot_model.h"

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class BootPresenterImpl : public BootPresenter {
public:
  BootPresenterImpl(std::unique_ptr<BootPresenterView> view,
                    std::unique_ptr<BootModel> model)
      : view_(std::move(view)), model_(std::move(model)) {}
  virtual ~BootPresenterImpl() = default;

  virtual void Init() override final {
    // The boot model does not need to be explicitly initialized.
    view_->Init(model_->GetDescription(), model_->GetVersion());
    view_->Show();
  }

private:
  std::unique_ptr<BootPresenterView> view_;
  std::unique_ptr<BootModel> model_;
};
} // namespace

std::unique_ptr<BootPresenter>
BootPresenter::Create(std::unique_ptr<BootPresenterView> view,
                      std::unique_ptr<BootModel> model) {
  return std::make_unique<BootPresenterImpl>(std::move(view), std::move(model));
}
} // namespace ui
} // namespace core
} // namespace cdfw