#include "controllers.h"

namespace rbtree {

TreeController::TreeController(RBTreeINT* tree, QLineEdit* keyEdit, QObject* parent)
    : tree_(tree), keyEdit_(keyEdit), QObject(parent) {
}

void TreeController::HandleInsert() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        emit NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Insert(key)) {
        std::string msg = std::format("Key {} inserted successfully.", key);
        emit NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} already exist.", key);
        emit NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

void TreeController::HandleDelete() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        emit NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Delete(key)) {
        std::string msg = std::format("Key {} deleted successfully.", key);
        emit NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} does not exist.", key);
        emit NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

void TreeController::HandleFind() {
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        emit NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Search(key)) {
        std::string msg = std::format("Key {} found.", key);
        emit NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} not found.", key);
        emit NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

void TreeController::HandleReset() {
    tree_->Reset();
    std::string msg = "Tree was reset successfully.";
    emit NewMessage(QString::fromStdString(msg));
}

void TreeController::HandleStatusReset() {
    tree_->StatusResetWithNotify();
    std::string msg = "Node statuses was reset successfully.";
    emit NewMessage(QString::fromStdString(msg));
}

TimerController::TimerController(QTimer* timer, QObject* parent) : timer_(timer), QObject(parent) {
}

void TimerController::HandleRateChange(int rate, int maxRate) {
    std::chrono::milliseconds msc(maxRate - rate);
    timer_->setInterval(msc);
}

ViewController::ViewController(TreeView* view, QLineEdit* keyEdit, QObject* parent)
    : view_(view), keyEdit_(keyEdit), QObject(parent) {
}

void ViewController::HandleScaleChange(int scale, float scaleOfScale) {
    view_->HandleScaleChange(scale, scaleOfScale);
}

void ViewController::HandleViewSave() {
    auto fileName = keyEdit_->text().toStdString();
    bool ok = TreeExporter::SaveToPng(view_, fileName);
    if (ok) {
        std::string msg = "Picture was saved to Donwloads successfully.";
        emit NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = "Something goes wrong. Picture was not saved.";
        emit NewError(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

}  // namespace rbtree
