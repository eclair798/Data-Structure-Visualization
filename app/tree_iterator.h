#pragma once

namespace app {

// Итератор подойдет для любого бинарного дерева с полями:
// left, right (unique ptrs) и parent (raw ptr)

template<typename Node>
class Iterator {
public:
    using NodePtr = std::unique_ptr<Node>;

    Iterator(Node* startNode = nullptr) : current(startNode) {
    }

    Iterator(NodePtr& startNode = nullptr) : current(startNode.get()) {
    }

    Node* operator->() const {
        return current;
    }

    operator bool() const {
        if (current) {
            return true;
        }
        return false;
    }

    Iterator& GoLeft() {
        current = current ? current->Left.get() : nullptr;
        return *this;
    }

    Iterator Left() {
        Node* next = current ? current->left.get() : nullptr;
        return Iterator(next);
    }

    Iterator& GoRight() {
        current = current ? current->right.get() : nullptr;
        return *this;
    }

    Iterator Right() {
        Node* next = current ? current->right.get() : nullptr;
        return Iterator(next);
    }

    Iterator& GoToParent() {
        current = current ? current->parent : nullptr;
        return *this;
    }

    Iterator parent() {
        Node* next = current ? current->parent : nullptr;
        return Iterator(next);
    }

    bool operator==(const Iterator& other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }

private:
    Node* current;
};

template<typename Node>
class ConstIterator {
public:
    using NodePtr = std::unique_ptr<Node>;

    ConstIterator(Node* startNode = nullptr) : current(startNode) {
    }

    ConstIterator(const NodePtr& startNode = nullptr) : current(startNode.get()) {
    }

    const Node* operator->() const {
        return current;
    }

    operator bool() const {
        if (current) {
            return true;
        }
        return false;
    }

    ConstIterator& GoLeft() {
        current = current ? current->left.get() : nullptr;
        return *this;
    }

    ConstIterator Left() {
        Node* next = current ? current->left.get() : nullptr;
        return ConstIterator(next);
    }

    ConstIterator& GoRight() {
        current = current ? current->right.get() : nullptr;
        return *this;
    }

    ConstIterator Right() {
        Node* next = current ? current->right.get() : nullptr;
        return ConstIterator(next);
    }

    ConstIterator& GoToParent() {
        current = current ? current->parent : nullptr;
        return *this;
    }

    ConstIterator parent() {
        Node* next = current ? current->parent : nullptr;
        return ConstIterator(next);
    }

    bool operator==(const ConstIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const ConstIterator& other) const {
        return current != other.current;
    }

private:
    Node* current;
};

}  // namespace app
