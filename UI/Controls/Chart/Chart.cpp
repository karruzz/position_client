#include <UI/Controls/Chart/Chart.h>
#include "LineNode.h"

Chart::Chart(QQuickItem *parent)
    : QQuickItem(parent),
      _min(-0.1), _max(0.1), _color("red")
{
    setFlag(ItemHasContents, true);
}

void Chart::setPoints(const QVector<QPointF> &points)
{
    if (points.isEmpty()) return;
    _points = points;

    update();
}

class ChartNode : public QSGNode
{
    public:
        LineNode *line;
};

QSGNode *Chart::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    ChartNode *n = static_cast<ChartNode *>(oldNode);

    QRectF rect = boundingRect();

    if (rect.isEmpty()) {
        delete n;
        return 0;
    }

    if (!n) {
        n = new ChartNode();
        n->line = new LineNode(_points.size()+1, _color);
        n->appendChildNode(n->line);
    }
    else
    {
        n->line->alloc(_points.size());
    }

    n->line->setPoints(rect, _points, _max, _min);

    return n;
}
