#pragma once

#include <QObject>
#include <QTimer>
#include <QLineEdit>
#include <QSlider>

#include "geom_model.h"

namespace rbtree {

class TreeController : public QObject {
    Q_OBJECT

public:
    TreeController(RBTreeINT* tree, QLineEdit* keyEdit, QObject* parent = nullptr);

public slots:
    void HandleInsert();
    void HandleDelete();
    void HandleFind();
    void HandleReset();

signals:
    void NewMessage(const QString& message);

private:
    RBTreeINT* tree_;
    QLineEdit* keyEdit_;
};

class TimerController : public QObject {
    Q_OBJECT

public:
    TimerController(QTimer* timer, QObject* parent = nullptr);

public slots:
    void HandleTimerChange(int val);

private:
    QTimer* timer_;
};

}  // namespace rbtree
