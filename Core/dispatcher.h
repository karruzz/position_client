#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include <QtQuick>

#include "Channel/TFileChannel.h"
#include "Data/Devices/GyroFrame.h"
#include "Subsystems/Gyro/GyroChartModel.h"

class Dispatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY( quint64 count READ count NOTIFY opened)

public:
    explicit Dispatcher(QQuickView *parent = 0);
    ~Dispatcher();

    quint64 count() const { return _count; }

signals:
    void opened();

public slots:
    void open(const QString &path);
    void seek(quint64 index);

private:
    QQuickView *_parent;
    quint64 _count;

    GyroChartModel *_gyroChart;
    TFileChannel<GyroFrame> *_channel;
};

#endif // DISPATCHER_H

