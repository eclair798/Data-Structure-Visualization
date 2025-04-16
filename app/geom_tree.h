#pragma once

#include "tree.h"

#include <memory>
#include <iostream>

namespace app {

enum class Color : std::uint8_t {
    Black,
    Red,
    Green,  // нашли вершину
    Gray,   // промежуточный этап
};

using Scalar = float;

struct Point {
    Scalar x = 0;
    Scalar y = 0;

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point& other) const {
        return {x - other.x, y - other.y};
    }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point& operator-=(const Point& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

const Point rootCoordinates = {0, 0};

using Text = std::string;

// доделать
template<typename KeyType = int>
Color GetNodeColor(typename RBTree<KeyType>::ConstIt it) {
    using Tree = RBTree<KeyType>;
    if (it->status == Tree::NodeStatus::NoChange) {
        switch (it->color) {
            case Tree::NodeColor::Red:
                return Color::Red;
            default:
                return Color::Black;
        }
    }
    if (it->status == Tree::NodeStatus::Found) {
        return Color::Green;
    }
    return Color::Gray;
}

template<typename KeyType = int>
class GeomTree {
public:
    using Tree = RBTree<KeyType>;
    using NumOfLevel = int;

    struct GeomNode {
        using GeomNodePtr = std::unique_ptr<GeomNode>;
        Point centre;
        Scalar R = radiusOfNodeView;
        Color color = Color::Black;

        Text value;
        Scalar widthOfSubtree;

        GeomNodePtr left = nullptr;
        GeomNodePtr right = nullptr;
        GeomNode* parent = nullptr;
    };

    using GeomNodePtr = typename GeomNode::GeomNodePtr;

public:
    using It = Iterator<GeomNode>;
    using ConstIt = ConstIterator<GeomNode>;

    It GetRoot() {
        return It{root_};
    }

    ConstIt GetRoot() const {
        return ConstIt{root_};
    }

public:
    GeomTree(const Tree& tree) {
        SetNode(root_, tree.GetRoot());
        SetCoordinates(root_);
    }

private:
    Scalar SetNode(GeomNodePtr& curNode, typename Tree::ConstIt it) {
        auto node = std::make_unique<GeomNode>();

        if (!it) {
            node->widthOfSubtree = node->R * 2;
            node->value = "NIL";
            curNode = std::move(node);
            return curNode->widthOfSubtree;
        }

        node->value = std::to_string(it->key);
        node->color = GetNodeColor(it);
        node->R = radiusOfNodeView;

        Scalar leftWidth = SetNode(node->left, it.Left());
        Scalar rightWidth = SetNode(node->right, it.Right());

        node->left->parent = node.get();
        node->right->parent = node.get();

        node->widthOfSubtree = 2 * radiusOfNodeView + leftWidth + rightWidth;
        node->widthOfSubtree += (leftWidth > 0 ? minDistBetweenNodes : 0);
        node->widthOfSubtree += (rightWidth > 0 ? minDistBetweenNodes : 0);

        curNode = std::move(node);

        return curNode->widthOfSubtree;
    }

    void SetCoordinates(GeomNodePtr& curNode) {
        if (!curNode) {
            return;
        }
        if (curNode.get() == root_.get()) {
            curNode->centre = rootCoordinates;
            SetCoordinates(curNode->left);
            SetCoordinates(curNode->right);
            return;
        }

        GeomNode* parent = curNode->parent;
        Scalar xShift;

        if (!curNode->left) {
            xShift = radiusOfNodeView;
        } else {
            xShift = curNode->left->widthOfSubtree + minDistBetweenNodes + radiusOfNodeView;
        }

        if (curNode.get() == parent->left.get()) {
            xShift = curNode->widthOfSubtree - xShift;
        }

        xShift += radiusOfNodeView + minDistBetweenNodes;

        if (curNode.get() == parent->left.get()) {
            xShift = -xShift;
        }

        Scalar yShift = heightOfLevel;

        Point shift = {xShift, yShift};
        curNode->centre = parent->centre + shift;

        SetCoordinates(curNode->left);
        SetCoordinates(curNode->right);
    }

private:
    GeomNodePtr root_;

public:
    static constexpr const Scalar heightOfLevel = 50.;
    static constexpr const Scalar minDistBetweenNodes = 5.;
    static constexpr const Scalar radiusOfNodeView = 20.;
};

}  // namespace app
