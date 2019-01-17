/*
 * grid_node.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "grid_node.h"

#include <QSGFlatColorMaterial>

GridNode::GridNode(QColor color, int cols, int rows)
	: _geometry(QSGGeometry::defaultAttributes_Point2D(), cols*rows + 13)
	, _cols(cols)
	, _rows(rows)
{
	_vertices_count = _cols * _rows + 12;
	_geometry.setLineWidth(1);
	_geometry.setDrawingMode(GL_LINES);
	setGeometry(&_geometry);

	QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
	material->setColor(color);
	setMaterial(material);
	setFlag(QSGNode::OwnsMaterial);
	markDirty(QSGNode::DirtyMaterial);
}

void GridNode::alloc()
{
	_geometry.allocate(_vertices_count);
}

void GridNode::set_rect(const QRectF &bounds)
{
	QSGGeometry::Point2D *vertices = _geometry.vertexDataAsPoint2D();

	float bottom = bounds.height();
	float step = (bottom - 2) / _rows;
	float center = bottom / 2;
	int i = 0;
	int position = 0;

	while (center + i * step < bottom) {
		vertices[position++].set(0, center + i * step);
		vertices[position++].set(bounds.width(), center + i * step);
		vertices[position++].set(0, center - i * step);
		vertices[position++].set(bounds.width(), center - i * step);
		i++;
	}

	step = (bounds.width()- 2) / _cols;
	center = bounds.width() / 2;
	i = 0;

	while (center + i * step < bounds.width()) {
		vertices[position++].set(center + i * step, 0);
		vertices[position++].set(center + i * step, bottom);
		vertices[position++].set(center - i * step, 0);
		vertices[position++].set(center - i * step, bottom);
		i++;
	}

	while (position < _vertices_count) {
		vertices[position++].set(0, 0);
	}

	markDirty(QSGNode::DirtyGeometry);
}
