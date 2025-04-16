#include "geom_model.h"

namespace app {

GeomModel::GeomModel(Tree& tree) : observer_([this](const Tree& tree) { this->UpdateFrom(tree); }) {
    tree.SubscribeStep(&observer_);
}

void GeomModel::UpdateFrom(const Tree& tree) {
    tree_ = std::make_shared<const GTree>(GTree(tree));
}

GeomModel::GTreeConstPtr GeomModel::GetCurrentFrame() const {
    return tree_;
}

}  // namespace app
