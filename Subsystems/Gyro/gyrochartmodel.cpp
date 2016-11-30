#include "gyrochartmodel.h"

GyroChartModel::GyroChartModel(QObject *parent, Chart *view, IChannel<GyroFrame> *channel)
    : QObject(parent), _channel(channel)
{
    QObject::connect(this, &GyroChartModel::AngleXUpdated, view, &Chart::setPoints);
}

void GyroChartModel::seek(quint64 index)
{
    auto frames = _channel->Read(index, 800);
    QVector<QPointF> points;
    points.reserve(800);
    for (auto i = 0; i < 800; i++)
        points.append( QPointF(i, frames[i].Angle.X * 1000 + 200) );

    emit AngleXUpdated(points);
}

