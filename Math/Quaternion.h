#ifndef QUATERNION_H
#define QUATERNION_H

#include <QtGui/qvector3d.h>
#include <QtGui/qvector4d.h>

#include <QtMath>

class Quaternion
{
    public:
        Quaternion();
        Quaternion(float scalar, float xpos, float ypos, float zpos);

        float x() const { return xp; }
        float y() const { return yp; }
        float z() const { return zp; }
        float a() const { return ap; }

        void setX(float x) { xp = x; }
        void setY(float y) { yp = y; }
        void setZ(float z) { zp = z; }
        void setA(float a) { ap = a; }

        static Quaternion Unit(float angle, float x, float y, float z);

        QVector3D vector() const;
        float length() const;
        float lengthSqr() const;
        Quaternion conjugate() const;
        Quaternion derivative(float wx, float wy, float wz) const;

        Quaternion &operator+=(const Quaternion &quaternion);

        friend inline const Quaternion operator+(const Quaternion &q1, const Quaternion &q2);
        friend inline const Quaternion operator*(float factor, const Quaternion &quaternion);
        friend inline const Quaternion operator*(const Quaternion &quaternion, float factor);
        friend inline const Quaternion operator*(const Quaternion &q1, const Quaternion& q2);
        friend inline const Quaternion operator/(const Quaternion &quaternion, float divisor);

    private:
        float ap, xp, yp, zp;
};

inline Quaternion::Quaternion() : ap(1.0f), xp(0.0f), yp(0.0f), zp(0.0f) {}

inline Quaternion::Quaternion(float a, float x, float y, float z) : ap(a), xp(x), yp(y), zp(z) {}

inline QVector3D Quaternion::vector() const
{
    return QVector3D(xp, yp, zp);
}

inline float Quaternion::length() const
{
    return ap * ap + xp * xp + yp * yp + zp * zp;
}

inline float Quaternion::lengthSqr() const
{
    return qSqrt(ap * ap + xp * xp + yp * yp + zp * zp);
}

inline Quaternion Quaternion::conjugate() const
{
    return Quaternion(ap, -xp, -yp, -zp);
}

inline Quaternion Quaternion::derivative(float wx, float wy, float wz) const
{
    auto q = *this;
    return 0.5 * q * Quaternion(0, wx, wy, wz);
}

inline Quaternion &Quaternion::operator+=(const Quaternion &quaternion)
{
    xp += quaternion.xp;
    yp += quaternion.yp;
    zp += quaternion.zp;
    ap += quaternion.ap;
    return *this;
}

inline const Quaternion operator+(const Quaternion &q1, const Quaternion &q2)
{
    return Quaternion(q1.ap + q2.ap, q1.xp + q2.xp, q1.yp + q2.yp, q1.zp + q2.zp);
}

inline const Quaternion operator/(const Quaternion &quaternion, float divisor)
{
    return Quaternion(quaternion.ap / divisor, quaternion.xp / divisor, quaternion.yp / divisor, quaternion.zp / divisor);
}

inline const Quaternion operator*(float factor, const Quaternion &quaternion)
{
    return Quaternion(quaternion.ap * factor, quaternion.xp * factor, quaternion.yp * factor, quaternion.zp * factor);
}

inline const Quaternion operator*(const Quaternion &quaternion, float factor)
{
    return Quaternion(quaternion.ap * factor, quaternion.xp * factor, quaternion.yp * factor, quaternion.zp * factor);
}

inline const Quaternion operator*(const Quaternion &q1, const Quaternion& q2)
{
    float a = q1.ap * q2.ap - q1.xp * q2.xp - q1.yp * q2.yp - q1.zp * q2.zp;
    float x = q1.ap * q2.xp + q1.xp * q2.ap + q1.yp * q2.zp - q1.zp * q2.yp;
    float y = q1.ap * q2.yp - q1.xp * q2.zp + q1.yp * q2.ap + q1.zp * q2.xp;
    float z = q1.ap * q2.zp + q1.xp * q2.yp - q1.yp * q2.xp + q1.zp * q2.ap;

    return Quaternion(a, x, y, z);
}

#endif // QUATERNION_H


