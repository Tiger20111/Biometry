
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class MyPoint : public QGraphicsEllipseItem {
public:
	MyPoint();
	QRectF boundingRect() const;
	void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option, QWidget *widget);

};
