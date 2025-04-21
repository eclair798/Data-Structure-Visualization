#pragma once

namespace rbtree {

// Итератор подойдет для любого бинарного дерева с полями:
// left, right (unique ptrs) и parent (raw ptr)

template<typename Node>
class Iterator {
public:
    using NodePtr = std::unique_ptr<Node>;

    Iterator(Node* startNode = nullptr) : current_(startNode) {
    }

    Iterator(NodePtr& startNode = nullptr) : current_(startNode.get()) {
    }

    Node* operator->() const {
        return current_;
    }

    operator bool() const {
        if (current_) {
            return true;
        }
        return false;
    }

    Iterator& GoLeft() {
        current_ = current_ ? current_->Left.get() : nullptr;
        return *this;
    }

    Iterator Left() {
        Node* next = current_ ? current_->left.get() : nullptr;
        return Iterator(next);
    }

    Iterator& GoRight() {
        current_ = current_ ? current_->right.get() : nullptr;
        return *this;
    }

    Iterator Right() {
        Node* next = current_ ? current_->right.get() : nullptr;
        return Iterator(next);
    }

    Iterator& GoToParent() {
        current_ = current_ ? current_->parent : nullptr;
        return *this;
    }

    Iterator Parent() {
        Node* next = current_ ? current_->parent : nullptr;
        return Iterator(next);
    }

    bool operator==(const Iterator& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const Iterator& other) const {
        return current_ != other.current_;
    }

private:
    Node* current_;
};

template<typename Node>
class ConstIterator {
public:
    using NodePtr = std::unique_ptr<Node>;

    ConstIterator(Node* startNode = nullptr) : current_(startNode) {
    }

    ConstIterator(const NodePtr& startNode = nullptr) : current_(startNode.get()) {
    }

    const Node* operator->() const {
        return current_;
    }

    operator bool() const {
        if (current_) {
            return true;
        }
        return false;
    }

    ConstIterator& GoLeft() {
        current_ = current_ ? current_->left.get() : nullptr;
        return *this;
    }

    ConstIterator Left() {
        Node* next = current_ ? current_->left.get() : nullptr;
        return ConstIterator(next);
    }

    ConstIterator& GoRight() {
        current_ = current_ ? current_->right.get() : nullptr;
        return *this;
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
        Node* next = current_ ? current_->parent : nullptr;
        return ConstIterator(next);
    }

    bool operator==(const ConstIterator& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const ConstIterator& other) const {
        return current_ != other.current_;
    }

private:
    Node* current_;
};

}  // namespace rbtree
