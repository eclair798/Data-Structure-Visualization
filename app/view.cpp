#include "view.h"

namespace rbtree {

TreeView::TreeView(QWidget *parent) : QWidget(parent) {
}

void TreeView::ShowFrame(GTreeConstPtr frame) {
    currentFrame_ = std::move(frame);
    update();
}

void TreeView::paintEvent(QPaintEvent *) {
    if (!currentFrame_) {
        return;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    DrawTree(painter);
}

void TreeView::DrawTree(QPainter &painter) {
    // todo
}

void TreeView::DrawNode(QPainter &painter, ConstIt nodeIt) {
    // todo
}

void TreeView::DrawEdge(QPainter &painter, ConstIt nodeItFrom, ConstIt nodeItTo) {
    // todo
}

}  // namespace rbtree
