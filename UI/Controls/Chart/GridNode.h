#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>


class GridNode : public QSGGeometryNode
{
    public:
        GridNode();

        void setRect(const QRectF &bounds);
        void alloc();

    private:
        QSGGeometry _geometry;
};

#endif // GRIDNODE_H

