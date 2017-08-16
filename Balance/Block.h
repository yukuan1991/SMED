#pragma once
#include <QGraphicsObject>
#include <base/lang/not_null.h>


namespace Balance {

class Block : public QGraphicsObject
{
    Q_OBJECT
signals:
    void width_changed (qreal);
    void name_changed();
public:
    Block(QGraphicsItem * parent = null);

    void paint (QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget = null) override;

    QRectF boundingRect () const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void set_width (qreal w) { width_ = w;}
    qreal width () const noexcept { return width_; }
private:
    qreal width_ = 0;
};

} // namespace Balance

