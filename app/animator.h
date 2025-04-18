#pragma once

#include <QObject>
#include <QTimer>
#include <queue>
#include <chrono>

#include "observer.h"
#include "geom_model.h"

namespace app {

class Animator : public QObject {
    Q_OBJECT

public:
    using GTreeObserver = NSLibrary::CColdInput<GTreeConstPtr, NSLibrary::CByValue>;

    Animator(GeomModel* gModel);

signals:
    void frameReady();

private slots:

    void onTimeout();

private:
    void enqueueFrame(GTreeConstPtr frame);

    GTreeConstPtr PopFrame();

private:
    GTreeObserver observer_;

    QTimer timer_;

    std::chrono::milliseconds timer_interval{100};

    std::queue<GTreeConstPtr> frames_;
};

}  // namespace app
