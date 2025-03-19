#pragma once

#include <memory>
#include <iostream>
#include <cassert>
#include <cstdint>

namespace app {

/* Красно-Черное дерево. Его свойства:
* 1) Каждый узел красный или черный
* 2) Корень и конечные узлы (листья) дерева — чёрные (в структуре листья NIL будут храниться как nullptr)
* 3) У красного узла родительский узел — чёрный
* 4) Все простые пути из любого узла x до листьев содержат одинаковое количество чёрных узлов
* 5) Чёрный узел может иметь чёрного родителя
*/

template<typename KeyType = int>
class RBTree {
public:
    enum class NodeColor : std::uint8_t { Black, Red };

    struct Node {
        using NodePtr = std::unique_ptr<Node>;
        KeyType key;
        NodePtr left = nullptr;
        NodePtr right = nullptr;
        Node* parent = nullptr;
        NodeColor color = NodeColor::Black;
    };

    using NodePtr = Node::NodePtr;

    RBTree() = default;

    void Insert(const KeyType& key);
    void Delete(const KeyType& key);
    bool Search(const KeyType& key) const;

    // В будущем: copy constructor, copy assignment, move constructor, move assignment. Наверное

    std::ostream& operator<<(std::ostream& os,
                             const RBTree& tree);  // TODO

private:
    void RotateLeft(Node* x);
    void RotateRight(Node* x);
    void InsertFixup(Node* x);
    void DeleteFixup(Node* parent);

    Node* SearchNode(const KeyType& key) const;
    Node* Minimum(Node* subtreeRoot) const;
    NodePtr& ParentRef(Node* child);

    NodePtr root_ = nullptr;
};

}  // namespace app
