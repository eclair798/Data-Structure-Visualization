#include "geom_model.h"

namespace rbtree {

GTreeConst::GTreeConst(const RBTreeINT& tree) {
    frame_ = std::make_shared<const GTree>(tree);
}

const GTree* GTreeConst::operator->() const {
    return frame_.get();
}

bool GTreeConst::operator!() const {
    return !frame_;
}

GeomModel::GeomModel()
    : treePort_([this](const RBTreeINT& changedTree) { NotifyFrame(changedTree); }) {
}

void GeomModel::SubscribeTree(RBTreeINT* tree) {
    tree->SubscribeTree(&treePort_);
}

void GeomModel::SubscribeFrame(GTreeObserver* observerPtr) {
    gtreeObservable_.subscribe(observerPtr);
}

void GeomModel::NotifyFrame(const RBTreeINT& tree) {
    gtreeObservable_.set(GTreeConst(tree));
}

}  // namespace rbtree
