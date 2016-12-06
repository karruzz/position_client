#include "Projection.h"

#include <QtQuick/qquickwindow.h>

Projection::Projection()
    : _renderer(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void Projection::setPosition(GyroFrame p)
{
    _position = p;
    emit positionChanged();

    if (window()) window()->update();
}

void Projection::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}

void Projection::cleanup()
{
    if (!_renderer) return;

    delete _renderer;
    _renderer = 0;
}

void Projection::sync()
{
    if (!_renderer) {
        _renderer = new ProjectionRenderer();
        connect(window(), SIGNAL(beforeRendering()), _renderer, SLOT(paint()), Qt::DirectConnection);
    }
    _renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    _renderer->setT(0.5);
}

ProjectionRenderer::~ProjectionRenderer()
{
    delete _program;

    _vao->destroy();
    delete _vao;

    _vbo->destroy();
    delete _vbo;
}


static const GLfloat _data[] = {
    -0.5, 0.5, 0,
    -0.5, -0.5, 0,
    0.5, -0.5, 0,
};

void ProjectionRenderer::paint()
{
    if (!_program) {
        initializeOpenGLFunctions();

        _program = new QOpenGLShaderProgram();

        _program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                           "uniform lowp float t;"
                                           "varying highp vec2 coords;"
                                           "void main() {"
                                           "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
                                           "    i = smoothstep(t - 0.8, t + 0.8, i);"
                                           "    i = floor(i * 20.) / 20.;"
                                           "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
                                           "}");

        _program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                           "attribute highp vec3 in_position;"
                                           "varying highp vec2 coords;"
                                           "void main() {"
                                           "    gl_Position   = vec4(in_position, 1.0);"
                                           "    coords = in_position.xy;"
                                           "}");

        _program->link();

        _vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        _vbo->create();
        _vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
        _vbo->bind();
        _vbo->allocate(9 * sizeof(GLfloat));

        _vao = new QOpenGLVertexArrayObject(this);
        _vao->create();
        _vao->bind();

        _program->bind();
        _vbo->bind();
        _vbo->write(0, _data, 9 * sizeof(GLfloat));

        int vertexLocation = _program->attributeLocation("in_position");
        _program->enableAttributeArray(vertexLocation);
        _program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3);

        _vao->release();
        _vbo->release();
        _program->release();
    }

    _program->setUniformValue("t", (float) _t);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glDisable(GL_DEPTH_TEST);

    glClearColor(0.25, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    _program->bind();

    _vao->bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    _vao->release();

    _program->release();
}

