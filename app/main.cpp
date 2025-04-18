#include "geom_tree.h"

#include <iostream>

using namespace rbtree;

int main() {
    RBTree<int> tree;
    tree.Insert(5);
    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(10);
    tree.Insert(7);
    tree.Insert(8);

    std::cout << tree << "\n=====================\n";

    tree.Delete(5);
    tree.Delete(10);
    tree.Delete(1);

    std::cout << tree << "\n=====================\n";

    GeomTree<int> gTree(tree);

    return 0;
}
