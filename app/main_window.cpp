#include "main_window.h"

namespace rbtree {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    treeView = std::make_unique<TreeView>(this);

    mainLayout->addWidget(treeView.get(), 3);

    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    // Поле для ввода
    keyEdit = std::make_unique<QLineEdit>(this);

    // Кнопки
    insertButton = std::make_unique<QPushButton>("Insert", this);
    deleteButton = std::make_unique<QPushButton>("Delete", this);
    findButton = std::make_unique<QPushButton>("Find", this);
    resetButton = std::make_unique<QPushButton>("Reset", this);

    rightLayout->addWidget(keyEdit.get());
    rightLayout->addWidget(insertButton.get());
    rightLayout->addWidget(deleteButton.get());
    rightLayout->addWidget(findButton.get());
    rightLayout->addWidget(resetButton.get());

    // Ползунок таймера
    intervalSlider = std::make_unique<QSlider>(Qt::Horizontal, this);
    intervalSlider->setRange(1, 1000);
    intervalSlider->setValue(500);

    QLabel* intervalLabel = new QLabel("Time between frames:", this);

    QWidget* intervalWidget = new QWidget(this);
    QVBoxLayout* intervalGroupLayout = new QVBoxLayout(intervalWidget);
    intervalGroupLayout->setContentsMargins(0, 0, 0, 0);
    intervalGroupLayout->addWidget(intervalLabel);
    intervalGroupLayout->addWidget(intervalSlider.get());
    intervalWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLayout->addWidget(intervalWidget);

    // Ползунок масштабирования
    scaleSlider = std::make_unique<QSlider>(Qt::Horizontal, this);
    scaleSlider->setRange(5, 30);
    scaleSlider->setValue(10);

    QLabel* scaleLabel = new QLabel("Picture scaling:", this);

    QWidget* scaleWidget = new QWidget(this);
    QVBoxLayout* scaleGroupLayout = new QVBoxLayout(scaleWidget);
    scaleGroupLayout->setContentsMargins(0, 0, 0, 0);
    scaleGroupLayout->addWidget(scaleLabel);
    scaleGroupLayout->addWidget(scaleSlider.get());
    scaleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLayout->addWidget(scaleWidget);

    // Окошко с сообщением
    messageLabel = std::make_unique<QLabel>("Hello! Create your Red Black Tree!", this);
    messageLabel->setWordWrap(true);

    QFrame* messageFrame = new QFrame(this);
    QVBoxLayout* frameLayout = new QVBoxLayout(messageFrame);
    frameLayout->addWidget(messageLabel.get());
    frameLayout->setContentsMargins(8, 8, 8, 8);

    messageFrame->setFrameShape(QFrame::StyledPanel);
    messageFrame->setFrameShadow(QFrame::Raised);
    messageFrame->setLineWidth(2);

    rightLayout->addWidget(messageFrame);

    // Вся панель настроек
    rightPanel->setFixedWidth(200);
    mainLayout->addWidget(rightPanel);

    resize(500, 400);
}

}  // namespace rbtree
