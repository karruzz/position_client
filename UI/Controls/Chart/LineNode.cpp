#include "LineNode.h"

#include <QSGFlatColorMaterial>

LineNode::LineNode(int size, const QColor &color)
    : _geometry(QSGGeometry::defaultAttributes_Point2D(), size)
{
    _geometry.setLineWidth(1);
    _geometry.setDrawingMode(GL_LINE_STRIP);
    setGeometry(&_geometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    material->setColor(color);
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
    markDirty(QSGNode::DirtyMaterial);
}
void LineNode::alloc(int size)
{
   _geometry.allocate(size);
}

void LineNode::setPoints(const QRectF &bounds, const QVector<QPointF> &points,
                         float max, float min)
{
    auto size = points.size();
    auto delta = max - min;

    QSGGeometry::Point2D *vertices = _geometry.vertexDataAsPoint2D();
    for (int i = 0; i < size; ++i) {
        const QPointF &p = points[i];
        float x = p.x() / size * bounds.width();
        float y = (1.0 - (p.y() - min) / delta) * bounds.height();
        vertices[i].set(x, y);
    }

    markDirty(QSGNode::DirtyGeometry);
}
