#include "application.h"

namespace rbtree {

Application::Application(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

    qApp_ = std::make_unique<QApplication>(argc, argv);
    window_ = std::make_unique<MainWindow>();  // создается вьюха

    tree_ = std::make_unique<RBTreeINT>();
    geomModel_ = std::make_unique<GeomModel>(tree_.get());

    animator_ =
        std::make_unique<Animator>(geomModel_.get(), window_.get());  // внутри заводится таймер

    treeController_ =
        std::make_unique<TreeController>(tree_.get(), window_->keyEdit.get(), window_.get());
    timerController_ = std::make_unique<TimerController>(animator_->timer_.get(), window_.get());

    SetupConnections();
}

void Application::SetupConnections() {
    // шаблон connect(sender, &SenderType::signalName, receiver, &ReceiverType::slotName);
    // или connect(sender, &SenderType::signalName, [](){} );

    // connect Аниматора с вьюхой
    QObject::connect(animator_.get(), &Animator::frameReady,
                     [this]() { window_->treeView->ShowFrame(animator_->PopFrame()); });

    // connect Кнопок с контроллером
    QObject::connect(window_->insertButton.get(), &QPushButton::clicked, treeController_.get(),
                     &TreeController::HandleInsert);
    QObject::connect(window_->deleteButton.get(), &QPushButton::clicked, treeController_.get(),
                     &TreeController::HandleDelete);
    QObject::connect(window_->findButton.get(), &QPushButton::clicked, treeController_.get(),
                     &TreeController::HandleFind);
    QObject::connect(window_->resetButton.get(), &QPushButton::clicked, treeController_.get(),
                     &TreeController::HandleReset);

    // connect Ползунка таймера с контроллером
    QObject::connect(window_->intervalSlider.get(), &QSlider::valueChanged, timerController_.get(),
                     &TimerController::HandleTimerChange);

    // connect Ползунка масштабирования с вьюхой
    QObject::connect(window_->scaleSlider.get(), &QSlider::valueChanged, window_->treeView.get(),
                     &TreeView::HandleScaleChange);

    // connect Контроллера с сообщением для пользователя
    QObject::connect(treeController_.get(), &TreeController::NewMessage,
                     window_->messageLabel.get(), &QLabel::setText);
}

int Application::Run() {
    window_->show();
    return qApp_->exec();
    // todo ?
}

}  // namespace rbtree
