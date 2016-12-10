#include "Projection.h"

#include <QtQuick/qquickwindow.h>
#include "Math/Quaternion.h"

Projection::Projection(QQuickItem *parent)
    :  QQuickItem(parent), _renderer(0), _camX(1,0,0), _camY(0,1,0), _camZ(0,0,1)
    , _camPos(0,-2,0), _qCamera(1,0,0,0), _angle(0)
    , _dragAngle(false)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));

    setAcceptHoverEvents(true);
    setFlag(ItemAcceptsInputMethod, true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void Projection::setPosition(GyroFrame p)
{
    _position = p;
    emit positionChanged();

    if (window()) window()->update();
}

void Projection::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton)){
        _dragAngle = !_dragAngle;
        _dragPosition = false;
        _mousePosLast.setX(0);
        _mousePosLast.setY(0);
    }

    if (event->buttons().testFlag(Qt::RightButton)){
        _dragPosition = !_dragPosition;
        _dragAngle = false;
        _mousePosLast.setX(0);
        _mousePosLast.setY(0);
    }

    QQuickItem::mousePressEvent(event);
}

void Projection::hoverMoveEvent(QHoverEvent *event)
{
    if (_mousePosLast.x() != 0 || _mousePosLast.y() != 0)
    {
        float dx = event->pos().x() - event->oldPos().x();
        float dy = event->pos().y() - event->oldPos().y();

        if (dx != 0 || dy != 0){
            if (_dragAngle)
            {
                _qCamera += _qCamera.derivative(-dy / 60.0, 0, 0);
                _qCamera = Quaternion::Unit(-dx / 60.0, 0, 1, 0) * _qCamera;
            }
            if (_dragPosition)
            {
                _camPos -= _camX * dx / 40.0;
                _camPos -= _camZ * dy / 40.0;
            }

            auto norm = _qCamera.length();
            Quaternion qCamInverted = _qCamera.conjugate() / norm / norm;
            _camX = (_qCamera * Quaternion(0, 1, 0, 0) * qCamInverted).vector();
            _camY = (_qCamera * Quaternion(0, 0, 1, 0) * qCamInverted).vector();
            _camZ = (_qCamera * Quaternion(0, 0, 0, 1) * qCamInverted).vector();

            QMatrix4x4 vMatrix;
            vMatrix.setRow(0, QVector4D(-_camX));
            vMatrix.setRow(1, QVector4D(_camZ));
            vMatrix.setRow(2, QVector4D(-_camY));
            vMatrix.setRow(3, QVector4D(0.0, 0.0, 0.0, 1.0));

            vMatrix.translate(-_camPos);

            _renderer->setVMatrix(vMatrix);
            if (window()) window()->update();
        }
    }

    _mousePosLast.setX(event->pos().x());
    _mousePosLast.setY(event->pos().y());
    QQuickItem::hoverMoveEvent(event);
}

void Projection::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);

        QSurfaceFormat format;
        format.setMajorVersion(3);
        format.setMinorVersion(3);
        format.setProfile( QSurfaceFormat::CompatibilityProfile );
        win->setFormat( format );
    }
}

void Projection::cleanup()
{
    if (!_renderer) return;

    delete _renderer;
    _renderer = 0;
}

void Projection::sync()
{
    if (!_renderer) {
        _renderer = new Renderer();
        connect(window(), SIGNAL(beforeRendering()), _renderer, SLOT(paint()), Qt::DirectConnection);
    }
    _renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    _renderer->setT(0.5);
}



