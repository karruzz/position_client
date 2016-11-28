#ifndef GYROFRAME
#define GYROFRAME

#include <QDataStream>

#include "Data/iframe.h"
#include "Math/point3d.h"

class GyroFrame : public IFrame
{
    public:
      //  quint64 TimeStamp;
        Point3d Acs;
        Point3d Omega;
        Point3d Angle;

        inline int Size() override final { return 80; }

        friend QDataStream &operator >>(QDataStream &out, GyroFrame &frame);
};

inline QDataStream &operator >>(QDataStream &out, GyroFrame &frame)
{
    out >> frame.Counter;

    out >> frame.Angle.X;
    out >> frame.Angle.Y;
    out >> frame.Angle.Z;

    out >> frame.Omega.X;
    out >> frame.Omega.Y;
    out >> frame.Omega.Z;

    out >> frame.Acs.X;
    out >> frame.Acs.Y;
    out >> frame.Acs.Z;

    return out;
}

#endif // GYROFRAME


