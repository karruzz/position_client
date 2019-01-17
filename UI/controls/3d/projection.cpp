/*
 * projection.cpp
 *
 *  Created on: Nov 8, 2018
 *  Copyright © 2018-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "projection.h"
#include "core/math.h"

#include <QtQuick/qquickwindow.h>
#include <QtMath>

Projection::Projection(QQuickItem *parent)
	:  QQuickItem(parent)
	, _renderer(parent)
	, _frame(new QGyroFrame(this))
	, _camX(1, 0, 0, 0), _camY(0, 1, 0, 0), _camZ(0, 0, 1, 0)
	, _cam_pos(0, -2, 0, 0)
	, _cam_quat(1, 0, 0, 0)
{
	connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handle_window_changed(QQuickWindow*)));
	// init position
	_cam_pos = QVector4D(-0.361009872, -1.0, 0.563965559, 0);
	_cam_quat = QQuaternion(0.340076178, 0.0609764457, 0.165994048, 0.925754309);
}

void Projection::set_position(GyroFrame p)
{
	_frame->data = p;
	emit _frame->changed();

	_renderer.set_cube_rotate_matrix(Math::dcm(p.Angle));
	if (window()) window()->update();
}

void Projection::wheelEvent(QWheelEvent *event)
{
	_cam_pos -= _camY * event->angleDelta().y() / 400.0;

	_renderer.set_view_matrix(view_matrix());
	if (window()) window()->update();

	QQuickItem::wheelEvent(event);
}

QMatrix4x4 Projection::view_matrix()
{
	QMatrix4x4 r = Math::dcm(_cam_quat);
	_camX = r.column(0);
	_camY = r.column(1);
	_camZ = r.column(2);

	QMatrix4x4 vm;
	vm.setRow(0, -_camX);
	vm.setRow(1,  _camZ);
	vm.setRow(2,  _camY);
	vm.setRow(3, r.column(3));

	vm.translate(-_cam_pos.toVector3D());

	return vm;
}

void Projection::mouse_dragged(Qt::MouseButtons but, int dx, int dy)
{
	if (dx != 0 || dy != 0) {
		if (but == Qt::LeftButton) {
			_cam_quat += Math::derivative(_cam_quat, dy / 160.0, 0, 0);
			_cam_quat.normalize();
			_cam_quat = Math::unit(-dx / 160.0, 0, 0, 1) * _cam_quat;
		}
		if (but == Qt::RightButton) {
			_cam_pos -= _camX * dx / 80.0;
			_cam_pos -= _camZ * dy / 80.0;
		}

		_renderer.set_view_matrix(view_matrix());
		if (window()) window()->update();
	}
}

void Projection::handle_window_changed(QQuickWindow *win)
{
	if (win) {
		connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
//		connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
		// If we allow QML to do the clearing, they would clear what we paint
		// and nothing would show.
		win->setClearBeforeRendering(false);
	}
}

void Projection::sync()
{
	static bool renderer_inited = false;
	if (!renderer_inited) {
		_renderer.init();
		connect(window(), SIGNAL(beforeRendering()), &_renderer, SLOT(paint()), Qt::DirectConnection);
		renderer_inited = true;
	}

	_renderer.set_viewport_size(window()->size() * window()->devicePixelRatio());
	_renderer.set_view_matrix(view_matrix());
}


