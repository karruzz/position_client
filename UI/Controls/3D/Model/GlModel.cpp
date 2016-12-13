#include "GlModel.h"

GlModel::GlModel(QOpenGLShaderProgram *_program, QVector<GlVertex> &vertexes, QVector<GLushort> &indexes) :
    _primitive(GL_LINES)
{
    initializeOpenGLFunctions();

    _rotateMatrix.setToIdentity();
    _translateMatrix.setToIdentity();

    _count = vertexes.length();

    QVector<GLfloat> _data;
    QVectorIterator<GlVertex> i(vertexes);
    while (i.hasNext()){
        GlVertex vertex = i.next();
        _data << vertex.Point.x() << vertex.Point.y() << vertex.Point.z();
        _data << vertex.Color.x() << vertex.Color.y() << vertex.Color.z();
    }

    _arrayBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    _arrayBuffer->create();
    _arrayBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    _arrayBuffer->bind();
    _arrayBuffer->allocate(_data.constData(), _data.length() * sizeof(GLfloat));

//    _indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    _indexBuffer->create();
//    _indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
//    _indexBuffer->bind();
//    _indexBuffer->allocate(indexes.constData(), indexes.length() * sizeof(GLushort));

    _vao = new QOpenGLVertexArrayObject(this);
    _vao->create();
    _vao->bind();
    _arrayBuffer->bind();
   // _indexBuffer->bind();

    _program->enableAttributeArray("in_position");
    _program->setAttributeBuffer("in_position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    _program->enableAttributeArray("in_color");
    _program->setAttributeBuffer("in_color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

  //  _indexBuffer->release();
    _arrayBuffer->release();
    _vao->release();
}

GlModel::~GlModel()
{
    _vao->destroy();
    delete _vao;

    _arrayBuffer->destroy();
    delete _arrayBuffer;
}

void GlModel::draw()
{
    _vao->bind();
     glDrawArrays(_primitive, 0, _count);
    _vao->release();
}
