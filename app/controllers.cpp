#include "controllers.h"

namespace rbtree {

TreeController::TreeController(RBTreeINT* tree, QLineEdit* keyEdit, QObject* parent)
    : tree_(tree), keyEdit_(keyEdit), QObject(parent) {
}

void TreeController::HandleInsert() {
    bool ok;
    int value = keyEdit_->text().toInt(&ok);
    if (ok) {
        tree_->Insert(value);
    } else {
        // todo error
    }
}

void TreeController::HandleDelete() {
    bool ok;
    int value = keyEdit_->text().toInt(&ok);
    if (ok) {
        tree_->Delete(value);
    } else {
        // todo error
    }
}

void TreeController::HandleFind() {
    bool ok;
    int value = keyEdit_->text().toInt(&ok);
    if (ok) {
        tree_->Search(value);
    } else {
        // todo error
    }
}

void TreeController::HandleReset() {
    tree_->Reset();
}

TimerController::TimerController(QTimer* timer, QObject* parent) : timer_(timer), QObject(parent) {
}

void TimerController::HandleTimerChange(int value) {
    // todo
}

}  // namespace rbtree
