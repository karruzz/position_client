#ifndef GYROCHARTMODEL_H
#define GYROCHARTMODEL_H

#include <QtCore>
#include <QtQuick>

#include "Channel/ichannel.h"
#include "Data/Devices/gyroframe.h"
#include "View/chart.h"

class GyroChartModel : public QObject
{
    Q_OBJECT

    public:
        explicit GyroChartModel(QQuickView *parent = 0, IChannel<GyroFrame> *channel = 0);

    void seek(quint64 index);

    signals:
        void AngleXUpdated(const QVector<QPointF> &points);
        void AngleYUpdated(const QVector<QPointF> &points);
        void AngleZUpdated(const QVector<QPointF> &points);

    private:
        IChannel<GyroFrame> *_channel;
        quint64 _count;
};

#endif // GYROCHARTMODEL_H

