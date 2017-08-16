#include "smed_analysis.h"
#include "ui_smed_analysis.h"
#include "Balance/Analysis/HaChannel.h"
using namespace Balance::Analysis;
smed_analysis::smed_analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::smed_analysis)
{
    ui->setupUi(this);
    connect (ui->view->bar (), &HaChannel::totalTimeChanged, [this] (qreal time){
        ui->label_6->setText (QString::number (time));
    });
}

smed_analysis::~smed_analysis()
{
    delete ui;
}

void smed_analysis::setTotalTime(qreal totalTime)
{
    ui->view->setTotalTime (totalTime);
}

qreal smed_analysis::totalTime() const noexcept
{
    return ui->view->totalTime ();
}

void smed_analysis::set_task_count()
{

}
