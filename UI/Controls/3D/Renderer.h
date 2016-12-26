#ifndef RENDERER_H
#define RENDERER_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>

#include "Model/GlModel.h"

class Renderer  : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Renderer();
    ~Renderer();

    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setVMatrix(const QMatrix4x4 &vMatrix) { _vMatrix = vMatrix; }
    GlModel *cube() { return _cube; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
    QOpenGLShaderProgram *_program;

    GlModel *_grid;
    GlModel *_cube;
    GlModel *_axles;

    QVector<GLfloat> _data;
    QMatrix4x4 _pMatrix;
    QMatrix4x4 _vMatrix;
};

#endif // RENDERER_H


