#include "geom_tree.h"

#include <iostream>

#include "application.h"
#include "except.h"

int main(int argc, char* argv[]) {
    try {
        rbtree::Application app(argc, argv);
        return app.Run();
    } catch (...) {
        except::React();
    }
    return 0;
}
