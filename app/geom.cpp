#pragma once

#include "geom.h"

namespace app {

GeomNode::GeomNode(KeyType val, Point coordinate, Scalar R, Color color)
    : val(val), coordinate(coordinate), R(R), color(color) {
}

GeomNodePtr GeomTree::GetRoot() {
    return root_;
}

GeomTree GeomModel::CreateGeomTree(const RBTree &) {
    // TODO
    return;
}

}  // namespace app
