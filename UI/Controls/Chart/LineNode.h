#ifndef LINENODE_H
#define LINENODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QVector2D>

class LineNode : public QSGGeometryNode
{
    public:
        LineNode(int size, const QColor &color);

        void setPoints(const QRectF &bounds, const QVector<QPointF> &points,
                       float minY, float maxY, quint64 minX, quint64 maxX);

        void alloc(int size);

    private:
        QSGGeometry _geometry;
};

#endif // LINENODE_H

