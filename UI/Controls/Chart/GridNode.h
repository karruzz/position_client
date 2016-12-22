#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QVector2D>


class GridNode : public QSGGeometryNode
{
    public:
        GridNode( const QColor color, const QVector2D colsRows);

        void setRect(const QRectF &bounds);
        void alloc();

    private:
        QSGGeometry _geometry;
        QVector2D _colsRows;
        int _verticesCount;
};

#endif // GRIDNODE_H

