#include "main_window.h"

namespace rbtree {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    treeView = std::make_unique<TreeView>(this);

    // Поле для ввода
    keyEdit = std::make_unique<QLineEdit>(new QLineEdit(this));

    // Кнопки
    insertButton = std::make_unique<QPushButton>(new QPushButton("Insert", this));
    deleteButton = std::make_unique<QPushButton>(new QPushButton("Delete", this));
    findButton = std::make_unique<QPushButton>(new QPushButton("Find", this));
    resetButton = std::make_unique<QPushButton>(new QPushButton("Reset", this));

    // Ползунок таймера
    intervalSlider = std::make_unique<QSlider>(new QSlider(Qt::Horizontal, this));
    intervalSlider->setRange(10, 1000);
    intervalSlider->setValue(500);

    messageLabel = std::make_unique<QLabel>(new QLabel("Hello! Create your Red Black Tree!", this));

    intervalLabel = std::make_unique<QLabel>(new QLabel("Time between frames", this));

    layout->addWidget(keyEdit.get());
    layout->addWidget(insertButton.get());
    layout->addWidget(deleteButton.get());
    layout->addWidget(findButton.get());
    layout->addWidget(resetButton.get());

    layout->addWidget(messageLabel.get());

    layout->addWidget(intervalLabel.get());
    layout->addWidget(intervalSlider.get());

    setCentralWidget(centralWidget);

    // todo разобраться с деталями отрисовки
}

}  // namespace rbtree
