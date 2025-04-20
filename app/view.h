#pragma once

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "geom_model.h"

namespace rbtree {

class TreeView : public QWidget {
    Q_OBJECT
public:
    using QScalar = qreal;

    using ConstIt = GTree::ConstIt;
    TreeView(QWidget* parent = nullptr);

    void ShowFrame(GTreeConstPtr frame);

public slots:
    void HandleScaleChange(int val);

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

    QRectF CircleToRect(QPointF centre, QScalar radius);
    QRectF GetRect(QPointF centre, QScalar halfWidth);

    void DrawNodeWithCenteredText(QPainter& painter, QRectF rect, const QString& text,
                                  const QColor& fillColor = Qt::lightGray,
                                  GTree::NodeShape shape = GTree::NodeShape::Circle);

public:
    QScalar scaler = 1;

private:
    GTreeConstPtr currentFrame_;
    static constexpr const int fontSize = 14;
    const QString fontName = "Courier New";
    static constexpr const QScalar textIndent = 1.;
};

}  // namespace rbtree
