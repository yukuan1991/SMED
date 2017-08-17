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
}

void HaChannel::addTask(add_task params)
{
    auto newTask = new Block (this);
    newTask->setName (params.taskName);
    newTask->setObjectName (params.taskName);
    auto totaltime =  totalTime ();
    auto width = (params.time / totaltime) * (channelWidth - 2 * channelGrayWidth);
    newTask->set_width (width);
    newTask->setFlag (QGraphicsItem::ItemIsMovable);
    newTask->setFlag (QGraphicsItem::ItemIsSelectable);
    newTask->setPos ({channelGrayWidth, 0});
}

void HaChannel::setTotalTime(qreal time)
{
    totalTime_ = time;

    emit totalTimeChanged (time);
}


} // namespace HmAnalysis
} // namespace Balance
