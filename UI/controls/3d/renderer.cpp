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
//									   "    gl_FragDepth = depth;"
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

	// coordinate axles
	QVector<GlVertex> _axlesVertexes;
	_axlesVertexes << GlVertex(0.0, 0.0, 0.0, QColor("green") );
	_axlesVertexes << GlVertex(0.0, 0.0, 0.3, QColor("green") );
	_axlesVertexes << GlVertex(0.0, 0.0, 0.0, QColor("blue") );
	_axlesVertexes << GlVertex(0.3, 0.0, 0.0, QColor("blue") );
	_axlesVertexes << GlVertex(0.0, 0.0, 0.0, QColor("red") );
	_axlesVertexes << GlVertex(0.0, 0.3, 0.0, QColor("red") );
	_axles.reset(new GlModel(_program, _axlesVertexes));

	// grid
	QVector<GlVertex> _gridVertexes;
	auto gray = QColor( 0x50, 0x50, 0x50 );
	float gridSize = 0.5;
	float gridStep = 0.125;

	for (GLfloat i = -gridSize; i <= gridSize; i+=gridStep) {
		_gridVertexes << GlVertex(-gridSize, i, 0.0 , gray );
		_gridVertexes << GlVertex( gridSize, i, 0.0 , gray );

		_gridVertexes << GlVertex( i, -gridSize, 0.0 , gray );
		_gridVertexes << GlVertex( i,  gridSize, 0.0 , gray );
	}
	_grid.reset(new GlModel(_program, _gridVertexes));

	// cube
	QVector<GlVertex> _cubeVertexes;
	auto red2 = QColor( 0x80, 0x08, 0x40 );
	auto red = QColor( 0x70, 0x38, 0x40 );
	auto green = QColor( 0x08, 0x80, 0x40 );
	auto yellow = QColor( 0x80, 0x80, 0x08 );
	auto blue2 = QColor( 0x08, 0x08, 0x80 );
	auto blue = QColor( 0x38, 0x38, 0x70 );
	float cubeX = 0.1;
	float cubeY = 0.2;
	float cubeZ = 0.05;
/*
 *    5 ______ 6
 *     /green/|
 *  1 /_____/b|
 *    |   2 |l|
 *    | red |u/ 7
 *    |_____|/
 *  4         3
 */
	QVector3D p1 = QVector3D(-cubeX, cubeY,  cubeZ);
	QVector3D p2 = QVector3D( cubeX, cubeY,  cubeZ);
	QVector3D p3 = QVector3D( cubeX, cubeY, -cubeZ);
	QVector3D p4 = QVector3D(-cubeX, cubeY, -cubeZ);

	QVector3D p5 = QVector3D(-cubeX, -cubeY,  cubeZ);
	QVector3D p6 = QVector3D( cubeX, -cubeY,  cubeZ);
	QVector3D p7 = QVector3D( cubeX, -cubeY, -cubeZ);
	QVector3D p8 = QVector3D(-cubeX, -cubeY, -cubeZ);

	//oy plates
	_cubeVertexes << GlVertex(p1, red) << GlVertex(p2, red) << GlVertex(p3, red);
	_cubeVertexes << GlVertex(p1, red) << GlVertex(p3, red) << GlVertex(p4, red);

	_cubeVertexes << GlVertex(p5, red2) << GlVertex(p7, red2) << GlVertex(p6, red2);
	_cubeVertexes << GlVertex(p5, red2) << GlVertex(p8, red2) << GlVertex(p7, red2);

	//ox plates
	_cubeVertexes << GlVertex(p2, blue) << GlVertex(p6, blue) << GlVertex(p7, blue);
	_cubeVertexes << GlVertex(p2, blue) << GlVertex(p7, blue) << GlVertex(p3, blue);

	_cubeVertexes << GlVertex(p1, blue2) << GlVertex(p8, blue2) << GlVertex(p5, blue2);
	_cubeVertexes << GlVertex(p1, blue2) << GlVertex(p4, blue2) << GlVertex(p8, blue2);

	//oz plates
	_cubeVertexes << GlVertex(p1, green) << GlVertex(p5, green) << GlVertex(p6, green);
	_cubeVertexes << GlVertex(p1, green) << GlVertex(p6, green) << GlVertex(p2, green);

	_cubeVertexes << GlVertex(p4, yellow) << GlVertex(p7, yellow) << GlVertex(p8, yellow);
	_cubeVertexes << GlVertex(p4, yellow) << GlVertex(p3, yellow) << GlVertex(p7, yellow);

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
	glDepthMask(GL_TRUE); // GL_FALSE
//	glDepthMask(GL_FALSE); // GL_FALSE

	glClearDepthf(1.0f);
	glDepthRangef(0.0f, 1.0f);
	glDepthRange(0, 1); // disable
	glDepthFunc(GL_LEQUAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_program.bind();

	if (_grid) {
		_program.setUniformValue("pvrtMatrix", _uniform_matrix * _view_matrix * _grid->rotate_matrix * _grid->translate_matrix);
		_grid->draw(_program, GL_LINES);
	}

	if (_axles) {
		_program.setUniformValue("pvrtMatrix", _uniform_matrix * _view_matrix * _axles->rotate_matrix * _axles->translate_matrix);
		_axles->draw(_program, GL_LINES);
	}

	if (_cube) {
		_program.setUniformValue("pvrtMatrix", _uniform_matrix * _view_matrix * _cube->rotate_matrix * _cube->translate_matrix);
		_cube->draw(_program, GL_TRIANGLES);
	}

	_program.release();
}

