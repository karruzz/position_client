#include "Renderer.h"

Renderer::~Renderer()
{
    delete _program;

    _vao->destroy();
    delete _vao;

    _vbo->destroy();
    delete _vbo;
}

void Renderer::paint()
{
    if (!_program) {
        initializeOpenGLFunctions();

        for (GLfloat i = -0.5; i < 0.5; i+=0.1){
            _data << -0.5 << i << 0;
            _data << 0.5 << i << 0;

            _data << i << -0.5 << 0;
            _data << i << 0.5 << 0;
        }

        _program = new QOpenGLShaderProgram();

        _program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                           "uniform lowp float t;"
                                           "void main() {"
                                           "    gl_FragColor = vec4(0.5, 0.5, 0.5, 1);"
                                           "}");

        _program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                           "uniform mat4 matrix;"
                                           "attribute highp vec3 in_position;"
                                           "void main() {"
                                           "    gl_Position  =  matrix*vec4(in_position, 1.0);"
                                           "}");

        _program->link();

        _vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        _vbo->create();
        _vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
        _vbo->bind();
        _vbo->allocate(_data.length() * sizeof(GLfloat));

        _vao = new QOpenGLVertexArrayObject(this);
        _vao->create();
        _vao->bind();

        _program->bind();
        _vbo->bind();
        _vbo->write(0, _data.constData(), _data.length() * sizeof(GLfloat));

        int vertexLocation = _program->attributeLocation("in_position");
        _program->enableAttributeArray(vertexLocation);
        _program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3);

        _vao->release();
        _vbo->release();
        _program->release();
    }

    _pMatrix.setToIdentity();
    _pMatrix.perspective(45, (float) m_viewportSize.width() / (float) m_viewportSize.height(), 0, 7);

 //   QMatrix4x4 vMatrix;
//    QMatrix4x4 camera;

//    camera.rotate(25, 0, 1, 0);
//    camera.rotate(-25, 1, 0, 0);

//    QVector3D cameraPosition = camera * QVector3D(0,0,2);
//    QVector3D cameraIpDirection = camera * QVector3D(0,1,0);

   // vMatrix.setToIdentity();
//    vMatrix.lookAt(cameraPosition, QVector3D(0,0,0), cameraIpDirection);

      //  vMatrix.lookAt(QVector3D(1,1,1), QVector3D(0,0,0), QVector3D(0,1,0));


    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program->bind();

    _program->setUniformValue("t", (float) _t);
    _program->setUniformValue("matrix", _pMatrix * _vMatrix);

    _vao->bind();

    glDrawArrays(GL_LINES, 0, _data.length() / 3);

    _vao->release();

    _program->release();
}
