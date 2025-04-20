#include "geom_model.h"

namespace rbtree {

GeomModel::GeomModel(RBTreeINT* tree)
    : observer_([this](const RBTreeINT& changedTree) { this->UpdateFrom(changedTree); }) {
    tree->SubscribeStep(&observer_);
    tree_ = std::make_shared<const GTree>(*tree);
}

void GeomModel::UpdateFrom(const RBTreeINT& tree) {
    tree_ = std::make_shared<const GTree>(tree);
    NotifyFrame();
}

GTreeConstPtr GeomModel::GetCurrentFrame() const {
    return tree_;
}

}  // namespace rbtree
