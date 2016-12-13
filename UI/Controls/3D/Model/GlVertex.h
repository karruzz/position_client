#ifndef GLVERTEX_H
#define GLVERTEX_H

#include <QVector3D>

struct GlVertex
{
    QVector3D Point;
    QVector3D Color;

    GlVertex() {}

    GlVertex(QVector3D point, QVector3D color) : Point(point), Color (color) {}
};

#endif // GLVERTEX_H

