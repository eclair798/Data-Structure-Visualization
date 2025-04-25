#pragma once

#include <QObject>
#include <QTimer>

#include <queue>
#include <chrono>

#include "geom_model.h"

namespace rbtree {

class Animator : public QObject {
    Q_OBJECT

public:
    using GTreeObserver = NSLibrary::CColdInput<GTreeConstPtr, NSLibrary::CByValue>;

    Animator(GeomModel* gModel, int startRate, int maxRate, QObject* parent = nullptr);

    GTreeConstPtr PopFrame();

signals:
    void FrameReady();

private slots:
    void OnTimeout();

private:
    void EnqueueFrame(GTreeConstPtr frame);

public:
    std::unique_ptr<QTimer> timer;

private:
    GTreeObserver gteeObserver_;
    std::queue<GTreeConstPtr> frames_;
};

}  // namespace rbtree
