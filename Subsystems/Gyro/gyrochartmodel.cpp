#include "gyrochartmodel.h"

GyroChartModel::GyroChartModel(QQuickView *parent, IChannel<GyroFrame> *channel)
    : QObject(parent), _channel(channel)
{
    auto root = parent->rootObject();
    auto viewX = root->findChild<Chart*>("gyroChartAngleX");
    QObject::connect(this, &GyroChartModel::AngleXUpdated, viewX, &Chart::setPoints);

    auto viewY = root->findChild<Chart*>("gyroChartAngleY");
    QObject::connect(this, &GyroChartModel::AngleYUpdated, viewY, &Chart::setPoints);

    auto viewZ = root->findChild<Chart*>("gyroChartAngleZ");
    QObject::connect(this, &GyroChartModel::AngleZUpdated, viewZ, &Chart::setPoints);
}

void GyroChartModel::seek(quint64 index)
{
    auto frames = _channel->Read(index, 800);

    QVector<QPointF> pointsX;
    QVector<QPointF> pointsY;
    QVector<QPointF> pointsZ;
    pointsX.reserve(800);
    pointsY.reserve(800);
    pointsZ.reserve(800);
    for (auto i = 0; i < 800; i++)
    {
        pointsX.append( QPointF(i, frames[i].Angle.X) );
        pointsY.append( QPointF(i, frames[i].Angle.Y) );
        pointsZ.append( QPointF(i, frames[i].Angle.Z) );
    }

    emit AngleXUpdated(pointsX);
    emit AngleYUpdated(pointsY);
    emit AngleZUpdated(pointsZ);
}


