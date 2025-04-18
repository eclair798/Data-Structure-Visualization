#include "animator.h"

namespace app {

void Animator::onTimeout() {
    if (!frames_.empty()) {
        emit frameReady();
    }
}

Animator::Animator(GeomModel* gModel)
    : observer_([this](GTreeConstPtr frame) { this->enqueueFrame(frame); }) {
    gModel->SubscribeFrame(&observer_);

    connect(&timer_, &QTimer::timeout, this, &Animator::onTimeout);

    timer_.setSingleShot(false);
    timer_.setInterval(timer_interval);
    timer_.start();
}

void Animator::enqueueFrame(GTreeConstPtr frame) {
    frames_.push(frame);
}

GTreeConstPtr Animator::PopFrame() {
    GTreeConstPtr frame = frames_.front();
    frames_.pop();
    return frame;
}

}  // namespace app
