#pragma once

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "geom_model.h"

namespace rbtree {

class TreeView : public QWidget {
    Q_OBJECT
public:
    using ConstIt = GTree::ConstIt;
    TreeView(QWidget* parent = nullptr);

    void ShowFrame(GTreeConstPtr frame);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void DrawTree(QPainter& painter);
    void DrawNode(QPainter& painter, ConstIt nodeIt);
    void DrawEdge(QPainter& painter, ConstIt nodeItFrom, ConstIt nodeItTo);

private:
    GTreeConstPtr currentFrame_;
};

}  // namespace rbtree
