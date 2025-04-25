#pragma once

#include "geom_tree.h"

namespace rbtree {

using Key = int;
using RBTreeINT = RBTree<Key>;
using GTree = GeomTree<Key>;
using GTreeConstPtr = std::shared_ptr<const GTree>;
using GNode = GTree::GeomNode;

class GeomModel {
public:
    using GTreeObservable = NSLibrary::CObservable<GTreeConstPtr, NSLibrary::CByValue>;
    using GTreeObserver = NSLibrary::CColdInput<GTreeConstPtr, NSLibrary::CByValue>;

    using TreeObserver = NSLibrary::CColdInput<const RBTreeINT&, NSLibrary::CByReference>;

    GeomModel(RBTreeINT* tree);

    void UpdateFrom(const RBTreeINT& tree);
    GTreeConstPtr GetCurrentFrame() const;

public:
    void SubscribeFrame(GTreeObserver* observerPtr);

private:
    void NotifyFrame();

private:
    GTreeConstPtr tree_;
    TreeObserver teeObserver_;

    GTreeObservable gtreeObservable_{[this]() -> GTreeConstPtr {
        return GetCurrentFrame();
    }};
};

}  // namespace rbtree
