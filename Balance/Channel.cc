﻿#include "Balance/Channel.h"
#include <QPainter>
#include "Balance/parameters.hpp"
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QFontMetricsF>

#include "Balance/Block.h"

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

using namespace boost::adaptors;

Balance::Channel::Channel(QGraphicsItem *parent)
    :QGraphicsObject (parent)
{
    setZValue (0);
    setAcceptHoverEvents (true);
    connect (this, &Channel::objectNameChanged, [this] { update (); });
    connect (this, &Channel::fontChanged, [this] { update (); });
}

#include <QDebug>
void Balance::Channel::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget *widget)
{
    qDebug() << "paint";
    painter->setBrush (Qt::white);
    painter->setPen (Qt::NoPen);
    painter->drawRect (boundingRect ());
    Q_UNUSED (widget);
    Q_UNUSED (option);
}

QRectF Balance::Channel::boundingRect() const
{
    return QRectF (0, 0, channelWidth, channelHeight);
}

void Balance::Channel::clearItems()
{
//    for (auto block : childItems ()
//         | transformed ([] (auto && child) { return dynamic_cast<TaskBlock*> (child); })
//         | filtered ([](auto && child) { return child != null; }))
//    {
//        block->deleteLater ();
//    }

}

