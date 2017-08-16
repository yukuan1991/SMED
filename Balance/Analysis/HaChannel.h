#ifndef HACHANNEL_H
#define HACHANNEL_H
#include "Balance/Channel.h"
#include <QDebug>
#include <vector>
#include <utility>
#include <QString>
#include <QVariantMap>


namespace Balance {
namespace Analysis {

class HaChannel final : public Balance::Channel
{
    Q_OBJECT
signals:
    void efficiencyChanged ();
    void totalTimeChanged (qreal);
public:
    HaChannel(QGraphicsObject * parent = null);
    /// 增加任务 taskName -> 任务名称, time -> 任务用时, startAt -> 起始时间
    void addTask(add_task t) override;
    void setTotalTime (qreal time);
    qreal totalTime () const noexcept { return totalTime_; }
private:
    qreal totalTime_;
};

} // namespace HmAnalysis
} // namespace Balance

#endif // HACHANNEL_H
