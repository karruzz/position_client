#ifndef GYRO3DMODEL_H
#define GYRO3DMODEL_H

#include <QtCore>
#include <QtQuick>

#include "channel/ichannel.h"
#include "data/devices/gyro_frame.h"
#include "ui/controls/3d/projection.h"

class Gyro3DModel : public QObject
{
    Q_OBJECT

    public:
        explicit Gyro3DModel(QQuickView *parent = 0, IChannel<GyroFrame> *channel = 0);

    void seek(quint64 index);

    signals:
        void PointUpdated(const GyroFrame &points);

    private:
        IChannel<GyroFrame> *_channel;
        quint64 _count;
};

#endif // GYRO3DMODEL_H

