#include "view.h"

namespace rbtree {

const QString TreeView::kFontName = "Courier New";

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

    QPointF centre = MakeQPoint(nodeIt->centre);
    QScalar halfWidth(nodeIt->halfWidth);
    QColor color = MakeQColor(nodeIt->color);
    QString text = MakeQString(nodeIt->key);
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

QColor TreeView::MakeQColor(GTree::Color color) {
    switch (color) {
        case GTree::Color::Red:
            return kCustomDarkRed;
        case GTree::Color::Black:
            return kCustomBlack;
        case GTree::Color::Gray:
            return kCustomLighterBlack;
        case GTree::Color::LightRed:
            return kCustomLighterDarkRed;
        case GTree::Color::Green:
            return Qt::darkGreen;
        default:
            assert(false);
    }
}

QPointF TreeView::MakeQPoint(GTree::Point point) {
    return QPointF(point.x, point.y);
}

QString TreeView::MakeQString(GTree::Text text) {
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
    QFont font(kFontName, kFontSize);

    painter.setBrush(fillColor);
    painter.setPen(Qt::black);
    if (shape == GTree::NodeShape::Circle) {
        painter.drawEllipse(rect);
        font.setBold(true);
    } else {
        painter.drawRect(rect);
    }

    int size = kFontSize;
    while (size > 1) {
        font.setPointSize(size);
        painter.setFont(font);
        QFontMetricsF fm(font);
        QRectF textRect = fm.boundingRect(text);
        if (rect.width() - textRect.width() > kTextIndent &&
            rect.height() - textRect.height() > kTextIndent) {
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
