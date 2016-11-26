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

    Q_PROPERTY( qreal min READ min NOTIFY minChanged)
    Q_PROPERTY( qreal max READ max NOTIFY maxChanged)

    Q_PROPERTY( QVector<QPointF> points READ points WRITE setPoints NOTIFY changed)

public:
    explicit Chart(QQuickItem *parent = 0);

    qreal min() const { return _min; }
    qreal max() const { return _max; }

    QVector<QPointF> points() const { return _points; }
    Q_INVOKABLE void setPoints(const QVector<QPointF> &points);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

signals:
    void minChanged();
    void maxChanged();
    void changed();

private:
    QVector<QPointF> _points;
    qreal _min;
    qreal _max;

    int _samples;
};

#endif // CHART_H


