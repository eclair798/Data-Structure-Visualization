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
    QColor MakeQColor(GTree::Color color);
    QPointF MakeQPoint(GTree::Point point);
    QString MakeQString(GTree::Text text);

    QRectF CircleToRect(QPointF centre, QScalar radius);
    QRectF GetRect(QPointF centre, QScalar halfWidth);

    void DrawNodeWithCenteredText(QPainter& painter, QRectF rect, const QString& text,
                                  const QColor& fillColor = Qt::lightGray,
                                  GTree::NodeShape shape = GTree::NodeShape::Circle);

public:
    QScalar scaler = 1;

private:
    GTreeConstPtr currentFrame_;

    static constexpr const QColor kCustomBlack{0, 0, 0};
    static constexpr const QColor kCustomLighterBlack{100, 100, 100};

    static constexpr const QColor kCustomDarkRed{140, 0, 0};
    static constexpr const QColor kCustomLighterDarkRed{230, 0, 0};

    static constexpr const QScalar kTextIndent = 2.;

    static const QString kFontName;

    static constexpr const int kFontSize = 18;
};

}  // namespace rbtree
