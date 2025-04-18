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

    Animator(GeomModel* gModel, QObject* parent = nullptr);

    GTreeConstPtr PopFrame();

signals:
    void frameReady();

private slots:

    void onTimeout();

private:
    void enqueueFrame(GTreeConstPtr frame);

public:
    GTreeObserver observer_;
    std::unique_ptr<QTimer> timer_;

    static constexpr const std::chrono::milliseconds startTimerInterval{500};

private:
    std::queue<GTreeConstPtr> frames_;
};

}  // namespace rbtree
