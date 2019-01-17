/*
 * gl_vertex.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef GLVERTEX_H
#define GLVERTEX_H

#include <QVector3D>
#include <QColor>

struct GlVertex
{
	QVector3D Point;
	QVector3D Color;

	GlVertex() {}

	GlVertex(QVector3D point, QVector3D color)
		: Point(point)
		, Color (color)
	{}

	GlVertex(QVector3D point, QColor color)
		: Point(point)
		, Color(QVector3D(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f))
	{}

	GlVertex(float x, float y, float z, QColor color)
		: GlVertex(QVector3D(x, y, z), color)
	{}
};

#endif // GLVERTEX_H

