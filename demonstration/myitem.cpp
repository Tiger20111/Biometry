#include "myitem.h"
#include <iostream>
#include <fstream>

MyItem::MyItem(double startX, double startY, double size) {
	posX = startX;
	posY = startY;
	sizeBall = size;
	setPos(mapFromParent(startX, startY));
}

QRectF MyItem::boundingRect() const {
	return QRect(posX, posY, sizeBall, sizeBall);
	//left, top angle position
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QRectF rec = boundingRect();
	QBrush Brush(Qt::green);

	painter->setBrush(Qt::red);
	painter->drawEllipse(rec);
}
