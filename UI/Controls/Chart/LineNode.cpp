#include "LineNode.h"

#include <QSGFlatColorMaterial>

LineNode::LineNode(int size, const QColor &color, const QVector2D margin)
    : _geometry(QSGGeometry::defaultAttributes_Point2D(), size), _margin(margin)
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
                         float minY, float maxY, quint64 minX, quint64 maxX)
{
    auto size = points.size();
    float kx = (bounds.width() - _margin.x()) / (maxX - minX);
    float ky = (bounds.height() - _margin.y()) / (maxY - minY);

    QSGGeometry::Point2D *vertices = _geometry.vertexDataAsPoint2D();
    for (int i = 0; i < size; ++i) {
        const QPointF &p = points[i];
        float x = (p.x() - minX) * kx + _margin.x();
        float y = (maxY - p.y()) * ky;
        vertices[i].set(x, y);
    }

    markDirty(QSGNode::DirtyGeometry);
}
