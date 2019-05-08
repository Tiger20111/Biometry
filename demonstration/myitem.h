
#ifndef MYITEM_H
#define MYITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class MyItem : public QGraphicsEllipseItem {
	public:
		MyItem(double StartX, double StartY, double size);
		QRectF boundingRect() const;
		void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option, QWidget *widget);

	private:
		double posX;
		double posY;
		double sizeBall;
};

#endif // MYITEM_H
