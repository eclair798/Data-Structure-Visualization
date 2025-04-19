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

    // Ползунок таймера
    intervalSlider = std::make_unique<QSlider>(Qt::Horizontal, this);
    intervalSlider->setRange(10, 1000);
    intervalSlider->setValue(500);

    messageLabel = std::make_unique<QLabel>("Hello! Create your Red Black Tree!", this);

    intervalLabel = std::make_unique<QLabel>("Time between frames:", this);

    rightLayout->addWidget(keyEdit.get());
    rightLayout->addWidget(insertButton.get());
    rightLayout->addWidget(deleteButton.get());
    rightLayout->addWidget(findButton.get());
    rightLayout->addWidget(resetButton.get());

    rightLayout->addWidget(messageLabel.get());

    rightLayout->addWidget(intervalLabel.get());
    rightLayout->addWidget(intervalSlider.get());

    rightLayout->setSpacing(10);
    rightLayout->setContentsMargins(10, 10, 10, 10);

    mainLayout->addWidget(rightPanel, 1);

    // todo разобраться с деталями отрисовки
}

}  // namespace rbtree
