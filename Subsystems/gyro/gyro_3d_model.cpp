#include "gyro_3d_model.h"

Gyro3DModel::Gyro3DModel(QQuickView *parent, IChannel<GyroFrame> *channel)
    : QObject(parent), _channel(channel)
{
    auto root = parent->rootObject();
    auto view = root->findChild<Projection*>("gyro3D");
    QObject::connect(this, &Gyro3DModel::PointUpdated, view, &Projection::setPosition);
}

void Gyro3DModel::seek(quint64 counter)
{
    auto index = _channel->Index(counter);
    auto frame = _channel->Read(index);
    emit PointUpdated(frame);
}

