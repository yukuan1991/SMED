#include "smed_ribbon.h"

#include <array>
#include <base/lang/move.hpp>
#include <QDebug>
#include <QButtonGroup>
#include <QMessageBox>
using namespace std;
smed_ribbon::smed_ribbon(QWidget * parent )
    :ribbon(parent)
{
    vector<ui_group> edit;
    edit.resize (1);
    {
        vector<ui_group> edit;
        edit.resize (2);
        button_cell b;
        b.add ("新建", QPixmap ("png/新建.png"), create);
        b.add ("复制", QPixmap ("png/复制.png"), copy);
        b.add ("粘贴", QPixmap ("png/粘贴.png"), paste);
        b.add ("剪切", QPixmap ("png/剪切.png"), del);
        b.set_title ("第一类");
        edit.at (0) = ::move (b);

        b.add ("导入", QPixmap ("png/导入.png"), import);
        b.set_title ("第二类");
        edit.at (1) = ::move (b);
        add_tab (edit, "编辑");
    }
    inti_con();
}
void smed_ribbon::inti_con()
{
    connect (import, &ribbon_tool::clicked, [] { QMessageBox::information (nullptr, "新建", "新建点击"); });
    connect (this, &smed_ribbon::set_enabled, import, &ribbon_tool::setEnabled);
    connect (this, &smed_ribbon::set_enabled, create, &ribbon_tool::setEnabled);
    connect (this, &smed_ribbon::set_enabled, copy, &ribbon_tool::setEnabled);
    connect (this, &smed_ribbon::set_enabled, paste, &ribbon_tool::setEnabled);
    connect (this, &smed_ribbon::set_enabled, del, &ribbon_tool::setEnabled);
}
