#include "view.h"

namespace rbtree {

TreeView::TreeView(QWidget *parent) : QWidget(parent) {
}

void TreeView::ShowFrame(GTreeConstPtr frame) {
    currentFrame_ = std::move(frame);
    update();
}

void TreeView::HandleScaleChange(int val) {
    scaler = val / 10.0;
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
    painter.scale(scaler, scaler);
    DrawNode(painter, it);
}

void TreeView::DrawNode(QPainter &painter, ConstIt nodeIt) {
    if (!nodeIt) {
        return;
    }
    DrawEdge(painter, nodeIt, nodeIt->left);
    DrawEdge(painter, nodeIt, nodeIt->right);

    QPointF centre = makeQPoint(nodeIt->centre);
    QScalar halfWidth(nodeIt->halfWidth);
    QColor color = makeQColor(nodeIt->color);
    QString text = makeQString(nodeIt->key);
    QRectF rect;
    if (nodeIt->shape == GTree::NodeShape::Circle) {
        rect = CircleToRect(centre, halfWidth);
    } else {
        rect = GetRect(centre, halfWidth);
    }
    DrawNodeWithCenteredText(painter, rect, text, color, nodeIt->shape);

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

QRectF TreeView::CircleToRect(QPointF centre, QScalar radius) {
    QRectF circleRect(centre.x() - radius, centre.y() - radius, radius * 2, radius * 2);
    return circleRect;
}

QRectF TreeView::GetRect(QPointF centre, QScalar halfWidth) {
    QRectF rect(centre.x() - halfWidth, centre.y() - halfWidth * 0.5, halfWidth * 2, halfWidth);
    return rect;
}

void TreeView::DrawNodeWithCenteredText(QPainter &painter, QRectF rect, const QString &text,
                                        const QColor &fillColor, GTree::NodeShape shape) {
    QFont font(fontName, fontSize);

    painter.setBrush(fillColor);
    painter.setPen(Qt::black);
    if (shape == GTree::NodeShape::Circle) {
        painter.drawEllipse(rect);
        font.setBold(true);
    } else {
        painter.drawRect(rect);
    }

    int size = fontSize;
    while (size > 1) {
        font.setPointSize(size);
        painter.setFont(font);
        QFontMetricsF fm(font);
        QRectF textRect = fm.boundingRect(text);
        if (rect.width() - textRect.width() > textIndent &&
            rect.height() - textRect.height() > textIndent) {
            std::cout << textRect.width();
            std::cout << rect.width();

            break;
        }
        --size;
    }

    painter.setPen(Qt::white);
    painter.drawText(rect, Qt::AlignCenter, text);
}

}  // namespace rbtree
