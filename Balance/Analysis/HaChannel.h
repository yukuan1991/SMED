#ifndef HACHANNEL_H
#define HACHANNEL_H
#include "Balance/Channel.h"
#include <QDebug>
#include <vector>
#include <utility>
#include <QString>
#include <QVariantMap>
#include "Balance/parameters.hpp"

namespace Balance {
namespace Analysis {

class HaChannel final : public Balance::Channel
{
    Q_OBJECT
signals:
    void efficiencyChanged ();
    void totalTimeChanged (qreal);
    void gray_widthChanged (const QRectF &rectangle);
public:
    HaChannel(QGraphicsObject * parent = null);
    /// 增加任务 taskName -> 任务名称, time -> 任务用时, startAt -> 起始时间
    void addTask(add_task t) override;
    void setTotalTime (qreal time);
    qreal totalTime () const noexcept { return totalTime_; }

    void set_gray_width (qreal w) {
        qDebug() << "gray_width"; gray_width_ = w;emit gray_widthChanged (QRectF(0, 0, gray_width_, channelHeight));}
    qreal gray_width () const noexcept { return gray_width_; }
private:
    qreal totalTime_;
<<<<<<< HEAD
    qreal gray_width_ = 200;
=======
    qreal gray_width_ = 100;
>>>>>>> sponge
};

} // namespace HmAnalysis
} // namespace Balance

#endif // HACHANNEL_H
