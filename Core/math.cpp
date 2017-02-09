/*
 * math.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "math.h"
#include <QtMath>

QQuaternion q = Math::derivative(QQuaternion(1,0,0,0), 0, 0, 0);

QQuaternion Math::derivative(QQuaternion q, float wx, float wy, float wz)
{
    return 0.5 * q * QQuaternion(0, wx, wy, wz);
}

QQuaternion Math::unit(float angle, float x, float y, float z)
{
    float norm = 1.0 / qSqrt(x*x+y*y+z*z);
    x *= norm;
    y *= norm;
    z *= norm;

    float cos = qCos(angle / 2.0);
    float sin = qSin(angle / 2.0);
    return QQuaternion(cos, sin * x, sin * y, sin * z);
}

QMatrix4x4 Math::dcm(QQuaternion q)
{
    QMatrix4x4 m;
    float x = q.x();
    float y = q.y();
    float z = q.z();
    float a = q.scalar();

    const float s = 2.0;
    m.setColumn(0, QVector4D( 1.0 - s * (y * y + z * z),
                              s * (x * y + z * a),
                              s * (x * z - y * a),
                              0.0 ));

    m.setColumn(1, QVector4D( s * (x * y - z * a),
                              1.0 - s * (x * x + z * z),
                              s * (z * y + x * a),
                              0.0 ));

    m.setColumn(2, QVector4D( s * (x * z + y * a),
                              s * (y * z - x * a),
                              1.0 - s * (x * x + y * y),
                              0.0 ));

    m.setColumn(3, QVector4D( 0.0, 0.0, 0.0, 1.0 ));
    return m;
}

QMatrix4x4 Math::dcm(QVector3D euler)
{
    QMatrix4x4 r;
    float xc = qCos(euler.x());
    float xs = qSin(euler.x());

    float yc = qCos(euler.y());
    float ys = qSin(euler.y());

    float zc = qCos(euler.z());
    float zs = qSin(euler.z());

    r.setColumn(0, QVector4D(yc*zc, yc*zs, -ys, 0.0));
    r.setColumn(1, QVector4D(-xc*zs+xs*ys*zc, xc*zc+xs*ys*zs, xs*yc, 0.0));
    r.setColumn(2, QVector4D(xs*zs+xc*ys*zc, -xs*zc+xc*ys*zs, xc*yc, 0.0));
    r.setColumn(3, QVector4D(0.0, 0.0, 0.0, 1.0));

    return r;
}
