#pragma once

#include "geom_tree.h"

namespace rbtree {

using Key = int;
using RBTreeINT = RBTree<Key>;
using GTree = GeomTree<Key>;
using GNode = GTree::GeomNode;

class GTreeConst {
public:
    GTreeConst() = default;

    GTreeConst(const RBTreeINT& tree);

    const GTree* operator->() const;

    bool operator!() const;

private:
    std::shared_ptr<const GTree> frame_;
};

class GeomModel {
public:
    using GTreeObservable = NSLibrary::CObservableData<GTreeConst, NSLibrary::CByValue>;
    using GTreeObserver = NSLibrary::CHotInput<GTreeConst, NSLibrary::CByValue>;

    using TreeObserver = NSLibrary::CHotInput<const RBTreeINT&, NSLibrary::CByReference>;

    GeomModel();

    void SubscribeTree(RBTreeINT* tree);

public:
    void SubscribeFrame(GTreeObserver* observerPtr);

private:
    void NotifyFrame(const RBTreeINT& tree);

private:
    TreeObserver treePort_;

    GTreeObservable gtreeObservable_;
};

}  // namespace rbtree
