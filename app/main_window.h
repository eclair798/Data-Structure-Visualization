#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

#include <memory>

#include "view.h"

namespace rbtree {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

public:
    std::unique_ptr<TreeView> treeView;

    std::unique_ptr<QLineEdit> keyEdit;
    std::unique_ptr<QPushButton> insertButton;
    std::unique_ptr<QPushButton> deleteButton;
    std::unique_ptr<QPushButton> findButton;
    std::unique_ptr<QPushButton> resetButton;

    std::unique_ptr<QSlider> intervalSlider;
    std::unique_ptr<QSlider> scaleSlider;

    std::unique_ptr<QLabel> messageLabel;
};

}  // namespace rbtree
