#ifndef GYROFRAME
#define GYROFRAME

#include <QDataStream>

#include "Data/iframe.h"
#include "Math/point3d.h"

class GyroFrame
{
    public:
        quint64 TimeStamp;
        Point3d Acs;
        Point3d Omega;
        Point3d Angle;

        inline int Size() { return 80; }

        friend QDataStream &operator >>(QDataStream &out, GyroFrame &frame);
};

inline QDataStream &operator >>(QDataStream &out, GyroFrame &frame)
{
    out >> frame.TimeStamp;

    out >> frame.Acs.X;
    out >> frame.Acs.Y;
    out >> frame.Acs.Z;

    out >> frame.Omega.X;
    out >> frame.Omega.Y;
    out >> frame.Omega.Z;

    out >> frame.Angle.X;
    out >> frame.Angle.Y;
    out >> frame.Angle.Z;

    return out;
}

#endif // GYROFRAME


