#pragma once

#include "tree.h"

#include <memory>
#include <iostream>

namespace app {

enum class Color : std::uint8_t { Black, Red };

using Scalar = float;

const Scalar dy = 0;   // todo
const Scalar eps = 0;  // todo
const Scalar R = 0;    // todo

struct Point {
    Scalar x = 0;
    Scalar y = 0;
};

template<typename KeyType = int>
struct Circle {
    Point centre;
    Scalar R;
    Color color;
    KeyType value;
};

template<typename KeyType = int>
class GeomTree {
    struct GeomNode {
        using GeomNodePtr = std::unique_ptr<GeomNode>;
        Circle<KeyType> circle;
        GeomNodePtr left = nullptr;
        GeomNodePtr right = nullptr;
    };

    using GeomNodePtr = typename GeomNode::GeomNodePtr;

    GeomTree(const RBTree<KeyType>& tree);

    GeomNodePtr GetRoot();

private:
    GeomNodePtr root_;
};

}  // namespace app
