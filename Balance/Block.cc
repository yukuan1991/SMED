#include "Block.h"
#include <stdexcept>
#include <QPainter>
#include"Balance/parameters.hpp"
#include<QFontMetricsF>
#include <QApplication>
#include<QStyle>
#include <QStyleOptionGraphicsItem>
namespace Balance {

Block::Block(QGraphicsItem *parent)
    :QGraphicsObject (parent)
{
    if (parent == null)
    {
        throw std::logic_error ("cannot construct without a parent");
    }
    setFlag (ItemSendsGeometryChanges, true);
    setAcceptHoverEvents (true);
    connect (this, &Block::nameChanged, [this] { update (); });
    connect (this, &Block::width_changed, [this] { update (); });
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    auto rect = boundingRect();
    painter->setFont(qApp->font());

    {
        auto pen = item->state & QStyle::State_Selected ?
                    QPen (blockSelectedBorder) : QPen (blockBorder);
        pen.setWidthF(2.0);
        painter->setPen (pen);
    }

    const auto metrics = QFontMetricsF (painter->font ());
    const auto h = metrics.height ();
    const auto w = metrics.width (name ());

    auto final_text = QString ();
    auto real_w = qreal {};

    if (w > rect.width ())
    {
        final_text = metrics.elidedText (name (), Qt::ElideMiddle, rect.width ());
        real_w = metrics.width (final_text);
    }
    else
    {
        final_text = name ();
        real_w = w;
    }

    painter->setBrush (item->state & QStyle::State_Selected ? blockSelectedArea :
                        item->state & QStyle::State_MouseOver ? blockHoveredArea :
                                                                blockArea);
    rect.setLeft (rect.left () + 2);
    rect.setRight (rect.right () - 2);
    painter->drawRect (rect);

    painter->setPen (item->state & QStyle::State_Selected ? blockArea.darker (): blockSelectedArea.darker ());

    painter->drawText (QRectF (QPointF (rect.left () + (rect.width () - real_w) / 2,
                                        rect.top () + (rect.height () - h) / 2),
                               QSizeF (real_w, h)), final_text);
}

//    Q_UNUSED (item);
//    Q_UNUSED (widget);
//    if (item->state & QStyle::State_Selected)
//    {
//        painter->setBrush (Qt::red);
//        painter->setPen (Qt::black);
//    }
//    else
//    {
//        painter->setBrush (Qt::yellow);
//    }
//    painter->setBrush (blockArea);
//    painter->setPen (Qt::NoPen);
//    painter->drawRect (boundingRect ());

QRectF Block::boundingRect() const
{
    const auto height = parentItem ()->boundingRect ().height ();
    return QRectF (0, 0, width (), height);
}

QVariant Block::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
    {

        const auto new_pos = value.toPointF ();
        const auto old_pos = pos ();
        const auto x = new_pos.x ();
        const auto old_y = old_pos.y ();
        const auto old_x = old_pos.x();
        if(0 <= x and x <= channelWidth)
        {
            const auto fixed_pos = QPointF (x, old_y);
            return fixed_pos;
        }
        else
        {
            const auto fixed_pos = QPointF(old_x,old_y);
            return fixed_pos;
        }
    }
    else
    {
        return QGraphicsItem::itemChange (change, value);
    }
}

} // namespace Balance
