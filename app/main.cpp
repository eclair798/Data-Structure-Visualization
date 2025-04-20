#include "geom_tree.h"

#include <iostream>

#include "application.h"
#include "except.h"

using namespace rbtree;

int main(int argc, char* argv[]) {
    try {
        Application app(argc, argv);
        return app.Run();
    } catch (...) {
        except::React();
    }
    return 0;
}
