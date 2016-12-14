#include "Projection.h"

#include <QtQuick/qquickwindow.h>
#include "Math/Quaternion.h"
#include <QtMath>

Projection::Projection(QQuickItem *parent)
    :  QQuickItem(parent), _renderer(0), _camX(1,0,0,0), _camY(0,1,0,0), _camZ(0,0,1,0)
    , _camPos(0,-2,0,0), _qCamera(1,0,0,0),  _cube(0)
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

    if (_cube)
    {
        _cube->setRotate(dcm(p.Angle));
    }

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

QQuaternion Projection::derivative(QQuaternion &q, float wx, float wy, float wz)
{
    return 0.5 * q * QVector3D(wx, wy, wz);
}

QQuaternion Projection::unit(float angle, float x, float y, float z)
{
    float norm = 1.0 / qSqrt(x*x+y*y+z*z);
    x *= norm;
    y *= norm;
    z *= norm;

    float cos = qCos(angle / 2.0);
    float sin = qSin(angle / 2.0);
    return QQuaternion(cos, sin * x, sin * y, sin * z);
}

QMatrix4x4 Projection::dcm(Point3d euler)
{
    QMatrix4x4 r;
    float xc = qCos(euler.X);
    float xs = qSin(euler.X);

    float yc = qCos(euler.Y);
    float ys = qSin(euler.Y);

    float zc = qCos(euler.Z);
    float zs = qSin(euler.Z);

    r.setColumn(0, QVector4D(yc*zc, yc*zs, -ys, 0.0));
    r.setColumn(1, QVector4D(-xc*zs+xs*ys*zc, xc*zc+xs*ys*zs, xs*yc, 0.0));
    r.setColumn(2, QVector4D(xs*zs+xc*ys*zc, -xs*zc+xc*ys*zs, xc*yc, 0.0));
    r.setColumn(3, QVector4D(0.0, 0.0, 0.0, 1.0));

    return r;
}

QMatrix4x4 Projection::dcm(QQuaternion q)
{
    QMatrix4x4 m;
    float x = q.x();
    float y = q.y();
    float z = q.z();

    const float s = 2.0;
    m.setColumn(0, QVector4D( 1.0 - s * (y * y + z * z),
                              s * (x * y + z * ap),
                              s * (x * z - y * ap),
                              0.0 ));

    m.setColumn(1, QVector4D( s * (x * y - z * ap),
                              1.0 - s * (x * x + z * z),
                              s * (z * y + x * ap),
                              0.0 ));

    m.setColumn(2, QVector4D( s * (x * z + y * ap),
                              s * (y * z - x * ap),
                              1.0 - s * (x * x + y * y),
                              0.0 ));

    m.setColumn(3, QVector4D( 0.0, 0.0, 0.0, 1.0 ));
    return m;
}

QMatrix4x4 Projection::vMatrix()
{
    QMatrix4x4 r = dcm(_qCamera);
    _camX = r.column(0);
    _camY = r.column(1);
    _camZ = r.column(2);

    QMatrix4x4 vm;
    vm.setRow(0, -_camX);
    vm.setRow(1, _camZ);
    vm.setRow(2, -_camY);
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
            _qCamera += derivative(-dy / 80.0, 0, 0);
            _qCamera = unit(dx / 80.0, 0, 1, 0) * _qCamera;
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
}





