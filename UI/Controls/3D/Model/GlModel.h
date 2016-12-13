#ifndef GLMODEL_H
#define GLMODEL_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>

#include "GlVertex.h"

class GlModel : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
    public:
        GlModel(QOpenGLShaderProgram *_program, QVector<GlVertex> &vertexes, QVector<GLushort> &indexes);
        ~GlModel();

        void draw();
        void setPrimitive(GLushort primitive) { _primitive = primitive; }
        void setCount(int count) { _count = count; }

        void setRotate(QMatrix4x4 r) { _rotateMatrix = r; }
        void setTranslate(QMatrix4x4 r) { _translateMatrix = r; }

        QMatrix4x4 rotate() { return _rotateMatrix; }
        QMatrix4x4 translate() { return _translateMatrix; }

    private:
        QOpenGLVertexArrayObject *_vao;
        QOpenGLBuffer *_arrayBuffer;
        QOpenGLBuffer *_indexBuffer;

        QMatrix4x4 _rotateMatrix;
        QMatrix4x4 _translateMatrix;

        int _count;
        GLushort _primitive;
};

#endif // GLMODEL_H

