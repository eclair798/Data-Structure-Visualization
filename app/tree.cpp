#pragma once

#include "tree.h"

namespace app {

Node::Node(KeyType key, NodePtr left, NodePtr right, NodePtr parent, bool isRed)
    : key(key), left(left), right(right), parent(parent), isRed(isRed) {
}

NodePtr RBTree::NIL = std::make_shared<Node>(0, nullptr, nullptr, nullptr, false);

RBTree::RBTree() : root_(NIL) {
}

void RBTree::Insert(KeyType key) {
    NodePtr z = std::make_shared<Node>(key, NIL, NIL, NIL, true);
    NodePtr y = NIL;
    NodePtr x = root_;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NIL) {
        root_ = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = NIL;
    z->right = NIL;
    z->isRed = true;

    InsertFixup(z);
}

void RBTree::InsertFixup(NodePtr z) {
    while (z->parent->isRed) {
        if (z->parent == z->parent->parent->left) {
            NodePtr y = z->parent->parent->right;
            if (y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    RotateLeft(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                RotateRight(z->parent->parent);
            }
        } else {
            NodePtr y = z->parent->parent->left;
            if (y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RotateRight(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                RotateLeft(z->parent->parent);
            }
        }
    }
    root_->isRed = false;
}

void RBTree::Delete(KeyType key) {
    NodePtr z = SearchHelper(root_, key);
    if (z == NIL) {
        return;
    }
    NodePtr y = z;
    NodePtr x;
    bool yOriginalColor = y->isRed;

    if (z->left == NIL) {
        x = z->right;
        Transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        Transplant(z, z->left);
    } else {
        y = Minimum(z->right);
        yOriginalColor = y->isRed;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isRed = z->isRed;
    }
    if (!yOriginalColor) {
        DeleteFixup(x);
    }
}

void RBTree::DeleteFixup(NodePtr x) {
    while (x != root_ && !x->isRed) {
        if (x == x->parent->left) {
            NodePtr w = x->parent->right;
            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                RotateLeft(x->parent);
                w = x->parent->right;
            }
            if (!w->left->isRed && !w->right->isRed) {
                w->isRed = true;
                x = x->parent;
            } else {
                if (!w->right->isRed) {
                    w->left->isRed = false;
                    w->isRed = true;
                    RotateRight(w);
                    w = x->parent->right;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->right->isRed = false;
                RotateLeft(x->parent);
                x = root_;
            }
        } else {
            NodePtr w = x->parent->left;
            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                RotateRight(x->parent);
                w = x->parent->left;
            }
            if (!w->right->isRed && !w->left->isRed) {
                w->isRed = true;
                x = x->parent;
            } else {
                if (!w->left->isRed) {
                    w->right->isRed = false;
                    w->isRed = true;
                    RotateLeft(w);
                    w = x->parent->left;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->left->isRed = false;
                RotateRight(x->parent);
                x = root_;
            }
        }
    }
    x->isRed = false;
}

void RBTree::Transplant(NodePtr u, NodePtr v) {
    if (u->parent == NIL) {
        root_ = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

NodePtr RBTree::Minimum(NodePtr node) const {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

void RBTree::RotateLeft(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL) {
        root_ = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::RotateRight(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL) {
        root_ = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

bool RBTree::Search(KeyType key) const {
    return SearchHelper(root_, key) != NIL;
}

NodePtr RBTree::SearchHelper(NodePtr node, KeyType key) const {
    if (node == NIL || key == node->key) {
        return node;
    }
    if (key < node->key) {
        return SearchHelper(node->left, key);
    }
    return SearchHelper(node->right, key);
}

void RBTree::Print() {
    if (root_ != NIL) {
        PrintHelper(root_, "", true);
    }
}

void RBTree::PrintHelper(NodePtr node, std::string indent, bool last) {
    if (node != NIL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string color = node->isRed ? "RED" : "BLACK";
        std::cout << node->key << "(" << color << ")" << std::endl;
        PrintHelper(node->left, indent, false);
        PrintHelper(node->right, indent, true);
    }
}

}  // namespace app
