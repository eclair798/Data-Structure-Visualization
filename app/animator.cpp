#include "animator.h"

namespace rbtree {

void Animator::onTimeout() {
    if (!frames_.empty()) {
        emit frameReady();
    }
}

Animator::Animator(GeomModel* gModel, QObject* parent)
    : observer_([this](GTreeConstPtr frame) { this->enqueueFrame(frame); }), QObject(parent) {
    gModel->SubscribeFrame(&observer_);

    timer_ = std::make_unique<QTimer>(this);

    connect(timer_.get(), &QTimer::timeout, this, &Animator::onTimeout);

    timer_->setSingleShot(false);
    timer_->setInterval(startTimerInterval);
    timer_->start();
}

void Animator::enqueueFrame(GTreeConstPtr frame) {
    frames_.push(frame);
}

GTreeConstPtr Animator::PopFrame() {
    GTreeConstPtr frame = frames_.front();
    frames_.pop();
    return frame;
}

}  // namespace rbtree
