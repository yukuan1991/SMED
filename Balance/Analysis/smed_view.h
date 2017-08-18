#pragma once
#include <QGraphicsView>
#include <memory>
#include <base/lang/scope.hpp>
#include <vector>
#include <base/lang/not_null.h>
#include <base/utils/heap_buf.hpp>
#include <string_view>
#include <QMetaType>



namespace Balance {
class ResourceScene;
class Channel;
class Block;
namespace Analysis {
class HaChannel;


using std::make_unique;
using std::end;
using std::vector;
using std::make_pair;
using std::pair;


class smed_view : public QGraphicsView
{
    Q_OBJECT
public:
    void barClicked(Channel * bar);
    void blockClicked (Block * block);
    explicit smed_view(QWidget *parent = 0);
    void mouseReleaseEvent (QMouseEvent * event) override;
    ~smed_view() override;
    void setTotalTime (qreal totalTime);
    qreal totalTime () const noexcept;
    const HaChannel * bar () const noexcept;
private:
    HaChannel * smed_channel_ = nullptr;
    std::unique_ptr<Balance::ResourceScene> scene_;
};
} // namespace AmAnalysis
} // namespace Balance
