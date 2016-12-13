#include "Renderer.h"
#include "Model/GlVertex.h"
#include <QVector3D>
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

    QVector<GlVertex> _gridVertexes;

    for (GLfloat i = -0.5; i < 0.5; i+=0.1)
    {
        _gridVertexes << GlVertex(QVector3D( -0.5, i, 0.0 ), QVector3D( 0.5, 0.5, 0.5));
        _gridVertexes << GlVertex(QVector3D( 0.5, i, 0.0 ), QVector3D( 0.5, 0.5, 0.5));

        _gridVertexes << GlVertex(QVector3D( i, -0.5, 0.0 ), QVector3D( 0.5, 0.5, 0.5));
        _gridVertexes << GlVertex(QVector3D( i, 0.5, 0.0 ), QVector3D( 0.5, 0.5, 0.5));
    }

    _grid = new GlModel(_program, _gridVertexes);

    QVector<GlVertex> _cubeVertexes;

    //oy plate
    _cubeVertexes << GlVertex(QVector3D( -0.21, 0.11, 0.051 ), QVector3D( 0.1, 0.1, 0.5 ));
    _cubeVertexes << GlVertex(QVector3D( 0.21, 0.11, 0.051 ), QVector3D( 0.1, 0.1, 0.5 ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, 0.11, -0.051 ), QVector3D( 0.1, 0.1, 0.5 ));

    _cubeVertexes << GlVertex(QVector3D( 0.21, 0.11, 0.051 ), QVector3D( 0.1, 0.1, 0.5));
    _cubeVertexes << GlVertex(QVector3D(0.21, 0.11, -0.051 ), QVector3D( 0.1, 0.1, 0.5 ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, 0.11, -0.051 ), QVector3D( 0.1, 0.1, 0.5 ));

    _cubeVertexes << GlVertex(QVector3D( -0.21, -0.11, 0.051 ), QVector3D( 0.1, 0.1, 0.5 ));
    _cubeVertexes << GlVertex(QVector3D( 0.21, -0.11, 0.051 ), QVector3D( 0.1, 0.1, 0.5 ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, -0.11, -0.051 ), QVector3D( 0.1, 0.1, 0.5 ));

    _cubeVertexes << GlVertex(QVector3D( 0.21, -0.11, 0.051 ), QVector3D( 0.1, 0.1, 0.5 ));
    _cubeVertexes << GlVertex(QVector3D(0.21, -0.11, -0.051 ), QVector3D( 0.1, 0.1, 0.5 ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, -0.11, -0.051 ), QVector3D( 0.1, 0.1, 0.5 ));

    //ox plate
    _cubeVertexes << GlVertex(QVector3D( -0.21, 0.11, 0.051 ), QVector3D( 0.5, 0.1, 0.3));
    _cubeVertexes << GlVertex(QVector3D( -0.21, -0.11, 0.051 ), QVector3D( 0.5, 0.1, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, -0.11, -0.051 ), QVector3D( 0.5, 0.1, 0.3 ));

    _cubeVertexes << GlVertex(QVector3D( -0.21, 0.11, 0.051 ), QVector3D( 0.5, 0.1, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D( -0.21, 0.11, -0.051 ), QVector3D( 0.5, 0.1, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, -0.11, -0.051 ), QVector3D( 0.5, 0.1, 0.3 ));

    _cubeVertexes << GlVertex(QVector3D( 0.21, 0.11, 0.051 ), QVector3D( 0.5, 0.1, 0.3));
    _cubeVertexes << GlVertex(QVector3D( 0.21, -0.11, 0.051 ), QVector3D( 0.5, 0.1, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D(0.21, -0.11, -0.051 ), QVector3D( 0.5, 0.1, 0.3 ));

    _cubeVertexes << GlVertex(QVector3D( 0.21, 0.11, 0.051 ), QVector3D( 0.5, 0.1, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D( 0.21, 0.11, -0.051 ), QVector3D( 0.5, 0.1, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D(0.21, -0.11, -0.051 ), QVector3D( 0.5, 0.1, 0.3 ));

    //oz plate
    _cubeVertexes << GlVertex(QVector3D( -0.21, 0.11, 0.051 ), QVector3D( 0.1, 0.5, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D( -0.21, -0.11, 0.051 ), QVector3D( 0.1, 0.5, 0.3  ));
    _cubeVertexes << GlVertex(QVector3D( 0.21, -0.11, 0.051 ), QVector3D( 0.1, 0.5, 0.3  ));

    _cubeVertexes << GlVertex(QVector3D( 0.21, 0.11, 0.051 ), QVector3D( 0.1, 0.5, 0.3  ));
    _cubeVertexes << GlVertex(QVector3D( 0.21, -0.11, 0.051 ), QVector3D( 0.1, 0.5, 0.3  ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, 0.11, 0.051 ), QVector3D( 0.1, 0.5, 0.3  ));

    _cubeVertexes << GlVertex(QVector3D( -0.21, 0.11, -0.051 ), QVector3D( 0.1, 0.5, 0.3 ));
    _cubeVertexes << GlVertex(QVector3D( -0.21, -0.11, -0.051 ), QVector3D( 0.1, 0.5, 0.3  ));
    _cubeVertexes << GlVertex(QVector3D( 0.21, -0.11, -0.051 ), QVector3D( 0.1, 0.5, 0.3  ));

    _cubeVertexes << GlVertex(QVector3D( 0.21, 0.11, -0.051 ), QVector3D( 0.1, 0.5, 0.3  ));
    _cubeVertexes << GlVertex(QVector3D( 0.21, -0.11, -0.051 ), QVector3D( 0.1, 0.5, 0.3  ));
    _cubeVertexes << GlVertex(QVector3D(-0.21, 0.11, -0.051 ), QVector3D( 0.1, 0.5, 0.3  ));

    _cube = new GlModel(_program, _cubeVertexes);
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

