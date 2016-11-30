#include <View/chart.h>

Chart::Chart(QQuickItem *parent)
    : QQuickItem(parent),
      _min(0), _max(0)
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
        material->setColor("Red");
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
        node->markDirty(QSGNode::DirtyMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(size);
        material = static_cast<QSGFlatColorMaterial*>(node->material());
    }

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    for (int i = 0; i < size; ++i) {
        const QPointF &p = _points[i];
        vertices[i].set(p.x(), p.y());
    }

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
