#include "Quaternion.h"

static Quaternion q = Quaternion::Unit(1, 0, 0, 0);

inline Quaternion Quaternion::Unit(float angle, float x, float y, float z)
{
    float norm = 1.0 / qSqrt(x*x+y*y+z*z);
    x *= norm;
    y *= norm;
    z *= norm;

    float cos = qCos(angle / 2.0);
    float sin = qSin(angle / 2.0);
    return Quaternion(cos, sin * x, sin * y, sin * z);
}
