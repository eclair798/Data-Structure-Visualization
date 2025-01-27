#pragma once

#include <memory>
#include <iostream>

namespace app {

using KeyType = int;

using NodePtr = std::shared_ptr<Node>;

struct Node {
    Node(KeyType key, NodePtr left = nullptr, NodePtr right = nullptr, NodePtr parent = nullptr,
         bool isRed = false);

    KeyType key;
    NodePtr left;
    NodePtr right;
    NodePtr parent = nullptr;
    bool isRed;
};

class RBTree {
public:
    RBTree();
    ~RBTree() = default;
    void Insert(KeyType key);
    void Delete(KeyType key);
    bool Search(KeyType key) const;
    void Print();

private:
    void RotateLeft(NodePtr x);
    void RotateRight(NodePtr x);
    void InsertFixup(NodePtr z);
    void DeleteFixup(NodePtr x);

    void Transplant(NodePtr u, NodePtr v);
    NodePtr Minimum(NodePtr node) const;

    NodePtr SearchHelper(NodePtr node, KeyType key) const;

    void PrintHelper(NodePtr node, std::string indent, bool last);

    static NodePtr NIL;
    NodePtr root_ = NIL;
};

}  // namespace app
