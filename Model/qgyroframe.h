#ifndef QGYROFRAME
#define QGYROFRAME

#include <QtCore>

#include "Data/Devices/gyroframe.h"

class QGyroFrame : public QObject
{
    Q_OBJECT

    Q_PROPERTY( double Roll  READ getRoll NOTIFY changed)
    Q_PROPERTY( double Pitch READ getPitch NOTIFY changed)
    Q_PROPERTY( double Yaw   READ getYaw NOTIFY changed)

public:
    explicit QGyroFrame(QObject *parent = 0);

    double getRoll();
    double getPitch();
    double getYaw();

    GyroFrame data;

signals:
    void changed();
};

#endif // QGYROFRAME

