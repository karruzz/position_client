/*
 * projection.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef PROJECTION_H
#define PROJECTION_H

#include <QVector>

#include <QtQuick/QQuickItem>

#include "data/devices/gyro_frame.h"

#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector3D>

#include "renderer.h"
#include "data/devices/qgyro_frame.h"

class Projection : public QQuickItem
{
Q_OBJECT
Q_PROPERTY( QGyroFrame *Frame READ Frame NOTIFY frameChanged)

public:
	Projection(QQuickItem *parent = 0);

	QGyroFrame *Frame() const { return _frame; }

	void wheelEvent(QWheelEvent *event);
	Q_INVOKABLE void mouse_dragged(Qt::MouseButtons but, int dx, int dy);

signals:
	void frameChanged();

public slots:
	void sync();
	void setPosition(GyroFrame p);

private slots:
	void handleWindowChanged(QQuickWindow *win);

private:
	QMatrix4x4 vMatrix();

	// todo: remove pointer
	Renderer _renderer;

	// current frame
	GyroFrame _position;
	QGyroFrame *_frame;

	// camera
	QVector4D _camX, _camY, _camZ, _camPos;
	QQuaternion _qCamera;
	bool _dragAngle;
	bool _dragPosition;

	// cube
	GlModel *_cube;
};

#endif // PROJECTION_H

