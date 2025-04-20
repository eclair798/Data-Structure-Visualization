#include "controllers.h"

namespace rbtree {

TreeController::TreeController(RBTreeINT* tree, QLineEdit* keyEdit, QObject* parent)
    : tree_(tree), keyEdit_(keyEdit), QObject(parent) {
}

void TreeController::HandleInsert() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        // todo error
        return;
    }
    if (tree_->Insert(key)) {
        NewMessage("Key inserted successfully.");
    } else {
        NewMessage("Key already exist.");
    }
}

void TreeController::HandleDelete() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        // todo error
        return;
    }
    if (tree_->Delete(key)) {
        NewMessage("Key deleted successfully.");
    } else {
        NewMessage("Key does not exist.");
    }
}

void TreeController::HandleFind() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        // todo error
        return;
    }
    if (tree_->Search(key)) {
        NewMessage("Key found.");
    } else {
        NewMessage("Key not found.");
    }
}

void TreeController::HandleReset() {
    tree_->Reset();
}

TimerController::TimerController(QTimer* timer, QObject* parent) : timer_(timer), QObject(parent) {
}

void TimerController::HandleTimerChange(int val) {
    std::chrono::milliseconds msc(val);
    timer_->setInterval(msc);
}

}  // namespace rbtree
