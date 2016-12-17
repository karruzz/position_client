#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include <QtQuick>

#include "Channel/TFileChannel.h"
#include "Data/Devices/GyroFrame.h"
#include "Subsystems/Gyro/GyroChartModel.h"
#include "Subsystems/Gyro/Gyro3DModel.h"

#include <QFileSystemWatcher>

class Dispatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY( quint64 startCounter READ startCounter NOTIFY opened)
    Q_PROPERTY( quint64 endCounter READ endCounter NOTIFY opened)
    Q_PROPERTY( bool isOpened READ isOpened NOTIFY opened)

public:
    explicit Dispatcher(QQuickView *parent = 0);
    ~Dispatcher();

    quint64 startCounter() const { return _channel ? _channel->StartCounter() : 0; }
    quint64 endCounter() const { return _channel ? _channel->EndCounter() : 0; }
    bool isOpened() const { return _isOpened; }

signals:
    void opened();

public slots:
    void open(const QString &path);
    void seek(quint64 counter);

    void fileChanged(const QString &path);

private:
    QQuickView *_parent;

    GyroChartModel *_gyroChart;
    Gyro3DModel *_gyro3D;

    TFileChannel<GyroFrame> *_channel;

    bool _isOpened;
};

#endif // DISPATCHER_H

