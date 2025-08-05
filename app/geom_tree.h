#pragma once

#include <QColor>
#include <QString>
#include <QPointF>

#include "tree.h"

namespace rbtree {

template<typename KeyType = int>
class GeomTree {
public:
    enum class NodeShape : std::uint8_t { Circle, Rect };
    using QScalar = qreal;

public:
    using RBTreeKT = RBTree<KeyType>;
    using NumOfLevel = int;

    static QColor GetNodeColor(typename RBTreeKT::ConstIt it) {
        if (it.getInfo().status == RBTreeKT::NodeStatus::NoChange) {
            if (it.getInfo().color == RBTreeKT::NodeColor::Red) {
                return kCustomDarkRed;
            } else {
                return kCustomBlack;
            }
        }

        if (it.getInfo().status == RBTreeKT::NodeStatus::Found) {
            return kCustomGreen;
        }

        if (it.getInfo().color == RBTreeKT::NodeColor::Red) {
            return kCustomLighterDarkRed;
        } else {
            return kCustomLighterBlack;
        }
    }

public:
    struct GeomNode {
        using GeomNodePtr = std::unique_ptr<GeomNode>;

        struct Info {
            QPointF centre;
            QScalar halfWidth = kHalfWidthOfNodeView;
            NodeShape shape = NodeShape::Circle;

            QColor color = kCustomBlack;
            QString key;

            QScalar widthOfSubtree;
            QScalar heightOfSubtree;
        };

        Info info;

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

    GeomTree(const RBTreeKT& tree) {
        SetNode(root_, tree.GetRoot());
        SetCoordinates(root_);

        QPointF shift{LeftWidth() + kIndent, kIndent};
        ShiftCoordinates(root_, shift);
        AlignCoordinates(root_);
    }

public:
    QScalar LeftWidth() const {
        if (!root_) {
            return 0;
        }
        QScalar leftW;
        if (!root_->left) {
            leftW = kHalfWidthOfNodeView;
        } else {
            leftW = root_->left->info.widthOfSubtree + kMinDistBetweenNodes + kHalfWidthOfNodeView;
        }
        return leftW;
    }

    QScalar Width() const {
        return root_->info.widthOfSubtree + kIndent * 2;
    }

    QScalar Height() const {
        return root_->info.heightOfSubtree + kIndent * 2;
    }

private:
    QScalar SetNode(GeomNodePtr& curNode, typename RBTreeKT::ConstIt it) {
        auto node = std::make_unique<GeomNode>();

        if (!it) {
            node->info.shape = NodeShape::Rect;
            node->info.key = "NIL";

            node->info.widthOfSubtree = node->info.halfWidth * 2;
            node->info.heightOfSubtree = 0;
            curNode = std::move(node);
            return curNode->info.widthOfSubtree;
        }

        node->info.key = QString::number(it.getInfo().key);
        node->info.color = GetNodeColor(it);
        node->info.halfWidth = kHalfWidthOfNodeView;

        QScalar leftWidth = SetNode(node->left, it.Left());
        QScalar rightWidth = SetNode(node->right, it.Right());

        node->left->parent = node.get();
        node->right->parent = node.get();

        node->info.widthOfSubtree = 2 * kHalfWidthOfNodeView + leftWidth + rightWidth;
        node->info.widthOfSubtree += (leftWidth > 0 ? kMinDistBetweenNodes : 0);
        node->info.widthOfSubtree += (rightWidth > 0 ? kMinDistBetweenNodes : 0);

        QScalar leftHeight = node->left->info.heightOfSubtree;
        QScalar rightHeight = node->right->info.heightOfSubtree;
        node->info.heightOfSubtree = std::max(leftHeight, rightHeight) + kHeightOfLevel;

        curNode = std::move(node);

        return curNode->info.widthOfSubtree;
    }

    void SetCoordinates(GeomNodePtr& curNode) {
        if (!curNode) {
            return;
        }
        if (curNode.get() == root_.get()) {
            curNode->info.centre = kStartRootCoordinates;
            SetCoordinates(curNode->left);
            SetCoordinates(curNode->right);
            return;
        }

        GeomNode* parent = curNode->parent;
        QScalar xShift;

        if (!curNode->left) {
            xShift = kHalfWidthOfNodeView;
        } else {
            xShift =
                curNode->left->info.widthOfSubtree + kMinDistBetweenNodes + kHalfWidthOfNodeView;
        }

        if (curNode.get() == parent->left.get()) {
            xShift = curNode->info.widthOfSubtree - xShift;
        }

        xShift += kHalfWidthOfNodeView + kMinDistBetweenNodes;

        if (curNode.get() == parent->left.get()) {
            xShift = -xShift;
        }

        QScalar yShift = kHeightOfLevel;

        QPointF shift = {xShift, yShift};
        curNode->info.centre = parent->info.centre + shift;

        SetCoordinates(curNode->left);
        SetCoordinates(curNode->right);
    }

    void ShiftCoordinates(GeomNodePtr& curNode, QPointF shift) {
        if (!curNode) {
            return;
        }
        curNode->info.centre += shift;
        ShiftCoordinates(curNode->left, shift);
        ShiftCoordinates(curNode->right, shift);
    }

    void AlignCoordinates(GeomNodePtr& curNode) {
        if (!curNode || !curNode->left || !curNode->right) {
            return;
        }
        AlignCoordinates(curNode->left);
        AlignCoordinates(curNode->right);
        curNode->info.centre.setX(
            (curNode->left->info.centre.x() + curNode->right->info.centre.x()) / 2);
    }

private:
    static constexpr const QScalar kHeightOfLevel = 70.;
    static constexpr const QScalar kMinDistBetweenNodes = -20.;
    static constexpr const QScalar kHalfWidthOfNodeView = 25.;
    static constexpr const QPointF kStartRootCoordinates = {0, 0};
    static constexpr const QScalar kIndent = 50.;

    static constexpr const QColor kCustomBlack{0, 0, 0};
    static constexpr const QColor kCustomLighterBlack{100, 100, 100};
    static constexpr const QColor kCustomDarkRed{140, 0, 0};
    static constexpr const QColor kCustomLighterDarkRed{230, 0, 0};
    static constexpr const QColor kCustomGreen{0, 100, 0};

    GeomNodePtr root_;
};

}  // namespace rbtree
