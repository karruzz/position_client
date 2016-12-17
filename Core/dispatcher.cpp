#include "Dispatcher.h"

Dispatcher::Dispatcher(QQuickView *parent)
    : QObject(parent), _parent(parent), _channel(NULL)
{
}

Dispatcher::~Dispatcher()
{
    if (_channel)
    {
        _channel->Close();
        delete _channel;
    }
}

void Dispatcher::open(const QString &path)
{
    if (!_channel) _channel = new TFileChannel<GyroFrame>();
    if (!_channel->Open(path)) return;

    _gyroChart = new GyroChartModel(_parent, _channel);
    _gyro3D = new Gyro3DModel(_parent, _channel);

    _isOpened = true;
    emit opened();
}

void Dispatcher::seek(quint64 counter)
{
    _channel->Count();
    _gyroChart->seek(counter);
    _gyro3D->seek(counter);
}

void Dispatcher::fileChanged(const QString &path)
{
    _gyroChart->seek(_channel->EndCounter());
    _gyro3D->seek(_channel->EndCounter());
}
