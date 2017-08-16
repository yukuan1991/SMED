#include "smed_main.h"
#include "ui_smed_main.h"
#include "smed_analysis.h"
#include <QMdiSubWindow>
#include <QInputDialog>

using namespace std;

smed_main::smed_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::smed_main)
{
    ui->setupUi(this);
    inti_con();
    ui->mdi->setViewMode (QMdiArea::TabbedView);
}

smed_main::~smed_main()
{
    delete ui;
}

not_null<smed_analysis *> smed_main::createWindow(smed_main::_createWindow param)
{
    auto view = new smed_analysis (this);
    view->setAttribute (Qt::WA_DeleteOnClose, true);

    auto sub = ui->mdi->addSubWindow (view);
    sub->setWindowTitle (param.title);
    view->setTotalTime (param.totalTime);

    view->setWindowState (Qt::WindowMaximized);
    return view;
}

void smed_main::onFileNew()
{
    bool isOk = false;
    auto totalTime = QInputDialog::getDouble (this, "总时间", "请输入总时间", 10, 0, 100000, 2, &isOk);
    if (isOk)
    {
        createWindow ({.totalTime = totalTime, .title = "未命名"});
    }
}

void smed_main::inti_con()
{
    connect (ui->rib, &ribbon::file_new, this, &smed_main::onFileNew);
}

