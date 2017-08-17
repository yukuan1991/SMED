#pragma once
#include <QGraphicsObject>

namespace Balance {

class GrayRectItem : public QGraphicsObject
{
    Q_OBJECT
public:
    GrayRectItem(QGraphicsItem *parent = nullptr);
    GrayRectItem(const QRectF &rect, QGraphicsItem *parent = nullptr);
    GrayRectItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);


    void setRect(const QRectF &rectangle);
    void setRect(qreal x, qreal y, qreal width, qreal height);
protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option,
                QWidget * widget) override;
    QRectF boundingRect () const override;
private:
    QRectF grayRect_;
};

} // namespace Balance

