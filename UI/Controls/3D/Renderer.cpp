#include "Renderer.h"

#include <QVector3D>
#include <QColor>

#include "Model/GlVertex.h"
#include "Model/GlModel.h"

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

    QVector<GlVertex> _gridVertexes;

    for (GLfloat i = -0.5; i <= 0.5; i+=0.25)
    {
        _gridVertexes << GlVertex(-0.5, i, 0.0 , gray );
        _gridVertexes << GlVertex( 0.5, i, 0.0 , gray );

        _gridVertexes << GlVertex( i, -0.5, 0.0 , gray );
        _gridVertexes << GlVertex( i, 0.5, 0.0 , gray );
    }

    _grid = new GlModel(_program, _gridVertexes);

    QVector<GlVertex> _cubeVertexes;

    //oy plate
    _cubeVertexes << GlVertex(  -0.2, 0.1, 0.05, blue );
    _cubeVertexes << GlVertex(  0.2, 0.1, 0.05, blue );
    _cubeVertexes << GlVertex( -0.2, 0.1, -0.05, blue );

    _cubeVertexes << GlVertex(  0.2, 0.1, 0.05, blue );
    _cubeVertexes << GlVertex( 0.2, 0.1, -0.05, blue );
    _cubeVertexes << GlVertex( -0.2, 0.1, -0.05, blue );

    _cubeVertexes << GlVertex(  -0.2, -0.1, 0.05, blue );
    _cubeVertexes << GlVertex(  0.2, -0.1, 0.05, blue );
    _cubeVertexes << GlVertex( -0.2, -0.1, -0.05, blue );

    _cubeVertexes << GlVertex(  0.2, -0.1, 0.05, blue );
    _cubeVertexes << GlVertex( 0.2, -0.1, -0.05, blue );
    _cubeVertexes << GlVertex( -0.2, -0.1, -0.05, blue );

    //ox plate
    _cubeVertexes << GlVertex(  -0.2, 0.1, 0.05, red );
    _cubeVertexes << GlVertex(  -0.2, -0.1, 0.05, red );
    _cubeVertexes << GlVertex( -0.2, -0.1, -0.05, red );

    _cubeVertexes << GlVertex(  -0.2, 0.1, 0.05, red );
    _cubeVertexes << GlVertex(  -0.2, 0.1, -0.05, red );
    _cubeVertexes << GlVertex( -0.2, -0.1, -0.05, red );

    _cubeVertexes << GlVertex(  0.2, 0.1, 0.05, red );
    _cubeVertexes << GlVertex(  0.2, -0.1, 0.05, red );
    _cubeVertexes << GlVertex( 0.2, -0.1, -0.05, red );

    _cubeVertexes << GlVertex(  0.2, 0.1, 0.05, red );
    _cubeVertexes << GlVertex(  0.2, 0.1, -0.05, red );
    _cubeVertexes << GlVertex( 0.2, -0.1, -0.05, red );

    //oz plate
    _cubeVertexes << GlVertex(  -0.2, 0.1, 0.05, green );
    _cubeVertexes << GlVertex(  -0.2, -0.1, 0.05, green );
    _cubeVertexes << GlVertex(  0.2, -0.1, 0.05, green );

    _cubeVertexes << GlVertex(  0.2, 0.1, 0.05, green );
    _cubeVertexes << GlVertex(  0.2, -0.1, 0.05, green );
    _cubeVertexes << GlVertex( -0.2, 0.1, 0.05, green );

    _cubeVertexes << GlVertex(  -0.2, 0.1, -0.05, green );
    _cubeVertexes << GlVertex(  -0.2, -0.1, -0.05, green );
    _cubeVertexes << GlVertex(  0.2, -0.1, -0.05, green );

    _cubeVertexes << GlVertex(  0.2, 0.1, -0.05, green );
    _cubeVertexes << GlVertex(  0.2, -0.1, -0.05, green );
    _cubeVertexes << GlVertex( -0.2, 0.1, -0.05, green );

    _cube = new GlModel(_program, _cubeVertexes);

    glClearColor(0, 0, 0, 1);
}

Renderer::~Renderer()
{
    delete _program;

    if (_grid) delete _grid;
    if (_cube) delete _cube;
}

void Renderer::paint()
{
    _pMatrix.setToIdentity();
    _pMatrix.perspective(45, (float) m_viewportSize.width() / (float) m_viewportSize.height(), 0, 100);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    glEnable(GL_DEPTH_TEST);
  //  glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);

    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0f);
    glDepthRange(0, 1);
    glDepthFunc(GL_LEQUAL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program->bind();

    if (_grid)
    {
        _program->setUniformValue("pvrtMatrix", _pMatrix * _vMatrix * _grid->rotate() * _grid->translate());
        _grid->draw(GL_LINES);
    }

    if (_cube)
    {
        _program->setUniformValue("pvrtMatrix", _pMatrix * _vMatrix * _cube->rotate() * _cube->translate());
        _cube->draw(GL_TRIANGLES);
    }

    _program->release();
}

