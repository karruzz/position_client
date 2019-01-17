/*
 * chart.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef CHART_H
#define CHART_H

#include <QList>
#include <QPointF>
#include <QQuickItem>
#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

class Chart : public QQuickItem
{
	Q_OBJECT

	Q_PROPERTY( QColor color READ color WRITE setColor NOTIFY color_changed)

	Q_PROPERTY( qreal minY READ minY NOTIFY boundary_changed)
	Q_PROPERTY( qreal maxY READ maxY NOTIFY boundary_changed)

	Q_PROPERTY( qint64 minX READ minX NOTIFY boundary_changed)
	Q_PROPERTY( qint64 maxX READ maxX NOTIFY boundary_changed)
public:
	explicit Chart(QQuickItem *parent = 0);

	QColor color() const { return _color; }
	void setColor(QColor c) { _color = c; emit color_changed(); }

	qreal minY() const { return _minY; }
	qreal maxY() const { return _maxY; }

	quint64 minX() const { return _minX; }
	quint64 maxX() const { return _maxX; }

public slots:
	void append_points(const QVector<QPointF> &points, float minY, float maxY, float minX, float maxX );

protected:
	QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

signals:
	void boundary_changed();
	void color_changed();

private:
	QVector<QPointF> _points;
	QColor _color;
	qreal _minY, _maxY;
	qint64 _minX, _maxX;
};

#endif // CHART_H


