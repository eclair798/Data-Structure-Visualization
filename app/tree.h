#pragma once

#include <memory>
#include <iostream>
#include <cassert>
#include <cstdint>

#include "tree_iterator.h"
#include "observer.h"

namespace rbtree {

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
    enum class NodeStatus : std::uint8_t { NoChange, Found, Intermediate };

private:
    struct Node {
        using NodePtr = std::unique_ptr<Node>;
        KeyType key;
        NodePtr left = nullptr;
        NodePtr right = nullptr;
        Node* parent = nullptr;
        NodeColor color = NodeColor::Black;

        NodeStatus status = NodeStatus::NoChange;
    };

    using NodePtr = typename Node::NodePtr;

public:
    using It = Iterator<Node>;
    using ConstIt = ConstIterator<Node>;

    using TreeObservable = NSLibrary::CObservable<const RBTree&, NSLibrary::CByReference>;
    using TreeObserver = NSLibrary::CColdInput<const RBTree&, NSLibrary::CByReference>;

    It GetRoot() {
        return It{root_};
    }

    ConstIt GetRoot() const {
        return ConstIt{root_};
    }

public:
    RBTree() = default;

    // Вставка нового ключа
    void Insert(const KeyType& key) {
        if (Search(key)) {
            return;  // Ключ уже в дереве
        }

        NodePtr newNode = std::make_unique<Node>(key);

        // Дерево пустое
        if (!root_) {
            newNode->color = NodeColor::Black;
            root_ = std::move(newNode);
            return;
        }
        newNode->color = NodeColor::Red;

        // ищем нужное место и родителя этого места
        Node* current = root_.get();
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (key < current->key) {
                current = current->left.get();
            } else {
                current = current->right.get();
            }
        }

        // insert
        newNode->parent = parent;
        Node* rawNew = newNode.get();

        if (key < parent->key) {
            parent->left = std::move(newNode);
        } else {
            parent->right = std::move(newNode);
        }

        // fixup
        InsertFixup(rawNew);
    }

    /* 
    * Удаление узла по ключу.
    * 1) Сначала ищем узел p с нужным ключом.
    * 2) В зависимости от числа детей действуем как в обычном BST:
    *    - Нет детей: удаляем узел напрямую.
    *    - Один ребёнок: "поднимаем" ребёнка на место p.
    *    - Два ребёнка: ищем "следующего по ключу" (minimum в правом поддереве),
    *      копируем его ключ в p, а дальше удаляем найденный узел как в случае "нет или один ребёнок".
    * 3) Если удалённая (или перемещённая) вершина была чёрной, делаем fixup.
    */
    void Delete(const KeyType& key) {
        Node* z = SearchNode(key);
        if (!z) {
            return;
        }

        // y - удаляемый узел
        Node* y = z;
        NodeColor yOriginalColor = y->color;
        Node* yOriginalParent = y->parent;

        // x - единственный сын y который поднимем на его место
        Node* x = nullptr;
        NodePtr tmpHolder;

        if (!z->left) {
            // нет левого ребёнка
            x = z->right.get();
            // "поднимаем" z->right на место z
            NodePtr& zRef = ParentRef(z);
            tmpHolder = std::move(zRef);
            NodePtr rightSubtree = std::move(z->right);
            if (rightSubtree) {
                rightSubtree->parent = z->parent;
            }
            zRef = std::move(rightSubtree);
        } else if (!z->right) {
            // нет правого ребёнка
            x = z->left.get();
            NodePtr& zRef = ParentRef(z);
            tmpHolder = std::move(zRef);
            NodePtr leftSubtree = std::move(z->left);
            if (leftSubtree) {
                leftSubtree->parent = z->parent;
            }
            zRef = std::move(leftSubtree);
        } else {
            // у z два ребёнка.
            y = Minimum(z->right.get());
            yOriginalColor = y->color;
            yOriginalParent = y->parent;

            x = y->right.get();

            // поднимаем x на место y
            NodePtr& yRef = ParentRef(y);
            tmpHolder = std::move(yRef);
            NodePtr yRight = std::move(y->right);
            if (yRight) {
                yRight->parent = y->parent;
            }
            yRef = std::move(yRight);

            // поднимаем y на место z
            NodePtr& zRef = ParentRef(z);

            y->right = std::move(z->right);
            y->right->parent = y;
            y->left = std::move(z->left);
            y->left->parent = y;
            y->parent = z->parent;
            y->color = z->color;

            NodePtr oldZ = std::move(zRef);
            zRef = std::move(tmpHolder);
        }

        if (yOriginalColor == NodeColor::Red) {
            return;
        }
        if (x) {
            assert(x->color == NodeColor::Red &&
                   "Error in Delete: The only child is black. The black height on the right and on "
                   "the "
                   "left is different");
            x->color = NodeColor::Black;
            return;
        }

        DeleteFixup(yOriginalParent);  // x это nullptr то есть nil
    }

    bool Search(const KeyType& key) const {
        return (SearchNode(key) != nullptr);
    }

    void Reset() {
        root_.reset();
    }

    void StatusReset(Node* now = nullptr) {
        if (root_ == nullptr) {
            return;
        }
        if (now == nullptr) {
            now = root_.get();
        }
        now->status = NodeStatus::NoChange;
        if (now->left) {
            StatusReset(now->left.get());
        }
        if (now->right) {
            StatusReset(now->right.get());
        }
    }

    template<typename KT>
    friend std::ostream& operator<<(std::ostream& os, const RBTree<KT>& tree) {
        if (!tree.root_) {
            os << "<empty tree>";
            return os;
        }

        std::function<void(const typename RBTree<KeyType>::NodePtr&, std::string, std::string)>
            printSubtree;

        printSubtree = [&](const typename RBTree<KeyType>::NodePtr& node, std::string indent,
                           std::string branch) {
            if (node) {
                os << indent << branch << node->key << "["
                   << (node->color == RBTree<KeyType>::NodeColor::Red ? "R" : "B") << "]" << "\n";
                printSubtree(node->left, indent + "    ", "L-- ");
                printSubtree(node->right, indent + "    ", "R-- ");
            }
        };

        printSubtree(tree.root_, "", "");
        return os;
    }

private:
    /*
    *       x               y
    *      / \             / \
    *     A   y    -->    x   C
    *        / \         / \
    *       B   C       A   B
    */
    void RotateLeft(Node* x) {
        if (!x || !x->right) {
            return;
        }

        NodePtr oldY = std::move(x->right);  // "упаковали" y во временный unique_ptr
        Node* y = oldY.get();
        y->parent = nullptr;

        x->right = std::move(y->left);  // в этот момент y отвязался от unique_ptr
        if (x->right) {
            x->right->parent = x;
        }

        NodePtr& refToX = ParentRef(x);  // получаем ссылку на x
        refToX.release();                // отвязываем x от unique_ptr

        NodePtr oldX;
        oldX.reset(x);  // "упаковали" x во временный unique_ptr

        // Восстанавливаем связь y->parent = x->parent
        y->parent = x->parent;

        // В refToX (тот, что раньше указывал на x) запишем y
        refToX = std::move(oldY);  // теперь refToX владеет y

        // y->left становится x
        y->left = std::move(oldX);
        y->left->parent = y;
    }

    /*
    *         x           y
    *        / \         / \
    *       y   A  -->  B   x   
    *      / \             / \
    *     B   C           C   A
    */
    void RotateRight(Node* x) {
        if (!x || !x->left) {
            return;
        }

        NodePtr oldY = std::move(x->left);
        Node* y = oldY.get();
        y->parent = nullptr;

        // Перенос "правого поддерева y" на "левое поддерево x"
        x->left = std::move(y->right);
        if (x->left) {
            x->left->parent = x;
        }

        NodePtr& refToX = ParentRef(x);
        refToX.release();

        NodePtr oldX;
        oldX.reset(x);

        y->parent = x->parent;
        refToX = std::move(oldY);

        y->right = std::move(oldX);
        y->right->parent = y;
    }

    /*
    * Восстановление КЧ-свойств после вставки узла x.
    * Пока у x есть "красный родитель", проверяем "дядю".
    * Если дядя красный - просто перекрашиваем, иначе делаем повороты.
    */
    void InsertFixup(Node* x) {
        // Пока есть родитель и он красный - нарушение свойства 3
        while (x != root_.get() && x->parent->color == NodeColor::Red) {
            Node* parent = x->parent;
            Node* grandparent =
                parent->parent;  // если есть красный отец то и дед должен быть, причем черный
            assert(grandparent && "Error in InsertFixup: red node has not parent");
            assert(grandparent->color == NodeColor::Black &&
                   "Error in InsertFixup: red node has red parent");

            if (parent == grandparent->left.get()) {
                // "Дядя" - правый сын деда
                Node* uncle = grandparent->right.get();

                // 1) Дядя красный
                if (uncle && uncle->color == NodeColor::Red) {
                    // Перекрашиваем
                    parent->color = NodeColor::Black;
                    uncle->color = NodeColor::Black;
                    grandparent->color = NodeColor::Red;
                    x = grandparent;
                } else {
                    // 2) Дядя чёрный
                    if (x == parent->right.get()) {
                        x = parent;
                        RotateLeft(x);
                        parent = x->parent;
                        grandparent = parent->parent;
                    }
                    parent->color = NodeColor::Black;
                    grandparent->color = NodeColor::Red;
                    RotateRight(grandparent);
                }
            } else {
                // "Дядя" - левый сын деда
                Node* uncle = grandparent->left.get();

                // 1) Дядя красный
                if (uncle && uncle->color == NodeColor::Red) {
                    parent->color = NodeColor::Black;
                    uncle->color = NodeColor::Black;
                    grandparent->color = NodeColor::Red;
                    x = grandparent;
                } else {
                    // 2) Дядя чёрный
                    if (x == parent->left.get()) {
                        x = parent;
                        RotateRight(x);
                        parent = x->parent;
                        grandparent = parent->parent;
                    }
                    parent->color = NodeColor::Black;
                    grandparent->color = NodeColor::Red;
                    RotateLeft(grandparent);
                }
            }
        }
        root_->color = NodeColor::Black;
    }

    /*
    * Восстановление КЧ-свойств после удаления.
    * x - это NIL узел который имеет двойную черность.
    * Идём вверх до корня, пока не снимем двойную чёрность.
    */
    void DeleteFixup(Node* parent) {
        Node* x = nullptr;
        while (x != root_.get() && (!x || x->color == NodeColor::Black)) {
            parent = x ? x->parent : parent;

            if (x == parent->left.get()) {
                // x - левый ребёнок
                Node* w = parent->right.get();
                assert(w && "Error in DeleteFixup: x has not brother");

                // 1. Если брат красный
                if (w->color == NodeColor::Red) {
                    w->color = NodeColor::Black;
                    parent->color = NodeColor::Red;
                    RotateLeft(parent);
                    w = parent->right.get();
                    assert(w && "Error in DeleteFixup: x has not brother");
                }

                // 2. Если дети брата чёрные
                if ((!w->left || w->left->color == NodeColor::Black) &&
                    (!w->right || w->right->color == NodeColor::Black)) {
                    w->color = NodeColor::Red;
                    x = parent;
                    continue;
                } else {
                    // 3. Если левый ребёнок брата красный, а правый чёрный
                    if (!w->right || w->right->color == NodeColor::Black) {
                        if (w->left) {
                            w->left->color = NodeColor::Black;
                        }
                        w->color = NodeColor::Red;
                        RotateRight(w);
                        w = parent->right.get();
                        if (!w) {
                            x = parent;
                            continue;
                        }
                    }
                    // 4. Правый ребёнок брата красный
                    w->color = parent->color;
                    parent->color = NodeColor::Black;
                    if (w->right) {
                        w->right->color = NodeColor::Black;
                    }
                    RotateLeft(parent);
                    x = root_.get();
                }
            } else {
                // x - правый ребёнок
                Node* w = parent->left.get();
                assert(w && "Error in DeleteFixup: x has not brother");

                // 1. Брат красный
                if (w->color == NodeColor::Red) {
                    w->color = NodeColor::Black;
                    parent->color = NodeColor::Red;
                    RotateRight(parent);
                    w = parent->left.get();
                    assert(w && "Error in DeleteFixup: x has not brother");
                }

                // 2. Оба ребёнка брата чёрные
                if ((!w->left || w->left->color == NodeColor::Black) &&
                    (!w->right || w->right->color == NodeColor::Black)) {
                    w->color = NodeColor::Red;
                    x = parent;
                    continue;
                } else {
                    // 3. Правый ребёнок брата красный, а левый чёрный
                    if (!w->left || w->left->color == NodeColor::Black) {
                        if (w->right) {
                            w->right->color = NodeColor::Black;
                        }
                        w->color = NodeColor::Red;
                        RotateLeft(w);
                        w = parent->left.get();
                        if (!w) {
                            x = parent;
                            continue;
                        }
                    }
                    // 4. Левый ребёнок брата красный
                    w->color = parent->color;
                    parent->color = NodeColor::Black;
                    if (w->left) {
                        w->left->color = NodeColor::Black;
                    }
                    RotateRight(parent);
                    x = root_.get();
                }
            }
        }
        x->color = NodeColor::Black;
    }

    // Просто ищет ноду с ключом. Если такого нет, то просто nullptr
    Node* SearchNode(const KeyType& key) const {
        Node* current = root_.get();
        while (current != nullptr) {
            if (key < current->key) {
                current = current->left.get();
            } else if (key > current->key) {
                current = current->right.get();
            } else {
                return current;
            }
        }
        return nullptr;
    }

    // Минимальный ключ в поддереве
    Node* Minimum(Node* subtreeRoot) const {
        Node* current = subtreeRoot;
        while (current->left) {
            current = current->left.get();
        }
        return current;
    }

    // Возвращает NodePtr& указываюзий на Node*
    NodePtr& ParentRef(Node* child) {
        if (child == root_.get()) {
            return root_;
        }
        Node* p = child->parent;
        assert(p && "Error in ParentRef: child->parent is null");

        if (p->left.get() == child) {
            return p->left;
        } else if (p->right.get() == child) {
            return p->right;
        }
        assert(false && "Error in ParentRef: child->parent has not this child");
    }

public:
    void SubscribeStep(TreeObserver* observerPtr) {
        observable_.subscribe(observerPtr);
    }

private:
    void NotifyStep() {  // todo: проставить NotifyStep в местах изменения дерева
        observable_.notify();
    }

private:
    NodePtr root_ = nullptr;

    TreeObservable observable_{[this]() -> const RBTree& {
        return *this;
    }};
};

}  // namespace rbtree
