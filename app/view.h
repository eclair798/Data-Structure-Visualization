#pragma once

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "geom_model.h"

namespace rbtree {

class TreeView : public QWidget {
    Q_OBJECT
public:
    using qScalar = qreal;

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
    QColor makeQColor(GTree::Color color);
    QPointF makeQPoint(GTree::Point point);
    QString makeQString(GTree::Text text);

    QRectF CircleToRect(QPointF centre, qScalar radius);
    QRectF GetRect(QPointF centre, qScalar halfWidth);

    void DrawCircleWithCenteredText(QPainter& painter, QRectF circleRect, const QString& text,
                                    const QColor& fillColor = Qt::lightGray);
    void DrawRectWithCenteredText(QPainter& painter, QRectF rect, const QString& text,
                                  const QColor& fillColor = Qt::lightGray);

private:
    GTreeConstPtr currentFrame_;
};

}  // namespace rbtree
