#ifndef RAWMODEL
#define RAWMODEL

#include <QtGui/QOpenGLFunctions>

class GlRawModel
{
    public:
        GlRawModel(GLuint vao, int vertices) : _vao(vao), _verticesCount(vertices) { }

        GLuint vao() const { return _vao; }
        int verticesCount() const { return _verticesCount; }

    private:
        GLuint _vao;
        int _verticesCount;
};

#endif // RAWMODEL
