#ifndef QGYROFRAME
#define QGYROFRAME

#include <QtCore>

#include "Data/Devices/GyroFrame.h"

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
    double Roll() const { return data.Angle.x(); }
    double Pitch() const { return data.Angle.y(); }
    double Yaw() const { return data.Angle.z(); }

    GyroFrame data;

signals:
    void changed();
};

#endif // QGYROFRAME

