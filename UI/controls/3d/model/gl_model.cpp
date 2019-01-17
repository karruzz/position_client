/*
 * gl_model.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "gl_model.h"

GlModel::GlModel(QOpenGLShaderProgram& _program, QVector<GlVertex> &vertexes)
	: _vertex_count(vertexes.length())
{
	initializeOpenGLFunctions();

	rotate_matrix.setToIdentity();
	translate_matrix.setToIdentity();

	QVector<GLfloat> _data;
	QVectorIterator<GlVertex> i(vertexes);
	while (i.hasNext()){
		GlVertex vertex = i.next();
		_data << vertex.Point.x() << vertex.Point.y() << vertex.Point.z();
		_data << vertex.Color.x() << vertex.Color.y() << vertex.Color.z();
	}

	_array_buffer.create();
	_array_buffer.bind();
	_array_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	_array_buffer.allocate(_data.constData(), _data.length() * sizeof(GLfloat));

	_vao.create();
	_vao.bind();

	_program.enableAttributeArray("in_position");
	_program.enableAttributeArray("in_color");
	_program.setAttributeBuffer("in_position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
	_program.setAttributeBuffer("in_color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

	_array_buffer.release();
	_vao.release();
}

GlModel::~GlModel()
{
	_vao.destroy();
	_array_buffer.destroy();
}

void GlModel::draw(QOpenGLShaderProgram& _program, GLushort primitive)
{
	_vao.bind();
	_array_buffer.bind();

	_program.enableAttributeArray("in_position");
	_program.enableAttributeArray("in_color");
	_program.setAttributeBuffer("in_position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
	_program.setAttributeBuffer("in_color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

	glDrawArrays(primitive, 0, _vertex_count);

	 _array_buffer.release();
	_vao.release();
}
