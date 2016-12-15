#ifndef GYROFRAME
#define GYROFRAME

#include <QDataStream>
#include <QVector3D>

#include "Data/IFrame.h"

class GyroFrame : public IFrame
{
    public:
      //  quint64 TimeStamp;
        QVector3D Acs;
        QVector3D Omega;
        QVector3D Angle;

        inline int Size() override final { return 80; }

        friend QDataStream &operator >>(QDataStream &out, GyroFrame &frame);
};

inline QDataStream &operator >>(QDataStream &out, GyroFrame &frame)
{
    out >> frame.Counter;

    out >> frame.Angle;
    out >> frame.Omega;
    out >> frame.Acs;

    return out;
}

#endif // GYROFRAME


