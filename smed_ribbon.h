#pragma once
#include"ribbon.h"

class smed_ribbon : public ribbon
{
     Q_OBJECT
signals:
    void file_import();
public:
    smed_ribbon(QWidget * parent = nullptr);
private:
    void inti_con();

    ribbon_tool * import = nullptr, * create = nullptr, * copy = nullptr, * paste = nullptr, * del = nullptr;
};
