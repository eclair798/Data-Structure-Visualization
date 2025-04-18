#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

#include "controllers.h"
#include "view.h"
#include "animator.h"
#include "geom_model.h"

namespace app {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

public:
    QLineEdit* keyEdit_;
    QPushButton* insertButton_;
    QPushButton* deleteButton_;
    QPushButton* findButton_;
    QPushButton* resetButton_;

    QSlider* intervalSlider_;
    QLabel* intervalLabel_;
};

}  // namespace app
