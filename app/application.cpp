#include "application.h"

namespace rbtree {

Application::Application()
    : geomModel_(),
      animator_(&window_),
      treeController_(&tree_, &window_.keyEdit, &window_),
      timerController_(animator_.getTimerPtr(), &window_.pauseButton, &window_),
      viewController_(&window_.treeView, &window_.fileNameEdit, &window_) {
    SetupConnections();
    window_.show();
}

void Application::SetupConnections() {
    geomModel_.SubscribeTree(&tree_);
    animator_.SubscribeFrame(&geomModel_);

    // шаблон connect(sender, &SenderType::signalName, receiver, &ReceiverType::slotName);
    // или connect(sender, &SenderType::signalName, [](){} );

    // connect Аниматора с вьюхой
    QObject::connect(&animator_, &Animator::FrameReady,
                     [this]() { window_.treeView.ShowFrame(animator_.PopFrame()); });

    // connect Кнопок с контроллером
    QObject::connect(&window_.insertButton, &QPushButton::clicked, &treeController_,
                     &TreeController::HandleInsert);
    QObject::connect(&window_.deleteButton, &QPushButton::clicked, &treeController_,
                     &TreeController::HandleDelete);
    QObject::connect(&window_.findButton, &QPushButton::clicked, &treeController_,
                     &TreeController::HandleFind);
    QObject::connect(&window_.resetButton, &QPushButton::clicked, &treeController_,
                     &TreeController::HandleReset);
    QObject::connect(&window_.statusResetButton, &QPushButton::clicked, &treeController_,
                     &TreeController::HandleStatusReset);

    QObject::connect(&window_.viewSaveButton, &QPushButton::clicked, &viewController_,
                     &ViewController::HandleViewSave);

    // connect Ползунка скорости с контроллером
    QObject::connect(&window_.rateSlider, &QSlider::valueChanged, [this](int rate) {
        timerController_.HandleRateChange(rate, Animator::kRateRange.to);
    });

    QObject::connect(&window_.pauseButton, &QPushButton::toggled, &timerController_,
                     &TimerController::HandlePause);

    // connect Ползунка масштабирования с контроллером
    QObject::connect(&window_.scaleSlider, &QSlider::valueChanged, &viewController_,
                     &ViewController::HandleScaleChange);

    // connect Контроллера с сообщением для пользователя
    QObject::connect(&treeController_, &TreeController::NewMessage, [this](const QString& message) {
        window_.messageLabel.setStyleSheet("");
        window_.messageLabel.setText(message);
    });

    QObject::connect(&viewController_, &ViewController::NewMessage, [this](const QString& message) {
        window_.messageLabel.setStyleSheet("");
        window_.messageLabel.setText(message);
    });

    // connect Контроллера с сообщением об ошибке
    QObject::connect(&treeController_, &TreeController::NewError, [this](const QString& error) {
        window_.messageLabel.setStyleSheet("color: red;");
        window_.messageLabel.setText(error);
    });

    QObject::connect(&viewController_, &ViewController::NewError, [this](const QString& error) {
        window_.messageLabel.setStyleSheet("color: red;");
        window_.messageLabel.setText(error);
    });
}

}  // namespace rbtree
