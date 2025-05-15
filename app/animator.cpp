#include "animator.h"

namespace rbtree {

Animator::Animator(QObject* parent)
    : gtreePort_([this](GTreeConst frame) { EnqueueFrame(frame); }), timer_(this), QObject(parent) {
    connect(&timer_, &QTimer::timeout, this, &Animator::OnTimeout);

    timer_.setSingleShot(false);
    std::chrono::milliseconds msc(kRateRange.to - kStartRate);
    timer_.setInterval(msc);
    timer_.start();
}

void Animator::SubscribeFrame(GeomModel* gModel) {
    gModel->SubscribeFrame(&gtreePort_);
}

GTreeConst Animator::PopFrame() {
    assert(!frames_.empty() && "Error in Animator: pop from empty queue");
    GTreeConst frame = frames_.front();
    frames_.pop();
    return frame;
}

QTimer* Animator::getTimerPtr() {
    return &timer_;
}

void Animator::OnTimeout() {
    if (!frames_.empty()) {
        emit FrameReady();
    }
}

void Animator::EnqueueFrame(GTreeConst frame) {
    frames_.push(frame);
}

}  // namespace rbtree
