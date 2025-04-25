#include "geom_model.h"

namespace rbtree {

GeomModel::GeomModel(RBTreeINT* tree)
    : teeObserver_([this](const RBTreeINT& changedTree) { this->UpdateFrom(changedTree); }) {
    tree->SubscribeStep(&teeObserver_);
    tree_ = std::make_shared<const GTree>(*tree);
}

void GeomModel::UpdateFrom(const RBTreeINT& tree) {
    tree_ = std::make_shared<const GTree>(tree);
    NotifyFrame();
}

GTreeConstPtr GeomModel::GetCurrentFrame() const {
    return tree_;
}

void GeomModel::SubscribeFrame(GTreeObserver* observerPtr) {
    gtreeObservable_.subscribe(observerPtr);
}

void GeomModel::NotifyFrame() {
    gtreeObservable_.notify();
}

}  // namespace rbtree
