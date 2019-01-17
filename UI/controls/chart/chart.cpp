/*
 * chart.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include <ui/controls/chart/chart.h>
#include "line_node.h"
#include "grid_node.h"

Chart::Chart(QQuickItem *parent)
	: QQuickItem(parent)
	, _color("red")
	, _minY(-0.1), _maxY(0.1)
{
	setFlag(ItemHasContents, true);
}

void Chart::append_points(const QVector<QPointF> &points, float minY, float maxY, float minX, float maxX)
{
	if (points.isEmpty()) return;
	_points = points;

	_minY = minY;
	_maxY = maxY;

	_minX = minX;
	_maxX = maxX;

	emit boundary_changed();
	update();
}

class ChartNode : public QSGNode
{
public:
	LineNode *line;
	GridNode *gridRed;
	GridNode *gridGray;
};

QSGNode *Chart::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
	ChartNode *n = static_cast<ChartNode *>(oldNode);

	QRectF rect = boundingRect();

	if (rect.isEmpty()) {
		delete n;
		return 0;
	}

	if (!n) {
		n = new ChartNode();
		n->gridRed = new GridNode(QColor(0x40, 0, 0), 5, 3);
		n->gridGray = new GridNode(QColor(0x20, 0x20, 0x20), 20, 6);
		n->line = new LineNode(_points.size()+1, _color);

		n->appendChildNode(n->gridGray);
		n->appendChildNode(n->gridRed);
		n->appendChildNode(n->line);
	} else {
		n->line->alloc(_points.size());
		n->gridRed->alloc();
		n->gridGray->alloc();
	}

	n->gridGray->set_rect(rect);
	n->gridRed->set_rect(rect);
	n->line->set_points(rect, _points, _minY, _maxY, _minX, _maxX);

	return n;
}


