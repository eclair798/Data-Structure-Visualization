#include "controllers.h"

namespace rbtree {

TreeController::TreeController(RBTreeINT* tree, QLineEdit* keyEdit, QObject* parent)
    : tree_(tree), keyEdit_(keyEdit), QObject(parent) {
}

void TreeController::HandleInsert() {
    if (keyEdit_->text().isEmpty()) {
        return;
    }
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        emit NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Insert(key)) {
        std::string msg = std::format("Key {} was inserted successfully.", key);
        emit NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} already exists.", key);
        emit NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

void TreeController::HandleDelete() {
    if (keyEdit_->text().isEmpty()) {
        return;
    }
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        emit NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Delete(key)) {
        std::string msg = std::format("Key {} was deleted successfully.", key);
        emit NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} does not exist.", key);
        emit NewMessage(QString::fromStdString(msg));
    }
    keyEdit_->clear();
}

void TreeController::HandleFind() {
    if (keyEdit_->text().isEmpty()) {
        return;
    }
    bool ok;
    int key = keyEdit_->text().toInt(&ok);
    if (!ok) {
        emit NewError("Input error. An integer is required");
        keyEdit_->clear();
        return;
    }
    if (tree_->Search(key)) {
        std::string msg = std::format("Key {} was found in the tree.", key);
        emit NewMessage(QString::fromStdString(msg));
    } else {
        std::string msg = std::format("Key {} has not found", key);
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

TimerController::TimerController(QTimer* timer, QPushButton* pauseButton, QObject* parent)
    : timer_(timer), pauseButton_(pauseButton), QObject(parent) {
}

void TimerController::HandleRateChange(int rate, int maxRate) {
    std::chrono::milliseconds msc(maxRate - rate);
    timer_->setInterval(msc);
}

void TimerController::HandlePause(bool push) {
    if (push) {
        timer_->stop();
        pauseButton_->setText("Resume");
    } else {
        timer_->start();
        pauseButton_->setText("Pause");
    }
}

ViewController::ViewController(TreeView* view, QLineEdit* fileNameEdit, QObject* parent)
    : view_(view), fileNameEdit_(fileNameEdit), QObject(parent) {
}

void ViewController::HandleScaleChange(int scale) {
    view_->HandleScaleChange(scale, kScaleRangeScale);
}

void ViewController::HandleViewSave() {
    auto fileName = fileNameEdit_->text();

    QImage image = GetImage();

    bool ok = TreeExporter::SaveAsPng(&image, fileName);
    if (ok) {
        emit NewMessage("Picture successfully saved to Downloads folder.");
    } else {
        emit NewError("An error occurred. Picture was not saved.");
    }
}

QImage ViewController::GetImage() {
    QSize realTreeSize = view_->TreeSize();
    QImage image(realTreeSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    view_->render(&painter);

    return image;
}

}  // namespace rbtree
