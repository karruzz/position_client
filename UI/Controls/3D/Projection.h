#ifndef PROJECTION_H
#define PROJECTION_H

#include <QVector>

#include <QtQuick/QQuickItem>

#include "Data/Devices/GyroFrame.h"

#include <QSurfaceFormat>
#include <QMatrix4x4>

#include "Renderer.h"
#include "Math/Quaternion.h"

class Projection : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY( GyroFrame position READ position WRITE setPosition NOTIFY positionChanged)

    public:
        Projection(QQuickItem *parent = 0);
        GyroFrame position() const { return _position; }
        void setPosition(GyroFrame p);

        void mousePressEvent(QMouseEvent *event);
        void hoverMoveEvent(QHoverEvent *event);

    signals:
        void positionChanged();

    public slots:
        void sync();
        void cleanup();

    private slots:
        void handleWindowChanged(QQuickWindow *win);

    private:
        Renderer *_renderer;
        GyroFrame _position;

        // camera
        QVector3D _camX, _camY, _camZ, _camPos;
        Quaternion _qCamera;
        QVector2D _mousePosLast;

        float _angle;

        bool _dragAngle;
        bool _dragPosition;
};

#endif // PROJECTION_H

