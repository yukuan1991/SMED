#pragma once
#include <QGraphicsObject>
#include <base/lang/not_null.h>
#include <base/lang/move.hpp>
#include"Balance/parameters.hpp"

namespace Balance {

class Block : public QGraphicsObject
{
    Q_OBJECT
signals:
    void timeChanged (qreal);
    void width_changed (qreal);
    void nameChanged (const QString &);
public:
    Block(QGraphicsItem * parent = null);
    void setTime (qreal time) { time_ = time;emit timeChanged (time_); }
    qreal time () const noexcept { return time_; }

    void setName (QString name) { name_ = ::move (name); emit nameChanged (name_); }
    const QString & name () const noexcept { return name_; }

    void paint (QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget = null) override;

    QRectF boundingRect () const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void set_width (qreal w) { width_ = w;emit width_changed (width_);}
    qreal width () const noexcept { return width_; } 
    bool isDragged () const noexcept { return isDragged_; }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    bool isDragged_ = false;
    qreal width_ = 0;
    QString name_;
    qreal time_ = 0;
};

} // namespace Balance

