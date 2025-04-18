#include "main_window.h"

namespace app {

MainWindow::MainWindow() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // Поле для ввода
    keyEdit_ = new QLineEdit(this);

    // Кнопки
    insertButton_ = new QPushButton("Insert", this);
    deleteButton_ = new QPushButton("Delete", this);
    findButton_ = new QPushButton("Find", this);
    resetButton_ = new QPushButton("Reset", this);

    // Ползунок таймера
    intervalSlider_ = new QSlider(Qt::Horizontal, this);
    intervalSlider_->setRange(10, 1000);
    intervalSlider_->setValue(100);

    intervalLabel_ = new QLabel("Animation speed", this);

    layout->addWidget(keyEdit_);
    layout->addWidget(insertButton_);
    layout->addWidget(deleteButton_);
    layout->addWidget(findButton_);
    layout->addWidget(resetButton_);
    layout->addWidget(intervalLabel_);
    layout->addWidget(intervalSlider_);

    setCentralWidget(centralWidget);
}

}  // namespace app
