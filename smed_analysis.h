#pragma once

#include <QWidget>

namespace Ui {
class smed_analysis;
}

class smed_analysis : public QWidget
{
    Q_OBJECT

public:
    explicit smed_analysis(QWidget *parent = 0);
    ~smed_analysis();
    void setTotalTime (qreal totalTime);
    qreal totalTime () const noexcept;
private:
    void set_task_count ();
    Ui::smed_analysis *ui;
};

