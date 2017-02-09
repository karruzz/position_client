/*
 * dispatcher.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "dispatcher.h"

Dispatcher::Dispatcher(QQuickView *parent)
    : QObject(parent), _parent(parent), _channel(new TFileChannel<GyroFrame>()), _isOpened(false)
{
}

Dispatcher::~Dispatcher()
{
    if (_isOpened)
        _channel->Close();
}

void Dispatcher::open(const QString &path)
{
    if (_isOpened){
        _channel->Close();
        delete _gyroChart;
        delete _gyro3D;

        _isOpened = false;
    }

    if (!_channel->Open(path)) return;

    _channel->Count();
    _gyroChart = new GyroChartModel(_parent, _channel);
    _gyro3D = new Gyro3DModel(_parent, _channel);

    _isOpened = true;
    emit opened();
    emit countChanged();
}

void Dispatcher::seek(quint64 counter)
{
    _channel->Count();

    _gyroChart->seek(counter);
    _gyro3D->seek(counter);
}

