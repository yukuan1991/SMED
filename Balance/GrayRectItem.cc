#include "GrayRectItem.h"
#include <QPainter>

namespace Balance {

GrayRectItem::GrayRectItem(QGraphicsItem *parent)
    : QGraphicsObject (parent)
{
    setZValue(3);
}

GrayRectItem::GrayRectItem(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsObject (parent), grayRect_(rect)
{

}

GrayRectItem::GrayRectItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsObject (parent), grayRect_(QRectF(x, y, width, height))
{

}

void GrayRectItem::setRect(const QRectF &rectangle)
{
    grayRect_ = rectangle;
    update();
}

void GrayRectItem::setRect(qreal x, qreal y, qreal width, qreal height)
{
    grayRect_ = QRectF(x, y, width, height);
}

void GrayRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush (QColor (127, 127, 127, 100));
    painter->setPen (Qt::NoPen);
    painter->drawRect(grayRect_);

    update();
}

QRectF GrayRectItem::boundingRect() const
{
    return grayRect_;
}

} // namespace Balance
