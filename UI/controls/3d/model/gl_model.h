/*
 * gl_model.h
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#ifndef GLMODEL_H
#define GLMODEL_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>

#include "gl_vertex.h"

class GlModel : public QObject, protected QOpenGLFunctions
{
Q_OBJECT
public:
	GlModel(QOpenGLShaderProgram& _program, QVector<GlVertex>& vertexes);
	~GlModel();

	void draw(QOpenGLShaderProgram& _program, GLushort primitive);

	QMatrix4x4 rotate_matrix;
	QMatrix4x4 translate_matrix;

private:
	int _count;
	QOpenGLVertexArrayObject _vao;
	QOpenGLBuffer _array_buffer;
};

#endif // GLMODEL_H

