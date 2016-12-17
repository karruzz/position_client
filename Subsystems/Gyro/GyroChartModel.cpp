#include "GyroChartModel.h"

GyroChartModel::GyroChartModel(QQuickView *parent, IChannel<GyroFrame> *channel)
    : QObject(parent), _channel(channel)
{
    auto root = parent->rootObject();
    auto viewX = root->findChild<Chart*>("gyroChartAngleX");
    QObject::connect(this, &GyroChartModel::AngleXUpdated, viewX, &Chart::setPoints);
    QObject::connect(this, &GyroChartModel::SetLeft, viewX, &Chart::setLeft);
    QObject::connect(this, &GyroChartModel::SetRight, viewX, &Chart::setRight);

    auto viewY = root->findChild<Chart*>("gyroChartAngleY");
    QObject::connect(this, &GyroChartModel::AngleYUpdated, viewY, &Chart::setPoints);
    QObject::connect(this, &GyroChartModel::SetLeft, viewY, &Chart::setLeft);
    QObject::connect(this, &GyroChartModel::SetRight, viewY, &Chart::setRight);

    auto viewZ = root->findChild<Chart*>("gyroChartAngleZ");
    QObject::connect(this, &GyroChartModel::AngleZUpdated, viewZ, &Chart::setPoints);
    QObject::connect(this, &GyroChartModel::SetLeft, viewZ, &Chart::setLeft);
    QObject::connect(this, &GyroChartModel::SetRight, viewZ, &Chart::setRight);
}

void GyroChartModel::seek(quint64 counter)
{
    auto counterLeft = counter - Scale_ns;
    auto counterRight = counter + Scale_ns;

    auto indexLeft = _channel->Index(counterLeft);
    auto indexRight = _channel->Index(counterRight);
    auto count = indexRight - indexLeft;

    auto frames = _channel->Read(indexLeft, count);

    QVector<QPointF> pointsX;
    QVector<QPointF> pointsY;
    QVector<QPointF> pointsZ;
    pointsX.reserve(count);
    pointsY.reserve(count);
    pointsZ.reserve(count);
    for (auto i = 0; i < count; i++)
    {
        pointsX.append( QPointF(frames[i].Counter, frames[i].Angle.x()) );
        pointsY.append( QPointF(frames[i].Counter, frames[i].Angle.y()) );
        pointsZ.append( QPointF(frames[i].Counter, frames[i].Angle.z()) );
    }

    emit SetLeft(counterLeft);
    emit SetRight(counterRight);
    emit AngleXUpdated(pointsX);
    emit AngleYUpdated(pointsY);
    emit AngleZUpdated(pointsZ);
}


