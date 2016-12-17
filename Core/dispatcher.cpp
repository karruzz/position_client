#include "Dispatcher.h"

Dispatcher::Dispatcher(QQuickView *parent)
    : QObject(parent), _parent(parent), _start(0), _end(0), _channel(NULL)
{
}

Dispatcher::~Dispatcher()
{
    if (!_channel)  return;
    _channel->Close();
    delete _channel;
}

void Dispatcher::open(const QString &path)
{
    if (!_channel) _channel = new TFileChannel<GyroFrame>();
    if (!_channel->Open(path)) return;

    _gyroChart = new GyroChartModel(_parent, _channel);
    _gyro3D = new Gyro3DModel(_parent, _channel);

    _start = _channel->StartCounter();
    _end = _channel->EndCounter();
    emit opened();
}

void Dispatcher::seek(quint64 counter)
{
    _gyroChart->seek(counter);
    _gyro3D->seek(counter);
}
