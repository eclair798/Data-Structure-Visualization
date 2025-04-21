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

    std::unique_ptr<QSlider> timerSlider;
    std::unique_ptr<QSlider> scaleSlider;

    std::unique_ptr<QLabel> messageLabel;

private:
    static const QString kInsertStr;
    static const QString kDeleteStr;
    static const QString kFindStr;
    static const QString kResetStr;

    static const QString kTimerComment;
    static constexpr const std::pair<int, int> kTimerRange = {10, 2000};
    static constexpr const int kStartTimer = 500;

    static const QString kScaleComment;
    static constexpr const std::pair<int, int> kScaleRange = {5, 30};
    static constexpr const int kStartScale = 10;

    static constexpr const int kRightPanelWidth = 200;
    static constexpr const std::pair<int, int> kWindowShape = {500, 400};

    static const QString kStartMessage;

    static constexpr const int kContentMargins = 8;
};

}  // namespace rbtree
