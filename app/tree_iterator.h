#pragma once

namespace rbtree {

// Итератор подойдет для любого бинарного дерева с полями:
// left, right (unique ptrs), parent (raw ptr) и info

template<typename Node>
class Iterator {
public:
    using NodePtr = std::unique_ptr<Node>;
    using Info = Node::Info;

    Iterator(Node* startNode = nullptr) : current_(startNode) {
    }

    Iterator(NodePtr& startNode = nullptr) : current_(startNode.get()) {
    }

    Info& getInfo() {
        return current_->info;
    }

    operator bool() const {
        return current_;
    }

    Iterator& GoLeft() {
        current_ = current_ ? current_->left.get() : nullptr;
        return *this;
    }

    Iterator Left() {
        Iterator it = *this;
        it.GoLeft();
        return it;
    }

    Iterator& GoRight() {
        current_ = current_ ? current_->right.get() : nullptr;
        return *this;
    }

    Iterator Right() {
        Iterator it = *this;
        it.GoRight();
        return it;
    }

    Iterator& GoToParent() {
        current_ = current_ ? current_->parent : nullptr;
        return *this;
    }

    Iterator Parent() {
        Iterator it = *this;
        it.GoToParent();
        return it;
    }

    bool operator==(const Iterator& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }

private:
    Node* current_;
};

template<typename Node>
class ConstIterator {
public:
    using NodePtr = std::unique_ptr<Node>;
    using Info = Node::Info;

    ConstIterator(Node* startNode = nullptr) : current_(startNode) {
    }

    ConstIterator(const NodePtr& startNode = nullptr) : current_(startNode.get()) {
    }

    const Info& getInfo() {
        return current_->info;
    }

    operator bool() const {
        return current_;
    }

    ConstIterator& GoLeft() {
        current_ = current_ ? current_->left.get() : nullptr;
        return *this;
    }

    ConstIterator Left() {
        ConstIterator it = *this;
        it.GoLeft();
        return it;
    }

    ConstIterator& GoRight() {
        ConstIterator it = *this;
        it.GoRight();
        return it;
    }

    ConstIterator Right() {
        Node* next = current_ ? current_->right.get() : nullptr;
        return ConstIterator(next);
    }

    ConstIterator& GoToParent() {
        current_ = current_ ? current_->parent : nullptr;
        return *this;
    }

    ConstIterator Parent() {
        ConstIterator it = *this;
        it.GoToParent();
        return it;
    }

    bool operator==(const ConstIterator& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const ConstIterator& other) const {
        return !(*this == other);
    }

private:
    Node* current_;
};

}  // namespace rbtree
