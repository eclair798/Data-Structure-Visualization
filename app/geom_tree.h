#pragma once

#include "tree.h"

namespace rbtree {

template<typename KeyType = int>
class GeomTree {
public:
    enum class Color : std::uint8_t {
        Black,
        Gray,
        Red,
        LightRed,
        Green,  // нашли вершину
    };

    using Scalar = double;

    enum class NodeShape : std::uint8_t { Circle, Rect };

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

    using Text = std::string;

public:
    using RBTreeKT = RBTree<KeyType>;
    using NumOfLevel = int;

    // todo доделать если буду менять статусы
    static Color GetNodeColor(typename RBTreeKT::ConstIt it) {
        if (it->status == RBTreeKT::NodeStatus::NoChange) {
            switch (it->color) {
                case RBTreeKT::NodeColor::Red:
                    return Color::Red;
                default:
                    return Color::Black;
            }
        }
        if (it->status == RBTreeKT::NodeStatus::Found) {
            return Color::Green;
        }
        switch (it->color) {
            case RBTreeKT::NodeColor::Red:
                return Color::LightRed;
            default:
                return Color::Gray;
        }
    }

public:
    struct GeomNode {
        using GeomNodePtr = std::unique_ptr<GeomNode>;
        Point centre;
        Scalar halfWidth = kHalfWidthOfNodeView;
        NodeShape shape = NodeShape::Circle;

        Color color = Color::Black;

        Text key;
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
    GeomTree(const RBTreeKT& tree) {
        SetNode(root_, tree.GetRoot());
        SetCoordinates(root_);

        Point shift{LeftWidth() + kIndent, kIndent};
        ShiftCoordinates(root_, shift);
        AlignCoordinates(root_);
    }

public:
    Scalar LeftWidth() const {
        if (!root_) {
            return 0;
        }
        Scalar leftW;
        if (!root_->left) {
            leftW = kHalfWidthOfNodeView;
        } else {
            leftW = root_->left->widthOfSubtree + kMinDistBetweenNodes + kHalfWidthOfNodeView;
        }
        return leftW;
    }

private:
    Scalar SetNode(GeomNodePtr& curNode, typename RBTreeKT::ConstIt it) {
        auto node = std::make_unique<GeomNode>();

        if (!it) {
            node->shape = NodeShape::Rect;
            node->key = "NIL";

            node->widthOfSubtree = node->halfWidth * 2;
            curNode = std::move(node);
            return curNode->widthOfSubtree;
        }

        node->key = std::to_string(it->key);
        node->color = GetNodeColor(it);
        node->halfWidth = kHalfWidthOfNodeView;

        Scalar leftWidth = SetNode(node->left, it.Left());
        Scalar rightWidth = SetNode(node->right, it.Right());

        node->left->parent = node.get();
        node->right->parent = node.get();

        node->widthOfSubtree = 2 * kHalfWidthOfNodeView + leftWidth + rightWidth;
        node->widthOfSubtree += (leftWidth > 0 ? kMinDistBetweenNodes : 0);
        node->widthOfSubtree += (rightWidth > 0 ? kMinDistBetweenNodes : 0);

        curNode = std::move(node);

        return curNode->widthOfSubtree;
    }

    void SetCoordinates(GeomNodePtr& curNode) {
        if (!curNode) {
            return;
        }
        if (curNode.get() == root_.get()) {
            curNode->centre = kRootCoordinates;
            SetCoordinates(curNode->left);
            SetCoordinates(curNode->right);
            return;
        }

        GeomNode* parent = curNode->parent;
        Scalar xShift;

        if (!curNode->left) {
            xShift = kHalfWidthOfNodeView;
        } else {
            xShift = curNode->left->widthOfSubtree + kMinDistBetweenNodes + kHalfWidthOfNodeView;
        }

        if (curNode.get() == parent->left.get()) {
            xShift = curNode->widthOfSubtree - xShift;
        }

        xShift += kHalfWidthOfNodeView + kMinDistBetweenNodes;

        if (curNode.get() == parent->left.get()) {
            xShift = -xShift;
        }

        Scalar yShift = kHeightOfLevel;

        Point shift = {xShift, yShift};
        curNode->centre = parent->centre + shift;

        SetCoordinates(curNode->left);
        SetCoordinates(curNode->right);
    }

    void ShiftCoordinates(GeomNodePtr& curNode, Point shift) {
        if (!curNode) {
            return;
        }
        curNode->centre += shift;
        ShiftCoordinates(curNode->left, shift);
        ShiftCoordinates(curNode->right, shift);
    }

    void AlignCoordinates(GeomNodePtr& curNode) {
        if (!curNode || !curNode->left || !curNode->right) {
            return;
        }
        AlignCoordinates(curNode->left);
        AlignCoordinates(curNode->right);
        curNode->centre.x = (curNode->left->centre.x + curNode->right->centre.x) / 2;
    }

private:
    GeomNodePtr root_;

public:
    static constexpr const Scalar kHeightOfLevel = 40.;
    static constexpr const Scalar kMinDistBetweenNodes = 0.;
    static constexpr const Scalar kHalfWidthOfNodeView = 15.;
    static constexpr const Point kRootCoordinates = {0, 0};
    static constexpr const Scalar kIndent = 30.;
};

}  // namespace rbtree
