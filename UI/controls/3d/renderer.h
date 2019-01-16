/*
 * renderer.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>

#include <QScopedPointer>

#include "model/gl_model.h"

class Renderer  : public QObject, protected QOpenGLFunctions
{
Q_OBJECT
public:
	Renderer(QObject* parent = 0)
		: QObject(parent)
	{}

	void init();
	void set_viewport_size(const QSize &size);
	void set_view_matrix(const QMatrix4x4 &vMatrix) { _view_matrix = vMatrix; }
	GlModel *cube() { return _cube.data(); }

public slots:
	void paint();

private:
	QOpenGLShaderProgram _program;

	QScopedPointer<GlModel> _grid, _cube, _axles;
	QMatrix4x4 _uniform_matrix, _view_matrix;
};

#endif // RENDERER_H


