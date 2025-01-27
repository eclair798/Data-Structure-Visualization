#pragma once

#include "tree.h"

#include <memory>
#include <iostream>

namespace app {

enum class Color { Black, Red };

using Scalar = float;

struct Point {
    Scalar x;
    Scalar y;
};

using GeomNodePtr = std::shared_ptr<GeomNode>;

struct GeomNode {
    GeomNode(KeyType val, Point coordinate, Scalar R, Color color);
    KeyType val;
    Point coordinate;
    Scalar R;
    Color color;

    GeomNodePtr left = nullptr;
    GeomNodePtr right = nullptr;
};

class GeomTree {
    GeomTree() = default;
    ~GeomTree() = default;

    GeomNodePtr GetRoot();

private:
    GeomNodePtr root_;
};

class GeomModel {
    GeomModel(Scalar dy, Scalar R);
    ~GeomModel() = default;

    GeomTree CreateGeomTree(const RBTree &);

private:
    Scalar dy;
    Scalar R;
};

}  // namespace app
