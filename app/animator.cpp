#include "animator.h"

namespace rbtree {

void Animator::OnTimeout() {
    if (!frames_.empty()) {
        emit FrameReady();
    }
}

Animator::Animator(GeomModel* gModel, int startRate, int maxRate, QObject* parent)
    : gteeObserver_([this](GTreeConstPtr frame) { this->EnqueueFrame(frame); }), QObject(parent) {
    gModel->SubscribeFrame(&gteeObserver_);

    EnqueueFrame(gModel->GetCurrentFrame());

    timer = std::make_unique<QTimer>(this);

    connect(timer.get(), &QTimer::timeout, this, &Animator::OnTimeout);

    timer->setSingleShot(false);
    std::chrono::milliseconds msc(maxRate - startRate);
    timer->setInterval(msc);
    timer->start();
}

void Animator::EnqueueFrame(GTreeConstPtr frame) {
    frames_.push(frame);
}

GTreeConstPtr Animator::PopFrame() {
    assert(!frames_.empty() && "Error in Animator: pop from empty queue");
    GTreeConstPtr frame = frames_.front();
    frames_.pop();
    return frame;
}

}  // namespace rbtree
