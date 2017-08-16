#pragma once

#include <QWidget>
#include <base/lang/not_null.h>
#include <string>
namespace Ui {
class smed_main;
}
class QMdiArea;
class QMdiSubWindow;
class smed_analysis;

class smed_main : public QWidget
{
    Q_OBJECT

public:
    explicit smed_main(QWidget *parent = 0);
    virtual ~smed_main();

private:

    struct _createWindow { qreal totalTime; const QString & title; };
    not_null<smed_analysis *> createWindow(_createWindow para);
    Ui::smed_main *ui;
    void onFileNew();

    void inti_con();
};

