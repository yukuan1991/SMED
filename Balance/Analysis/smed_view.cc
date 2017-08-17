#include "smed_view.h"
#include<QWidget>
#include "Balance/ResourceScene.h"
#include "Balance/Channel.h"
#include "Balance/parameters.hpp"
#include <QMouseEvent>
#include<QMenu>
#include<QCursor>
#include<QDialog>
#include<QMessageBox>
#include<QInputDialog>
#include"Balance/Analysis/AddTaskDlg.h"
#include"Balance/Analysis/HaChannel.h"
#include"Balance/Block.h"
namespace Balance {
namespace Analysis {
smed_view::smed_view(QWidget *parent)
    :QGraphicsView (parent)
    ,scene_ ([this] {auto s = make_unique<ResourceScene> (); this->setScene (s.get ()); return s; } ())
{
    scene_->setSceneRect (0, 0, 1024, 300);
    setRenderHint (QPainter::Antialiasing);
    setMouseTracking (true);
    setViewportUpdateMode (QGraphicsView::FullViewportUpdate);


    auto item = new HaChannel;
    scene_->addItem (item);
    item->setObjectName ("任务");
    human_ = item;
    item->setPos (scene_->sceneRect ().center () - item->boundingRect ().center ());

//        conns.push_back (connect (this, &HaView::totalTimeChanged, item, &HaChannel::setTotalTime));
//        conns.push_back (connect (item, &HaChannel::efficiencyChanged, this, &HaView::statusChanged));
//        conns.push_back (connect (item, &HaChannel::objectNameChanged, this, &HaView::statusChanged));

}

void smed_view::barClicked(Channel *bar)
{
     QMenu menu;
     auto addTask = menu.addAction ("增加作业");
     auto clearItems = menu.addAction ("清空作业");

     connect (addTask, &QAction::triggered, [&]
     {
         AddTaskDlg dlg (this);
         const auto res = dlg.exec ();

         if (QDialog::Accepted != res)
         {
             return;
         }

         const auto time = dlg.taskTime ();
         const auto name = dlg.taskName ();

         if (time < 0.1)
         {
             QMessageBox::information (this, "增加作业", "作业时间为" + QString::number (time) + " 时间太小 无法添加");
             return;
         }

         bar->addTask ({.taskName = name, .time = time});
     });
     menu.exec (QCursor::pos ());
}

void smed_view::blockClicked(Block *block)
{
    QMenu menu (this);
    connect (menu.addAction ("删除作业"), &QAction::triggered, [this, block] {
        block->deleteLater ();
    });
    connect (menu.addAction ("设置作业名"), &QAction::triggered, [this, block] {
        bool isOk = false;
        const auto text = QInputDialog::getText (this, "作业名", "新作业名", QLineEdit::Normal, block->objectName (), &isOk);
        if (isOk)
        {
            block->setName (text);
        }
    });
    connect (menu.addAction ("设置作业时间"), &QAction::triggered, [this, block] {
        bool isOk = false;
        const auto time = QInputDialog::getDouble (this, "作业时间", "新作业时间", block->time (), 0.0, 1000, 2, &isOk);
        if (isOk)
        {
            block->setTime (time);
            block->set_width (time / totalTime () * (channelWidth - 2 * channelGrayWidth));
        }
    });
    menu.exec (QCursor::pos ());
}

void smed_view::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent (event);
    const auto button = event->button ();
    if (button != Qt::RightButton)
    {
        return;
    }
    const auto item = itemAt (event->pos ());
    if (auto bar = dynamic_cast<HaChannel *> (item); bar != null)
    {
        barClicked (bar);
        return;
    }
    if (auto block = dynamic_cast<Block *> (item); block != null)
    {
        blockClicked (block);
    }
}

smed_view::~smed_view()
{

}

void smed_view::setTotalTime(qreal totalTime)
{
    human_->setTotalTime (totalTime);
}

qreal smed_view::totalTime() const noexcept
{
    return human_->totalTime ();
}

const HaChannel *smed_view::bar() const noexcept
{
    return human_;
}

} // namespace AmAnalysis
} // namespace Balance
