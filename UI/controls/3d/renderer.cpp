/*
 * renderer.cpp
 *
 *  Created on: Feb 9, 2017
 *  Copyright © 2017-2080 Ilja Karasev. All rights reserved.
 *     License: GNU GPL 3
 */

#include "renderer.h"

#include <QVector3D>
#include <QColor>

#include "model/gl_vertex.h"
#include "model/gl_model.h"

void Renderer::init()
{
	initializeOpenGLFunctions();


	_program.addShaderFromSourceCode(QOpenGLShader::Fragment,
									   "varying vec3 color;"
									   "varying float depth;"
									   "void main() {"
									   "    gl_FragColor = vec4(color, 1.0);"
										   "    gl_FragDepth = depth;"
									   "}");

	_program.addShaderFromSourceCode(QOpenGLShader::Vertex,
									   "uniform mat4 pvrtMatrix;"
									   "attribute vec3 in_position;"
									   "attribute vec3 in_color;"
									   "varying vec3 color;"
									   "varying float depth;"
									   "void main() {"
									   "    gl_Position  =  pvrtMatrix * vec4(in_position, 1.0);"
									   "    depth = gl_Position.z * 0.1;"
									   "    color = in_color;"
									   "}");

	_program.link();
	_program.bind();

	auto gray = QColor( 0x50, 0x50, 0x50 );

	auto red2 = QColor( 0x80, 0x08, 0x40 );
	auto red = QColor( 0x70, 0x38, 0x40 );

	auto green = QColor( 0x08, 0x80, 0x40 );
	auto yellow = QColor( 0x80, 0x80, 0x08 );

	auto blue2 = QColor( 0x08, 0x08, 0x80 );
	auto blue = QColor( 0x38, 0x38, 0x70 );

	QVector<GlVertex> _axlesVertexes;
	_axlesVertexes << GlVertex(0.0, 0.0, 0.0 , QColor("green") );
	_axlesVertexes << GlVertex(0.0, 0.0, 0.3 , QColor("green") );
	_axlesVertexes << GlVertex(0.0, 0.0, 0.0 , QColor("blue") );
	_axlesVertexes << GlVertex(0.3, 0.0, 0.0 , QColor("blue") );
	_axlesVertexes << GlVertex(0.0, 0.0, 0.0 , QColor("red") );
	_axlesVertexes << GlVertex(0.0, 0.3, 0.0 , QColor("red") );
	_axles.reset(new GlModel(_program, _axlesVertexes));

	QVector<GlVertex> _gridVertexes;
	float gridSize = 0.5;
	float gridStep = 0.125;

	for (GLfloat i = -gridSize; i <= gridSize; i+=gridStep)
	{
		_gridVertexes << GlVertex(-gridSize, i, 0.0 , gray );
		_gridVertexes << GlVertex( gridSize, i, 0.0 , gray );

		_gridVertexes << GlVertex( i, -gridSize, 0.0 , gray );
		_gridVertexes << GlVertex( i,  gridSize, 0.0 , gray );
	}

	_grid.reset(new GlModel(_program, _gridVertexes));

	QVector<GlVertex> _cubeVertexes;

	float cubeX = 0.1;
	float cubeY = 0.2;
	float cubeZ = 0.05;

	//oy plates
	_cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, red );
	_cubeVertexes << GlVertex(  cubeX, cubeY, cubeZ, red );
	_cubeVertexes << GlVertex( cubeX, cubeY, -cubeZ, red );

	_cubeVertexes << GlVertex(  -cubeX, cubeY, -cubeZ, red );
	_cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, red );
	_cubeVertexes << GlVertex( cubeX, cubeY, -cubeZ, red );

	_cubeVertexes << GlVertex(  -cubeX, -cubeY, cubeZ, red2 );
	_cubeVertexes << GlVertex(  -cubeX, -cubeY, -cubeZ, red2 );
	_cubeVertexes << GlVertex( cubeX, -cubeY, -cubeZ, red2 );

	_cubeVertexes << GlVertex(  cubeX, -cubeY, cubeZ, red2 );
	_cubeVertexes << GlVertex(  -cubeX, -cubeY, cubeZ, red2 );
	_cubeVertexes << GlVertex( cubeX, -cubeY, -cubeZ, red2 );

	//ox plates
	_cubeVertexes << GlVertex(  cubeX, cubeY, cubeZ, blue );
	_cubeVertexes << GlVertex(  cubeX, -cubeY, cubeZ, blue );
	_cubeVertexes << GlVertex( cubeX, -cubeY, -cubeZ, blue );

	_cubeVertexes << GlVertex(  cubeX, cubeY, -cubeZ, blue );
	_cubeVertexes << GlVertex(  cubeX, cubeY, cubeZ, blue );
	_cubeVertexes << GlVertex( cubeX, -cubeY, -cubeZ, blue );

	_cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, blue2 );
	_cubeVertexes << GlVertex(  -cubeX, cubeY, -cubeZ, blue2 );
	_cubeVertexes << GlVertex( -cubeX, -cubeY, -cubeZ, blue2 );

	_cubeVertexes << GlVertex(  -cubeX, -cubeY, cubeZ, blue2 );
	_cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, blue2 );
	_cubeVertexes << GlVertex( -cubeX, -cubeY, -cubeZ, blue2 );

	//oz plates
	_cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, green );
	_cubeVertexes << GlVertex(  -cubeX, -cubeY, cubeZ, green );
	_cubeVertexes << GlVertex(  cubeX, -cubeY, cubeZ, green );

	_cubeVertexes << GlVertex(  cubeX, cubeY, cubeZ, green );
	_cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, green );
	_cubeVertexes << GlVertex(  cubeX, -cubeY, cubeZ, green );

	_cubeVertexes << GlVertex(  -cubeX, cubeY, -cubeZ, yellow );
	_cubeVertexes << GlVertex(  cubeX, cubeY, -cubeZ, yellow );
	_cubeVertexes << GlVertex(  cubeX, -cubeY, -cubeZ, yellow );

	_cubeVertexes << GlVertex(  -cubeX, -cubeY, -cubeZ, yellow );
	_cubeVertexes << GlVertex(  -cubeX, cubeY, -cubeZ, yellow );
	_cubeVertexes << GlVertex(  cubeX, -cubeY, -cubeZ, yellow );

	_cube.reset(new GlModel(_program, _cubeVertexes));

	_program.release();
}

void Renderer::set_viewport_size(const QSize &size)
{
	_uniform_matrix.setToIdentity();
	_uniform_matrix.perspective(45, (float) size.width() / (float) size.height(), 0, 100);

	glViewport(0, 0, size.width(), size.height());
}

void Renderer::paint()
{
	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
//	glDepthMask(GL_TRUE); // GL_FALSE
	glDepthMask(GL_FALSE); // GL_FALSE

	glClearDepthf(1.0f);
	glDepthRangef(0.0f, 1.0f);
//	glDepthRange(0, 1); // disable
	glDepthFunc(GL_LEQUAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glDepthMask(GL_TRUE);

//	glClearColor(0, 0, 0, 1);
//	glClearDepth(1.0f);
//	glDepthFunc(GL_LEQUAL);

//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_program.bind();

	if (_grid) {
		_program.setUniformValue("pvrtMatrix", _uniform_matrix * _view_matrix * _grid->rotateMatrix() * _grid->translateMatrix());
		_grid->draw(_program, GL_LINES);
	}

	if (_axles) {
		_program.setUniformValue("pvrtMatrix", _uniform_matrix * _view_matrix * _axles->rotateMatrix() * _axles->translateMatrix());
		_axles->draw(_program, GL_LINES);
	}

	if (_cube) {
		_program.setUniformValue("pvrtMatrix", _uniform_matrix * _view_matrix * _cube->rotateMatrix() * _cube->translateMatrix());
		_cube->draw(_program, GL_TRIANGLES);
	}

	_program.release();
}

