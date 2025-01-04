// Local Headers
#include "cdfw/core/ui/boot_presenter.h"
#include "cdfw/core/ui/boot_model.h"

// Third Party Headers
// #include <Arduino.h>

// C++ Standard Library Headers
#include <memory>

namespace cdfw {
namespace core {
namespace ui {
namespace {
class BootPresenterImpl : public BootPresenter {
public:
  // BootPresenterImpl() : view_(nullptr), model_(nullptr) {}
  BootPresenterImpl() : view_(nullptr) {}
  virtual ~BootPresenterImpl() = default;

  virtual void SetView(std::unique_ptr<BootPresenterView> view) override final {
    view_ = std::move(view);
  }

  virtual void SetModel(std::unique_ptr<BootModel> model) override final {
    model_ = std::move(model);
  }

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

std::unique_ptr<BootPresenter> BootPresenter::Create() {
  return std::make_unique<BootPresenterImpl>();
}
} // namespace ui
} // namespace core
} // namespace cdfw