#include <UI/Controls/Chart/Chart.h>

Chart::Chart(QQuickItem *parent)
    : QQuickItem(parent),
      _min(-0.1), _max(0.1), _color("red")
{
    setFlag(ItemHasContents);
}

void Chart::setPoints(const QVector<QPointF> &points)
{
    if (points.isEmpty()) return;
    _points = points;

    update();
}

QSGNode *Chart::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    QSGFlatColorMaterial *material = 0;

    auto size = _points.size();

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), size + 1);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINE_STRIP);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        material = new QSGFlatColorMaterial;
        material->setColor(_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
        node->markDirty(QSGNode::DirtyMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(size);
        material = static_cast<QSGFlatColorMaterial*>(node->material());
    }

    auto delta = _max - _min;

    QRectF bounds = boundingRect();
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    for (int i = 0; i < size; ++i) {
        const QPointF &p = _points[i];
        float x = p.x() / size * bounds.width();
        float y = (1.0 - (p.y() - _min) / delta) * bounds.height();
        vertices[i].set(x, y);
    }

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
