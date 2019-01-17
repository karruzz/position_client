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
Q_PROPERTY(QGyroFrame* frame READ frame NOTIFY frame_changed)

public:
	Projection(QQuickItem *parent = 0);

	QGyroFrame* frame() const { return _frame; }

	void wheelEvent(QWheelEvent *event);
	Q_INVOKABLE void mouse_dragged(Qt::MouseButtons but, int dx, int dy);

signals:
	void frame_changed();

public slots:
	void sync();
	void set_position(GyroFrame p);

private slots:
	void handle_window_changed(QQuickWindow *win);

private:
	QMatrix4x4 view_matrix();

	Renderer _renderer;

	// current frame
	QGyroFrame *_frame;

	// camera
	QVector4D _camX, _camY, _camZ, _cam_pos;
	QQuaternion _cam_quat;
};

#endif // PROJECTION_H

