#pragma once

#include <QObject>
#include <QTimer>

#include <queue>
#include <chrono>

#include "geom_model.h"

namespace rbtree {

class Animator : public QObject {
    Q_OBJECT

    struct Interval {
        int from;
        int to;
    };

public:
    using GTreeObserver = NSLibrary::CHotInput<GTreeConst, NSLibrary::CByValue>;

    Animator(QObject* parent = nullptr);

    void SubscribeFrame(GeomModel* gModel);

    GTreeConst PopFrame();

    QTimer* getTimerPtr();

signals:
    void FrameReady();

private slots:
    void OnTimeout();

private:
    void EnqueueFrame(GTreeConst frame);

public:
    static constexpr const int kStartRate = 1000;
    static constexpr const Interval kRateRange = {0, 1500};

private:
    QTimer timer_;

    GTreeObserver gtreePort_;
    std::queue<GTreeConst> frames_;
};

}  // namespace rbtree
