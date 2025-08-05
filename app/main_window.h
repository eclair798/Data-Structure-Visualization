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

#include "animator.h"
#include "view.h"

namespace rbtree {

class MainWindow : public QMainWindow {
    Q_OBJECT

    struct HalvesProportion {
        int left;
        int right;
    };

    struct Shape {
        int w;
        int h;
    };

public:
    MainWindow(QWidget* parent = nullptr);

    TreeView treeView;

    QLineEdit keyEdit;
    QPushButton insertButton;
    QPushButton deleteButton;
    QPushButton findButton;
    QPushButton resetButton;
    QPushButton statusResetButton;

    QSlider rateSlider;

    QPushButton pauseButton;

    QSlider scaleSlider;

    QLabel messageLabel;

    QLineEdit fileNameEdit;
    QPushButton viewSaveButton;

private:
    static const QString kWindowTitle;

    static const QString kStartStyleSheet;

    static const QString kInsertStr;
    static const QString kDeleteStr;
    static const QString kFindStr;
    static const QString kResetStr;
    static const QString kStatusResetStr;
    static const QString kViewSaveStr;
    static const QString kPauseStr;

    static const QString kRateComment;

    static const QString kScaleComment;

    static constexpr const HalvesProportion kHalvesProportion = {1, 0};
    static constexpr const int kRightPanelWidth = 200;
    static constexpr const Shape kWindowShape = {1000, 650};

    static const QString kStartMessage;

    static constexpr const int kContentMargins = 8;
};

}  // namespace rbtree
