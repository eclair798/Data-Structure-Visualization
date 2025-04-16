#pragma once

#include "geom_tree.h"

namespace app {

using KeyType = int;

class GeomModel {
public:
    using Tree = RBTree<KeyType>;
    using GTree = GeomTree<KeyType>;
    using GTreeConstPtr = std::shared_ptr<const GTree>;

    using Observer = NSLibrary::CColdInput<const Tree&, NSLibrary::CByReference>;

    GeomModel(Tree& tree);

    void UpdateFrom(const Tree& tree);
    GTreeConstPtr GetCurrentFrame() const;

private:
    GTreeConstPtr tree_;
    Observer observer_;
};

}  // namespace app
