#include "view.h"

namespace rbtree {

const QString TreeView::kFontName = "Courier New";

TreeView::TreeView(QWidget *parent) : QWidget(parent) {
}

void TreeView::ShowFrame(GTreeConst frame) {
    currentFrame_ = std::move(frame);
    UpdatePicture();
}

void TreeView::HandleScaleChange(int scale, float scaleOfScale) {
    scaler = scale / scaleOfScale;
    UpdatePicture();
}

QSize TreeView::TreeSize() const {
    return curTreeSize;
}

void TreeView::UpdatePicture() {
    auto w = currentFrame_->Width() * scaler;
    auto h = currentFrame_->Height() * scaler;
    setMinimumWidth(w);
    setMinimumHeight(h);
    update();
    curTreeSize = QSize{CeilScalar(w), CeilScalar(h)};
}

void TreeView::paintEvent(QPaintEvent *) {
    if (!currentFrame_) {
        return;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    DrawTree(&painter);
    painter.end();
}

void TreeView::DrawTree(QPainter *painter) {
    ConstIt it = currentFrame_->GetRoot();
    if (!it) {
        return;
    }
    painter->scale(scaler, scaler);
    DrawNode(painter, it);
}

void TreeView::DrawNode(QPainter *painter, ConstIt nodeIt) {
    if (!nodeIt) {
        return;
    }
    DrawEdge(painter, nodeIt, nodeIt.Left());
    DrawEdge(painter, nodeIt, nodeIt.Right());

    QPointF centre = nodeIt.getInfo().centre;
    QScalar halfWidth = nodeIt.getInfo().halfWidth;
    QColor color = nodeIt.getInfo().color;
    QString text = nodeIt.getInfo().key;
    QRectF rect;

    if (nodeIt.getInfo().shape == GTree::NodeShape::Circle) {
        rect = CircleToRect(centre, halfWidth);
    } else {
        rect = GetRect(centre, halfWidth);
    }
    DrawNodeWithCenteredText(painter, rect, text, color, nodeIt.getInfo().shape);

    DrawNode(painter, nodeIt.Left());
    DrawNode(painter, nodeIt.Right());
}

void TreeView::DrawEdge(QPainter *painter, ConstIt nodeItFrom, ConstIt nodeItTo) {
    if (!nodeItFrom || !nodeItTo) {
        return;
    }
    QPoint from(nodeItFrom.getInfo().centre.x(), nodeItFrom.getInfo().centre.y());
    QPoint to(nodeItTo.getInfo().centre.x(), nodeItTo.getInfo().centre.y());
    painter->setPen(Qt::black);
    painter->drawLine(from, to);
}

int TreeView::CeilScalar(QScalar val) {
    return static_cast<int>(std::ceil(val));
}

QRectF TreeView::CircleToRect(QPointF centre, QScalar radius) {
    QRectF circleRect(centre.x() - radius, centre.y() - radius, radius * 2, radius * 2);
    return circleRect;
}

QRectF TreeView::GetRect(QPointF centre, QScalar halfWidth) {
    QRectF rect(centre.x() - halfWidth, centre.y() - halfWidth * 0.5, halfWidth * 2, halfWidth);
    return rect;
}

void TreeView::DrawNodeWithCenteredText(QPainter *painter, QRectF rect, const QString &text,
                                        const QColor &fillColor, GTree::NodeShape shape) {
    QFont font(kFontName, kFontSize);

    painter->setBrush(fillColor);
    painter->setPen(Qt::black);
    if (shape == GTree::NodeShape::Circle) {
        painter->drawEllipse(rect);
        font.setBold(true);
    } else {
        painter->drawRect(rect);
    }

    int size = kFontSize;
    while (size > 1) {
        font.setPointSize(size);
        painter->setFont(font);
        QFontMetricsF fm(font);
        QRectF textRect = fm.boundingRect(text);
        if (rect.width() - textRect.width() > kTextIndent &&
            rect.height() - textRect.height() > kTextIndent) {
            break;
        }
        --size;
    }

    painter->setPen(Qt::white);
    painter->drawText(rect, Qt::AlignCenter, text);
}

}  // namespace rbtree
