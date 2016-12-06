#ifndef PROJECTION_H
#define PROJECTION_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>

#include "Data/Devices/GyroFrame.h"

class ProjectionRenderer  : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    ProjectionRenderer() : _t(0), _program(0) { }
    ~ProjectionRenderer();

    void setT(qreal t) { _t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
    qreal _t;
    QOpenGLShaderProgram *_program;
    QOpenGLVertexArrayObject *_vao;
    QOpenGLBuffer *_vbo;
};

class Projection : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY( GyroFrame position READ position WRITE setPosition NOTIFY positionChanged)

    public:
        Projection();
        GyroFrame position() const { return _position; }
        void setPosition(GyroFrame p);

    signals:
        void positionChanged();

    public slots:
        void sync();
        void cleanup();

    private slots:
        void handleWindowChanged(QQuickWindow *win);

    private:
        ProjectionRenderer *_renderer;
        GyroFrame _position;
};

#endif // PROJECTION_H

