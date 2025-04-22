#pragma once

#include <format>

#include <QObject>
#include <QTimer>
#include <QLineEdit>
#include <QSlider>
#include <QString>
#include <QPushButton>

#include <QMessageBox>

#include "geom_model.h"
#include "view.h"
#include "exporter.h"

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
    void HandleStatusReset();

signals:
    void NewMessage(const QString& message);
    void NewError(const QString& message);

private:
    RBTreeINT* tree_;
    QLineEdit* keyEdit_;
};

class TimerController : public QObject {
    Q_OBJECT

public:
    TimerController(QTimer* timer, QPushButton* pauseButton, QObject* parent = nullptr);

public slots:
    void HandleRateChange(int rate, int maxRate);
    void HandlePause(bool push);

private:
    QTimer* timer_;
    QPushButton* pauseButton_;
};

class ViewController : public QObject {
    Q_OBJECT

public:
    ViewController(TreeView* view, QLineEdit* fileNameEdit, QObject* parent = nullptr);

public slots:
    void HandleScaleChange(int scale, float scaleOfScale);
    void HandleViewSave();

signals:
    void NewMessage(const QString& message);
    void NewError(const QString& message);

private:
    TreeView* view_;
    QLineEdit* fileNameEdit_;
};

}  // namespace rbtree
