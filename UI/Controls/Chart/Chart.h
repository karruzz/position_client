#ifndef CHART_H
#define CHART_H

#include <QList>
#include <QPointF>
#include <QQuickItem>
#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

class Chart : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY( QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY( qreal min READ min NOTIFY minChanged)
    Q_PROPERTY( qreal max READ max NOTIFY maxChanged)

    Q_PROPERTY( QVector<QPointF> points READ points WRITE setPoints NOTIFY pointsChanged)

public:
    explicit Chart(QQuickItem *parent = 0);

    QColor color() const { return _color; }
    void setColor(QColor c) { _color = c; emit colorChanged(); }

    qreal min() const { return _min; }
    qreal max() const { return _max; }

    QVector<QPointF> points() const { return _points; }
    Q_INVOKABLE void setPoints(const QVector<QPointF> &points);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

signals:
    void minChanged();
    void maxChanged();
    void pointsChanged();
    void colorChanged();

private:
    QVector<QPointF> _points;
    qreal _min;
    qreal _max;
    QColor _color;

    int _samples;
};

#endif // CHART_H


