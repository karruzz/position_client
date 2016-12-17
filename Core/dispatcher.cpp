#include "Dispatcher.h"

Dispatcher::Dispatcher(QQuickView *parent)
    : QObject(parent), _parent(parent), _start(0), _end(0), _channel(NULL), _watcher(0), _isNowWatching(false)
{
}

Dispatcher::~Dispatcher()
{
    if (_channel)
    {
        _channel->Close();
        delete _channel;
    }

    if (_watcher){
        _watcher->removePath(_path);
        this->disconnect(_watcher, &QFileSystemWatcher::fileChanged, this, &Dispatcher::fileChanged);
        delete _watcher;
    }
}

void Dispatcher::open(const QString &path)
{
    if (!_channel) _channel = new TFileChannel<GyroFrame>();
    if (!_channel->Open(path)) return;

    _gyroChart = new GyroChartModel(_parent, _channel);
    _gyro3D = new Gyro3DModel(_parent, _channel);

    _start = _channel->StartCounter();
    _end = _channel->EndCounter();

    _isOpened = true;
    _path = path;
    emit opened();
}

void Dispatcher::seek(quint64 counter)
{
    _gyroChart->seek(counter);
    _gyro3D->seek(counter);
}

void Dispatcher::fileChanged(const QString &path)
{
    _gyroChart->seek(_channel->EndCounter());
    _gyro3D->seek(_channel->EndCounter());
}

void Dispatcher::watch()
{
    if (!_isOpened) return;

    if (_isNowWatching){
        _watcher->removePath(_path);
        this->disconnect(_watcher, &QFileSystemWatcher::fileChanged, this, &Dispatcher::fileChanged);
        delete _watcher;
        _isNowWatching = false;
    }
    else{
        _watcher = new QFileSystemWatcher(this);
        this->connect(_watcher, &QFileSystemWatcher::fileChanged, this, &Dispatcher::fileChanged);
        _watcher->addPath(_path);
        _isNowWatching = true;
    }
}
