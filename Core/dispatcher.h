#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include <QtQuick>

#include "Channel/TFileChannel.h"
#include "Data/Devices/GyroFrame.h"
#include "Subsystems/Gyro/GyroChartModel.h"
#include "Subsystems/Gyro/Gyro3DModel.h"

class Dispatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY( quint64 start READ start NOTIFY opened)
    Q_PROPERTY( quint64 end READ end NOTIFY opened)

public:
    explicit Dispatcher(QQuickView *parent = 0);
    ~Dispatcher();

    quint64 start() const { return _start; }
    quint64 end() const { return _end; }

signals:
    void opened();

public slots:
    void open(const QString &path);
    void seek(quint64 counter);

private:
    QQuickView *_parent;

    quint64 _start;
    quint64 _end;

    GyroChartModel *_gyroChart;
    Gyro3DModel *_gyro3D;
    TFileChannel<GyroFrame> *_channel;
};

#endif // DISPATCHER_H

