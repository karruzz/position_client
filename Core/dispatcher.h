#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include <QtQuick>

#include "Channel/tfilechannel.h"
#include "Data/Devices/gyroframe.h"
#include "Subsystems/Gyro/gyrochartmodel.h"

class Dispatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY( quint64 count READ count NOTIFY opened)

public:
    explicit Dispatcher(QObject *parent = 0);
    ~Dispatcher();

    void SetRoot(QQuickItem *root) { _root = root; }
    quint64 count() const { return _count; }

signals:
    void opened();

public slots:
    void open(const QString &path);
    void seek(quint64 index);

private:
    QObject *_parent;
    quint64 _count;
    QQuickItem *_root;

    GyroChartModel *_gyroChart;
    TFileChannel<GyroFrame> *_channel;
};

#endif // DISPATCHER_H

