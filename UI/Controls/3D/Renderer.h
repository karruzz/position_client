#ifndef RENDERER_H
#define RENDERER_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>

class Renderer  : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Renderer() : _t(0), _program(0) { }
    ~Renderer();

    void setT(qreal t) { _t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setVMatrix(const QMatrix4x4 &vMatrix) { _vMatrix = vMatrix; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
    qreal _t;
    QOpenGLShaderProgram *_program;
    QOpenGLVertexArrayObject *_vao;
    QOpenGLBuffer *_vbo;

    QVector<GLfloat> _data;
    QMatrix4x4 _pMatrix;
    QMatrix4x4 _vMatrix;
};

#endif // RENDERER_H

