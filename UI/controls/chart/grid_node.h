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
	GridNode(const QColor color, int cols, int rows);

	void set_rect(const QRectF &bounds);
	void alloc();

private:
	QSGGeometry _geometry;
	int _cols, _rows;
	int _vertices_count;
};

#endif // GRIDNODE_H

