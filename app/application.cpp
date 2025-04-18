#include "application.h"

namespace app {

Application::Application() {
    window_ = std::make_unique<MainWindow>();

    tree_ = std::make_unique<RBTreeINT>();
    geomModel_ = std::make_unique<GeomModel>(tree_.get());

    animator_ = std::make_unique<Animator>(geomModel_.get());
    treeView_ = std::make_unique<TreeView>();

    tree_controller_ = std::make_unique<TreeController>(tree_.get(), window_->keyEdit_);
    timer_controller_ =
        std::make_unique<TimerController>(animator_.get(), window_->intervalSlider_);

    SetupConnections();
}

void Application::SetupConnections() {
    // шаблон connect(sender, &SenderType::signalName, receiver, &ReceiverType::slotName);
    // todo: кнопки и ползунки с контроллерами, аниматор с вьюхой
}

void Application::Run() {
}

}  // namespace app
