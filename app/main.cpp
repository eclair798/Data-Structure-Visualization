#include "geom_tree.h"

#include <QApplication>

#include <iostream>

#include "application.h"
#include "except.h"

int main(int argc, char* argv[]) {
    try {
        QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
        QApplication qtApp(argc, argv);
        rbtree::Application app;
        return qtApp.exec();
    } catch (...) {
        except::React();
    }
    return 0;
}
