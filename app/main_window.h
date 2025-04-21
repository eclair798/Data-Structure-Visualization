#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QScrollArea>

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

    std::unique_ptr<QSlider> rateSlider;
    std::unique_ptr<QSlider> scaleSlider;

    std::unique_ptr<QLabel> messageLabel;

public:
    static const QString kInsertStr;
    static const QString kDeleteStr;
    static const QString kFindStr;
    static const QString kResetStr;

    static const QString kRateComment;
    static constexpr const std::pair<int, int> kRateRange = {0, 1500};
    static constexpr const int kStartRate = 1000;

    static const QString kScaleComment;
    static constexpr const std::pair<int, int> kScaleRange = {50, 300};
    static constexpr const int kStartScale = 10;
    static constexpr const float kScaleRangeScale = 100;

    static constexpr const int kRightPanelWidth = 200;
    static constexpr const std::pair<int, int> kWindowShape = {800, 400};

    static const QString kStartMessage;

    static constexpr const int kContentMargins = 8;
};

}  // namespace rbtree
