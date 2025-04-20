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
    ConstIt it = currentFrame_->GetRoot();
    if (!it) {
        return;
    }
    DrawNode(painter, it);
}

void TreeView::DrawNode(QPainter &painter, ConstIt nodeIt) {
    if (!nodeIt) {
        return;
    }
    DrawEdge(painter, nodeIt, nodeIt->left);
    DrawEdge(painter, nodeIt, nodeIt->right);

    QPointF centre = makeQPoint(nodeIt->centre);
    qScalar halfWidth(nodeIt->halfWidth);
    QColor color = makeQColor(nodeIt->color);
    QString text = makeQString(nodeIt->key);
    if (nodeIt->shape == GTree::NodeShape::Circle) {
        QRectF cRect = CircleToRect(centre, halfWidth);
        DrawCircleWithCenteredText(painter, cRect, text, color);
    } else {
        QRectF rect = GetRect(centre, halfWidth);
        DrawRectWithCenteredText(painter, rect, text, color);
    }

    DrawNode(painter, nodeIt->left);
    DrawNode(painter, nodeIt->right);
}

void TreeView::DrawEdge(QPainter &painter, ConstIt nodeItFrom, ConstIt nodeItTo) {
    if (!nodeItFrom || !nodeItTo) {
        return;
    }
    QPoint from(nodeItFrom->centre.x, nodeItFrom->centre.y);
    QPoint to(nodeItTo->centre.x, nodeItTo->centre.y);
    painter.setPen(Qt::black);
    painter.drawLine(from, to);
    // if (nodeItTo->shape == GTree::NodeShape::Circle) {

    // } else {

    // }
}

QColor TreeView::makeQColor(GTree::Color color) {
    switch (color) {
        case GTree::Color::Red:
            return Qt::darkRed;
        case GTree::Color::Black:
            return Qt::black;
        case GTree::Color::Gray:
            return Qt::darkGray;
        case GTree::Color::Green:
            return Qt::darkGreen;
        default:
            assert(false);
    }
}

QPointF TreeView::makeQPoint(GTree::Point point) {
    return QPointF(point.x, point.y);
}

QString TreeView::makeQString(GTree::Text text) {
    return QString::fromStdString(text);
}

QRectF TreeView::CircleToRect(QPointF centre, qScalar radius) {
    QRectF circleRect(centre.x() - radius, centre.y() - radius, radius * 2, radius * 2);
    return circleRect;
}

QRectF TreeView::GetRect(QPointF centre, qScalar halfWidth) {
    QRectF rect(centre.x() - halfWidth, centre.y() - halfWidth * 0.5, halfWidth * 2, halfWidth);
    return rect;
}

void TreeView::DrawCircleWithCenteredText(QPainter &painter, QRectF circleRect, const QString &text,
                                          const QColor &fillColor) {
    // Круг
    painter.setBrush(fillColor);
    painter.setPen(Qt::black);
    painter.drawEllipse(circleRect);

    // Текст
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(circleRect, Qt::AlignCenter, text);
}

void TreeView::DrawRectWithCenteredText(QPainter &painter, QRectF rect, const QString &text,
                                        const QColor &fillColor) {
    // Прямоугольник
    painter.setBrush(fillColor);
    painter.setPen(Qt::black);
    painter.drawRect(rect);

    // Текст
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(rect, Qt::AlignCenter, text);
}

}  // namespace rbtree
