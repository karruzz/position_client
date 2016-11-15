#ifndef GYROFRAME
#define GYROFRAME

#include "iframe.h"
#include "Math/point3d.h"

class GyroFrame : public IFrame
{
    public:
        long TimeStamp;
        Point3d Acs;
        Point3d Omega;
        Point3d Angle;

        inline void Deserialize(QByteArray bytes) {
            *this = *(reinterpret_cast<GyroFrame*>(bytes.data()));
        }
};

#endif // GYROFRAME

