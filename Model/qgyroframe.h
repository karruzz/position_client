#ifndef QGYROFRAME
#define QGYROFRAME

#include <QtCore>

#include "Data/gyroframe.h"

class QGyroFrame : public QObject
{
    Q_OBJECT

    Q_PROPERTY( double Roll  READ getRoll)
    Q_PROPERTY( double Pitch READ getPitch)
    Q_PROPERTY( double Yaw   READ getYaw)

public:
    explicit QGyroFrame(QObject *parent = 0);

    double getRoll();
    double getPitch();
    double getYaw();

    GyroFrame frame;

};

#endif // QGYROFRAME

