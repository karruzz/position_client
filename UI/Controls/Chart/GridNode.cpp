#include "GridNode.h"

#include <QSGFlatColorMaterial>

GridNode::GridNode()
    : _geometry(QSGGeometry::defaultAttributes_Point2D(), 29)
{
    _geometry.setLineWidth(1);
    _geometry.setDrawingMode(GL_LINES);
    setGeometry(&_geometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    material->setColor(QColor(0x50, 0x50, 0x50));
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
    markDirty(QSGNode::DirtyMaterial);
}
void GridNode::alloc()
{
   _geometry.allocate(28);
}

void GridNode::setRect(const QRectF &bounds)
{
    QSGGeometry::Point2D *vertices = _geometry.vertexDataAsPoint2D();

    auto step = bounds.height() / 4;
    for (int i = 0; i < 5; ++i) {
        float y = i * step;
        vertices[2*i].set(0, y);
        vertices[2*i+1].set(bounds.width(), y);
    }

    int shift = 10;
    step = bounds.width() / 8;
    for (int i = 0; i < 9; ++i) {
        float x = i * step;
        vertices[shift+2*i].set(x, 0);
        vertices[shift+2*i+1].set(x, bounds.height());
    }

    markDirty(QSGNode::DirtyGeometry);
}
