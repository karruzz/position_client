#ifndef QGYROFRAME
#define QGYROFRAME

#include <QtCore>

#include "Data/Devices/gyroframe.h"

class QGyroFrame : public QObject
{
    Q_OBJECT

    Q_PROPERTY( quint64 Time  READ Time NOTIFY changed)
    Q_PROPERTY( double Roll  READ Roll NOTIFY changed)
    Q_PROPERTY( double Pitch READ Pitch NOTIFY changed)
    Q_PROPERTY( double Yaw   READ Yaw NOTIFY changed)

public:
    explicit QGyroFrame(QObject *parent = 0);

    quint64 Time() const { return data.Counter; }
    double Roll() const { return data.Angle.X; }
    double Pitch() const { return data.Angle.Y; }
    double Yaw() const { return data.Angle.Z; }

    GyroFrame data;

signals:
    void changed();
};

#endif // QGYROFRAME

