#pragma once

#include <cmath>

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "geom_model.h"

namespace rbtree {

class TreeView : public QWidget {
    Q_OBJECT

    struct Interval {
        int from;
        int to;
    };

public:
    using QScalar = qreal;
    using ConstIt = GTree::ConstIt;

    TreeView(QWidget* parent = nullptr);

    void ShowFrame(GTreeConst frame);

    void HandleScaleChange(int scale, float scaleOfScale);

    QSize TreeSize() const;

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void UpdatePicture();

    void DrawTree(QPainter* painter);
    void DrawNode(QPainter* painter, ConstIt nodeIt);
    void DrawEdge(QPainter* painter, ConstIt nodeItFrom, ConstIt nodeItTo);

    int CeilScalar(QScalar val);

    QRectF CircleToRect(QPointF centre, QScalar radius);
    QRectF GetRect(QPointF centre, QScalar halfWidth);

    void DrawNodeWithCenteredText(QPainter* painter, QRectF rect, const QString& text,
                                  const QColor& fillColor = Qt::lightGray,
                                  GTree::NodeShape shape = GTree::NodeShape::Circle);

public:
    static constexpr const Interval kScaleRange = {10, 200};
    static constexpr const int kStartScale = 100;

private:
    QScalar scaler = 1;
    QSize curTreeSize{0, 0};
    GTreeConst currentFrame_;

    static constexpr const QScalar kTextIndent = 2.;
    static const QString kFontName;
    static constexpr const int kFontSize = 28;
};

}  // namespace rbtree
