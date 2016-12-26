#include "Projection.h"
#include "Core/Math.h"

#include <QtQuick/qquickwindow.h>
#include <QtMath>

Projection::Projection(QQuickItem *parent)
    :  QQuickItem(parent), _renderer(0), _camX(1,0,0,0), _camY(0,1,0,0), _camZ(0,0,1,0)
    , _camPos(0, -2, 0, 0), _qCamera(1,0,0,0), _dragAngle(false),  _cube(0), _frame(new QGyroFrame(this))
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
    // init position
    _camPos = QVector4D(-0.761009872, -0.914833724, 0.563965559, 0);
    _qCamera = QQuaternion(0.340076178, 0.0609764457, 0.165994048, 0.925754309);

    setAcceptHoverEvents(true);
    setFlag(ItemAcceptsInputMethod, true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void Projection::setPosition(GyroFrame p)
{
    _frame->data = p;
    emit _frame->changed();

    _position = p;

    if (_cube) _cube->setRotate(Math::dcm(p.Angle));

    if (window()) window()->update();
}

void Projection::wheelEvent(QWheelEvent *event)
{
    _camPos += _camY * event->angleDelta().y() / 400.0;

    _renderer->setVMatrix(vMatrix());
    if (window()) window()->update();

    QQuickItem::wheelEvent(event);
}

void Projection::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton)){
        _dragAngle = !_dragAngle;
        _dragPosition = false;
    }

    if (event->buttons().testFlag(Qt::RightButton)){
        _dragPosition = !_dragPosition;
        _dragAngle = false;
    }

    QQuickItem::mousePressEvent(event);
}

QMatrix4x4 Projection::vMatrix()
{
    QMatrix4x4 r = Math::dcm(_qCamera);
    _camX = r.column(0);
    _camY = r.column(1);
    _camZ = r.column(2);

    QMatrix4x4 vm;
    vm.setRow(0, -_camX);
    vm.setRow(1, _camZ);
    vm.setRow(2, _camY);
    vm.setRow(3, r.column(3));

    vm.translate(-_camPos.toVector3D());

    return vm;
}

void Projection::hoverMoveEvent(QHoverEvent *event)
{
    float dx = event->pos().x() - event->oldPos().x();
    float dy = event->pos().y() - event->oldPos().y();

    if (dx != 0 || dy != 0){
        if (_dragAngle)
        {
            _qCamera += Math::derivative(dy / 80.0, 0, 0);
            _qCamera = Math::unit(-dx / 80.0, 0, 1, 0) * _qCamera;
        }
        if (_dragPosition)
        {
            _camPos -= _camX * dx / 40.0;
            _camPos -= _camZ * dy / 40.0;
        }

        _renderer->setVMatrix(vMatrix());
        if (window()) window()->update();
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
        _cube = _renderer->cube();
    }
    _renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    _renderer->setVMatrix(vMatrix());
}





