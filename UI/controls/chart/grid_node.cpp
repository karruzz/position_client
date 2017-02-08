#include "grid_node.h"

#include <QSGFlatColorMaterial>

GridNode::GridNode(QColor color, QVector2D colsRows)
    : _geometry(QSGGeometry::defaultAttributes_Point2D(), colsRows.x()*colsRows.y() + 13), _colsRows(colsRows)
{
    _verticesCount = _colsRows.x()*_colsRows.y() + 12;
    _geometry.setLineWidth(1);
    _geometry.setDrawingMode(GL_LINES);
    setGeometry(&_geometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    material->setColor(color);
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
    markDirty(QSGNode::DirtyMaterial);
}
void GridNode::alloc()
{
   _geometry.allocate(_verticesCount);
}

void GridNode::setRect(const QRectF &bounds)
{
    QSGGeometry::Point2D *vertices = _geometry.vertexDataAsPoint2D();

    float bottom = bounds.height();
    float step = (bottom - 2) / _colsRows.y();
    float center = bottom / 2;
    int i = 0;
    int position = 0;

    while (center + i * step < bottom)
    {
        vertices[position++].set(0, center + i * step);
        vertices[position++].set(bounds.width(), center + i * step);
        vertices[position++].set(0, center - i * step);
        vertices[position++].set(bounds.width(), center - i * step);
        i++;
    }

    step = (bounds.width()- 2) / _colsRows.x();
    center = bounds.width() / 2;
    i = 0;

    while (center + i * step < bounds.width())
    {
        vertices[position++].set(center + i * step, 0);
        vertices[position++].set(center + i * step, bottom);
        vertices[position++].set(center - i * step, 0);
        vertices[position++].set(center - i * step, bottom);
        i++;
    }
    while (position < _verticesCount)
    {
        vertices[position++].set(0, 0);
    }

    markDirty(QSGNode::DirtyGeometry);
}
