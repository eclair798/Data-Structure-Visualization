#pragma once

#include "geom_tree.h"

namespace app {

using KeyType = int;

class GeomModel {
    GeomModel(Scalar dy, Scalar R);

    GeomTree<KeyType> CreateGeomTree(const RBTree<KeyType>& tree);

private:
    // todo
};

}  // namespace app
