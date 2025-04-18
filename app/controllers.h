#pragma once

#include "geom_model.h"
#include "animator.h"

#include <QObject>
#include <QLineEdit>
#include <QSlider>

namespace app {

class TreeController : public QObject {
    Q_OBJECT

public:
    TreeController(RBTreeINT* tree, QLineEdit* keyEdit);

private slots:
    void HandleInsert();
    void HandleDelete();
    void HandleFind();
    void HandleReset();

private:
    RBTreeINT* tree_;
    QLineEdit* keyEdit_;
};

class TimerController : public QObject {
    Q_OBJECT

public:
    TimerController(Animator* animator, QSlider* intervalSlider);

private slots:
    void TimerController::HandleTimerChange();

private:
    Animator* animator_;
    QSlider* intervalSlider_;
};

}  // namespace app
