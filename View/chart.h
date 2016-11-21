#ifndef CHART_H
#define CHART_H

#include <QList>
#include <QPointF>
#include <QQuickItem>

class Chart : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY( qreal min READ min NOTIFY minChanged)
    Q_PROPERTY( qreal max READ max NOTIFY maxChanged)

    Q_PROPERTY( QQmlListProperty<QPointF> points READ points NOTIFY changed)

public:
    explicit Chart(QQuickItem *parent = 0);

    qreal min() const { return _min; }
    qreal max() const { return _max; }
    QQmlListProperty<QPointF> points() { return new QQmlListProperty<QPointF>(0, _points); }

    Q_INVOKABLE void addData(const QList<qreal> &data);

signals:
    void minChanged();
    void maxChanged();
    void changed();

private:
    QList<QPointF *> _points;
    qreal _min;
    qreal _max;

    int _samples;
};

#endif // CHART_H


