#pragma once

#include <QObject>

#include "view.h"
#include "animator.h"
#include "controllers.h"
#include "main_window.h"
#include "exporter.h"

namespace rbtree {

class Application {
public:
    Application();

private:
    void SetupConnections();

private:
    MainWindow window_;

    RBTreeINT tree_;
    GeomModel geomModel_;

    Animator animator_;

    TreeController treeController_;
    TimerController timerController_;
    ViewController viewController_;
};

}  // namespace rbtree
