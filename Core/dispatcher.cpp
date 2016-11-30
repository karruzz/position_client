#include "dispatcher.h"

Dispatcher::Dispatcher(QObject *parent)
    : QObject(parent), _parent(parent), _count(0), _channel(NULL)
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

    _gyroChart = new GyroChartModel(_parent, _root->findChild<Chart*>("chartObj"), _channel);
    _count = _channel->Count();
    emit opened();
}

void Dispatcher::seek(quint64 index)
{
    _gyroChart->seek(index);
}
