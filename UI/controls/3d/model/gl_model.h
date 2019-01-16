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
	void setCount(int count) { _count = count; }

	void setRotate(QMatrix4x4 r) { _rotateMatrix = r; }
	void setTranslate(QMatrix4x4 r) { _translateMatrix = r; }

	QMatrix4x4 rotateMatrix() { return _rotateMatrix; }
	QMatrix4x4 translateMatrix() { return _translateMatrix; }

private:
	QOpenGLVertexArrayObject _vao;
	QOpenGLBuffer _arrayBuffer;

	QMatrix4x4 _rotateMatrix;
	QMatrix4x4 _translateMatrix;

	int _count;
};

#endif // GLMODEL_H

