#ifndef PROJECTION_H
#define PROJECTION_H

#include <QVector>

#include <QtQuick/QQuickItem>

#include "data/devices/gyro_frame.h"

#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector3D>

#include "renderer.h"
#include "data/devices/qgyro_frame.h"

class Projection : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY( QGyroFrame *Frame READ Frame NOTIFY frameChanged)

    public:
        Projection(QQuickItem *parent = 0);

        QGyroFrame *Frame() const { return _frame; }

        void wheelEvent(QWheelEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void hoverMoveEvent(QHoverEvent *event);

    signals:
        void frameChanged();

    public slots:
        void sync();
        void cleanup();
        void setPosition(GyroFrame p);

    private slots:
        void handleWindowChanged(QQuickWindow *win);

    private:
        QMatrix4x4 vMatrix();

        Renderer *_renderer;

        // current frame
        GyroFrame _position;
		QGyroFrame *_frame;

        // camera
        QVector4D _camX, _camY, _camZ, _camPos;
        QQuaternion _qCamera;
        bool _dragAngle;
        bool _dragPosition;

		// cube
		GlModel *_cube;
};

#endif // PROJECTION_H

