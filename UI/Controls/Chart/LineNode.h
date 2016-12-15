#ifndef LINENODE_H
#define LINENODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>

class LineNode : public QSGGeometryNode
{
    public:
        LineNode(int size, const QColor &color);
        void setPoints(const QRectF &bounds, const QVector<QPointF> &points,
                       float max, float min);

        void alloc(int size);

    private:
        QSGGeometry _geometry;
};

#endif // LINENODE_H

