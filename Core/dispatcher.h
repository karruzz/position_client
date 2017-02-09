/*
 * dispatcher.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include <QtQuick>

#include "channel/tfile_channel.h"
#include "data/devices/gyro_frame.h"
#include "subsystems/gyro/gyro_chart_model.h"
#include "subsystems/gyro/gyro_3d_model.h"

#include <QFileSystemWatcher>

class Dispatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY( quint64 startCounter READ startCounter NOTIFY countChanged)
    Q_PROPERTY( quint64 endCounter READ endCounter NOTIFY countChanged)
    Q_PROPERTY( bool isOpened READ isOpened NOTIFY opened)

public:
    explicit Dispatcher(QQuickView *parent = 0);
    ~Dispatcher();

    quint64 startCounter() const { return _isOpened ? _channel->StartCounter() : 0; }
    quint64 endCounter() const { return _isOpened ? _channel->EndCounter() : 0; }
    bool isOpened() const { return _isOpened; }

signals:
    void opened();
    void countChanged();

public slots:
    void open(const QString &path);
    void seek(quint64 counter);

private:
    QQuickView *_parent;

    GyroChartModel *_gyroChart;
    Gyro3DModel *_gyro3D;

    TFileChannel<GyroFrame> *_channel;

    bool _isOpened;
};

#endif // DISPATCHER_H

