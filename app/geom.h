#pragma once

#include "tree.h"

#include <memory>
#include <iostream>

namespace app {

template<typename KeyType = int>
class GeomModel {
    enum class Color : std::uint8_t { Black, Red };

    using Scalar = float;

    struct Point {
        Scalar x;
        Scalar y;
    };

    class GeomTree {
        struct GeomNode {
            using GeomNodePtr = std::unique_ptr<GeomNode>;
            KeyType val;
            Point coordinate;
            Scalar R;
            Color color;
            GeomNodePtr left = nullptr;
            GeomNodePtr right = nullptr;
        };

        using GeomNodePtr = GeomNode::GeomNodePtr;

        GeomTree(const RBTree &);

        GeomNodePtr GetRoot();

    private:
        GeomNodePtr root_;
    };

    GeomModel(Scalar dy, Scalar R);

    GeomTree CreateGeomTree(const RBTree &);

private:
    Scalar dy;
    Scalar R;
};

}  // namespace app
