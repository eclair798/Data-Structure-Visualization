#pragma once

#include <QObject>

#include "view.h"
#include "animator.h"
#include "controllers.h"
#include "main_window.h"

namespace rbtree {

class Application {
public:
    Application();

    void Run();

private:
    std::unique_ptr<MainWindow> window_;

    std::unique_ptr<RBTreeINT> tree_;
    std::unique_ptr<GeomModel> geomModel_;

    std::unique_ptr<Animator> animator_;

    std::unique_ptr<TreeController> treeController_;
    std::unique_ptr<TimerController> timerController_;

    void SetupConnections();
};

// todo проставить asserts и errors

}  // namespace rbtree
