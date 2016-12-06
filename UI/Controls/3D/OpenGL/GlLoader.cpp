#include "GlLoader.h"
#include <QOpenGLFunctions>

GlRawModel GlLoader::LoadToVAO(QVector<GLfloat> positions) const
{
    int vaoID = 0;//createVAO();
  //  storeDataInAttributeList(0, positions);
   // unbindVAO();
    GlRawModel model(vaoID, positions.length() / 3);
    return model;
}

void GlLoader::CleanUp()
{
//    foreach (_vbos, vbo)
//        glDeleteBuffers(1, &vbo);
}

void GlLoader::storeDataInAttributeList(int attributeNumber, QVector<GLfloat> data)
{
//    GLuint vbo;
//    glGenBuffers(1, &vbo);
//    _vaos << vbo;
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, data.count() * sizeof(GLfloat), data.constData(), GL_STATIC_DRAW);
//    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
