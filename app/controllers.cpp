#include "controllers.h"

namespace rbtree {

TreeController::TreeController(RBTreeINT* tree, QLineEdit* keyEdit, QObject* parent)
    : tree_(tree), keyEdit_(keyEdit), QObject(parent) {
}

void TreeController::HandleInsert() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Insert(key)) {
        std::string msg = std::format("Key {} inserted successfully.", key);
        NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} already exist.", key);
        NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

void TreeController::HandleDelete() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Delete(key)) {
        std::string msg = std::format("Key {} deleted successfully.", key);
        NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} does not exist.", key);
        NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

void TreeController::HandleFind() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Search(key)) {
        std::string msg = std::format("Key {} found.", key);
        NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} not found.", key);
        NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
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
