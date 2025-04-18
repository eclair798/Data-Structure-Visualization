#pragma once

#include "main_window.h"
#include "animator.h"
#include "geom_model.h"
#include "view.h"

namespace app {

class Application {
public:
    Application();

    void Run();

private:
    std::unique_ptr<MainWindow> window_;

    std::unique_ptr<RBTreeINT> tree_;
    std::unique_ptr<GeomModel> geomModel_;

    std::unique_ptr<Animator> animator_;
    std::unique_ptr<TreeView> treeView_;

    std::unique_ptr<TreeController> tree_controller_;
    std::unique_ptr<TimerController> timer_controller_;

    void SetupConnections();
};

}  // namespace app
