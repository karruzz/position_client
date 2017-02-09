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

Renderer::Renderer() : _program(0)
{
    initializeOpenGLFunctions();

    _program = new QOpenGLShaderProgram();

    _program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       "varying highp vec3 color;"
                                       "varying highp float depth;"
                                       "void main() {"
                                       "    gl_FragColor = vec4(color, 1.0);"
                                       "    gl_FragDepth = depth;"
                                       "}");

    _program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       "uniform mat4 pvrtMatrix;"
                                       "attribute highp vec3 in_position;"
                                       "attribute highp vec3 in_color;"
                                       "varying highp vec3 color;"
                                       "varying highp float depth;"
                                       "void main() {"
                                       "    gl_Position  =  pvrtMatrix * vec4(in_position, 1.0);"
                                       "    depth = gl_Position.z * 0.1;"
                                       "    color = in_color;"
                                       "}");

    _program->link();

    auto gray = QColor( 0x50, 0x50, 0x50 );
    auto red = QColor( 0x80, 0x08, 0x40 );
    auto green = QColor( 0x08, 0x80, 0x40 );
    auto blue = QColor( 0x08, 0x08, 0x80 );

    QVector<GlVertex> _axlesVertexes;
    _axlesVertexes << GlVertex(0.0, 0.0, 0.0 , QColor("green") );
    _axlesVertexes << GlVertex(0.0, 0.0, 0.3 , QColor("green") );
    _axlesVertexes << GlVertex(0.0, 0.0, 0.0 , QColor("blue") );
    _axlesVertexes << GlVertex(0.3, 0.0, 0.0 , QColor("blue") );
    _axlesVertexes << GlVertex(0.0, 0.0, 0.0 , QColor("red") );
    _axlesVertexes << GlVertex(0.0, 0.3, 0.0 , QColor("red") );
    _axles = new GlModel(_program, _axlesVertexes);

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

    _grid = new GlModel(_program, _gridVertexes);

    QVector<GlVertex> _cubeVertexes;

    float cubeX = 0.1;
    float cubeY = 0.2;
    float cubeZ = 0.05;

    //oy plates
    _cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, red );
    _cubeVertexes << GlVertex(  cubeX, cubeY, cubeZ, red );
    _cubeVertexes << GlVertex( cubeX, cubeY, -cubeZ, red );
    _cubeVertexes << GlVertex(  -cubeX, cubeY, -cubeZ, red );

    _cubeVertexes << GlVertex(  -cubeX, -cubeY, cubeZ, red );
    _cubeVertexes << GlVertex(  -cubeX, -cubeY, -cubeZ, red );
    _cubeVertexes << GlVertex( cubeX, -cubeY, -cubeZ, red );
    _cubeVertexes << GlVertex(  cubeX, -cubeY, cubeZ, red );

    //ox plates
    _cubeVertexes << GlVertex(  cubeX, cubeY, cubeZ, blue );
    _cubeVertexes << GlVertex(  cubeX, -cubeY, cubeZ, blue );
    _cubeVertexes << GlVertex( cubeX, -cubeY, -cubeZ, blue );
    _cubeVertexes << GlVertex(  cubeX, cubeY, -cubeZ, blue );

    _cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, blue );
    _cubeVertexes << GlVertex(  -cubeX, cubeY, -cubeZ, blue );
    _cubeVertexes << GlVertex( -cubeX, -cubeY, -cubeZ, blue );
    _cubeVertexes << GlVertex(  -cubeX, -cubeY, cubeZ, blue );

    //oz plates
    _cubeVertexes << GlVertex(  -cubeX, cubeY, cubeZ, green );
    _cubeVertexes << GlVertex(  -cubeX, -cubeY, cubeZ, green );
    _cubeVertexes << GlVertex(  cubeX, -cubeY, cubeZ, green );
    _cubeVertexes << GlVertex(  cubeX, cubeY, cubeZ, green );

    _cubeVertexes << GlVertex(  -cubeX, cubeY, -cubeZ, green );
    _cubeVertexes << GlVertex(  cubeX, cubeY, -cubeZ, green );
    _cubeVertexes << GlVertex(  cubeX, -cubeY, -cubeZ, green );
    _cubeVertexes << GlVertex(  -cubeX, -cubeY, -cubeZ, green );

    _cube = new GlModel(_program, _cubeVertexes);
}

Renderer::~Renderer()
{
    delete _program;

    if (_grid) delete _grid;
    if (_cube) delete _cube;
    if (_axles) delete _axles;
}

void Renderer::paint()
{
    _pMatrix.setToIdentity();
    _pMatrix.perspective(45, (float) m_viewportSize.width() / (float) m_viewportSize.height(), 0, 100);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);

    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0f);
    glDepthRange(0, 1);
    glDepthFunc(GL_LEQUAL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program->bind();

    if (_grid)
    {
        _program->setUniformValue("pvrtMatrix", _pMatrix * _vMatrix * _grid->rotateMatrix() * _grid->translateMatrix());
        _grid->draw(GL_LINES);
    }

    if (_cube)
    {
        _program->setUniformValue("pvrtMatrix", _pMatrix * _vMatrix * _cube->rotateMatrix() * _cube->translateMatrix());
        _cube->draw(GL_QUADS);
    }

    if (_axles)
    {
        _program->setUniformValue("pvrtMatrix", _pMatrix * _vMatrix * _axles->rotateMatrix() * _axles->translateMatrix());
        _axles->draw(GL_LINES);
    }

    _program->release();
}

