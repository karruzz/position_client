#ifndef GLLOADER
#define GLLOADER

#include <QtCore>
#include <QVector>
#include <QList>
#include "GlRawModel.h"
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

class GlLoader : public QObject
{
    Q_OBJECT
    public:
        GlRawModel LoadToVAO(QVector<GLfloat> positions) const;
        void CleanUp();

    private:
        QOpenGLVertexArrayObject *_vao;
        QList<GLuint> _vbos;

      //  GLuint createVAO() const;
        void storeDataInAttributeList(int attributeNumber, QVector<GLfloat> data);
      //  void unbindVAO();
};

#endif // GLLOADER


