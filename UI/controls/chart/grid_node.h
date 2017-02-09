/*
 * grid_node.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

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

