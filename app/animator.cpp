#include "animator.h"

namespace rbtree {

void Animator::onTimeout() {
    if (!frames_.empty()) {
        emit frameReady();
    }
}

Animator::Animator(GeomModel* gModel, int startTimerInterval, QObject* parent)
    : observer_([this](GTreeConstPtr frame) { this->enqueueFrame(frame); }), QObject(parent) {
    gModel->SubscribeFrame(&observer_);

    enqueueFrame(gModel->GetCurrentFrame());

    timer_ = std::make_unique<QTimer>(this);

    connect(timer_.get(), &QTimer::timeout, this, &Animator::onTimeout);

    timer_->setSingleShot(false);
    std::chrono::milliseconds msc(startTimerInterval);
    timer_->setInterval(msc);
    timer_->start();
}

void Animator::enqueueFrame(GTreeConstPtr frame) {
    frames_.push(frame);
}

GTreeConstPtr Animator::PopFrame() {
    assert(!frames_.empty() && "Error in Animator: pop from empty queue");
    GTreeConstPtr frame = frames_.front();
    frames_.pop();
    return frame;
}

}  // namespace rbtree
