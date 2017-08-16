﻿#pragma once
#include <QGraphicsObject>
#include <base/lang/not_null.h>
#include <base/lang/move.hpp>


namespace Balance {

class Block : public QGraphicsObject
{
    Q_OBJECT
signals:
    void width_changed (qreal);
    void nameChanged (const QString &);
public:
    Block(QGraphicsItem * parent = null);

    void setName (QString name) { name_ = ::move (name); emit nameChanged (name_); }
    const QString & name () const noexcept { return name_; }

    void paint (QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget = null) override;

    QRectF boundingRect () const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void set_width (qreal w) { width_ = w;}
    qreal width () const noexcept { return width_; }
private:
    qreal width_ = 0;
    QString name_;
};

} // namespace Balance

