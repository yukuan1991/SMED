#include "Balance/Analysis/HaChannel.h"
#include <QApplication>
#include <QFont>
#include <QFontMetricsF>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Balance/parameters.hpp"
#include "Balance/Analysis/ChannelTitle.h"
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <base/lang/scope.hpp>
#include "Balance/Block.h"
#include "Balance/GrayRectItem.h"
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QWidget>
#include <boost/range/algorithm/sort.hpp>

namespace Balance {
namespace Analysis {

using namespace boost::adaptors;
using namespace boost::range;
using boost::accumulate;
using std::end;

HaChannel::HaChannel(QGraphicsObject *parent)
    :Channel (parent)
{
    auto rightper = new GrayRectItem (0, 0, gray_width (), channelHeight, this);
    rightper->setPos (channelWidth - gray_width (), 0);

    auto leftper = new GrayRectItem (0, 0, gray_width (), channelHeight, this);
    leftper->setPos (0, 0);

    using f_ptr = void (GrayRectItem::*)(const QRectF&);
    auto p = f_ptr(&GrayRectItem::setRect);

    connect (this, &HaChannel::gray_widthChanged, leftper, p);

    setAcceptDrops(true);
}

void HaChannel::addTask(add_task params)
{
    auto newTask = new Block (this);
    newTask->setName (params.taskName);
    newTask->setObjectName (params.taskName);
    auto totaltime =  totalTime ();
    auto width = (params.time / totaltime) * (channelWidth - 2 * channelGrayWidth);
    newTask->set_width (width);
//    newTask->setFlag (QGraphicsItem::ItemIsMovable);
    newTask->setFlag (QGraphicsItem::ItemIsSelectable);
    newTask->setPos ({channelGrayWidth, 0});

    taskBlocks_.emplace_back(newTask);
}

void HaChannel::setTotalTime(qreal time)
{
    totalTime_ = time;

    emit totalTimeChanged (time);
}

void HaChannel::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("item"))
    {
        qDebug() << "HaChannel::dragEnterEvent";
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        qDebug() << "Channel::dragEnterEvent(event)";
        Channel::dragEnterEvent(event);
    }
}

void HaChannel::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("item"))
    {
        qDebug() << "HaChannel::dropEvent";
        dropAction(event);
        event->accept();
    }
    else
    {
        qDebug() << "Channel::dropEvent(event)";
        Channel::dropEvent(event);
    }
}

void HaChannel::dropAction(QGraphicsSceneDragDropEvent *event)
{
    QString obj = event->mimeData()->data("item");
    QString taskname = event->mimeData()->data("taskname");
    auto taskwidth = (event->mimeData()->data("taskwidth")).toDouble();
    qDebug() << taskname;

    event->pos();

    std::vector<Block*> unDragged;
    auto rng = childItems () | transformed ([] (auto & c) { return dynamic_cast<Block*> (c);})
            | filtered ([&] (auto && c) { return c != null and not c->isDragged (); });

    push_back (unDragged, rng);
    sort (unDragged, [] (auto && c1, auto && c2) { return c1->pos ().x () < c2->pos ().x (); });

    for (auto & it : unDragged)
    {
        qDebug () << it->pos ();
    }

    const auto pos = event->pos();
    const auto scene_pos = mapToScene(pos);

    auto block = new Block(this);
    block->setObjectName(obj);
    block->setName(taskname);
    block->set_width(taskwidth);
    block->setFlag (QGraphicsItem::ItemIsSelectable);
    const auto rect_center = block->boundingRect().center();
    auto center_pos = scene_pos - rect_center;
    block->setPos(center_pos);

}





} // namespace HmAnalysis
} // namespace Balance
