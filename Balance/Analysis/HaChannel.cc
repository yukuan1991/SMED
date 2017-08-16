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

namespace Balance {
namespace Analysis {

using namespace boost::adaptors;
using namespace boost::range;
using boost::accumulate;
using std::end;

HaChannel::HaChannel(QGraphicsObject *parent)
    :Channel (parent)
{
    auto rightper = new QGraphicsRectItem (0, 0, channelGrayWidth, channelHeight, this);
    rightper->setBrush (QColor (127, 127, 127, 100));
    rightper->setZValue (3);
    rightper->setPen (Qt::NoPen);
    rightper->setPos (channelWidth - channelGrayWidth, 0);

    auto leftper = new QGraphicsRectItem (0, 0, channelGrayWidth, channelHeight, this);
    leftper->setBrush (QColor (127, 127, 127, 100));
    leftper->setPen (Qt::NoPen);
    leftper->setZValue (3);
    leftper->setPos (0, 0);
}

void HaChannel::addTask(add_task params)
{
    auto newTask = new Block (this);
    newTask->setObjectName (params.taskName);
//    setTotalTime (params.time);
    newTask->set_width (40);
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
