#include "callib.h"

#include "mypoint.h"

#include <QDebug>
#include <QThread>


Callib::Callib() {

}

void DrawBorder1(QGraphicsScene *scene) {
	scene->setSceneRect(0, 0, 1920, 1080);
	QPen mypen = QPen(Qt::red);

	QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
	QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
	QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
	QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

	scene->addLine(TopLine, mypen);
	scene->addLine(LeftLine, mypen);
	scene->addLine(RightLine, mypen);
	scene->addLine(BottomLine, mypen);
}

void Callib::ShowOneBall(QGraphicsItemAnimation *animation, std::vector<std::pair<int, int>> points) {
	for (unsigned long i = 0; i < points.size(); i++) {
		double num = (double)((double)i / (double)(points.size() - 1));
		animation->setPosAt(num, QPointF(points[i].first, points[i].second));
	}
}

QTimeLine *Callib::runTimer() {
	QTimeLine *timer = new QTimeLine(20000);
	timer->setFrameRange(0, 100);
	timer->setUpdateInterval(5000);
	return timer;
}

void Callib::runAnimation(std::vector<std::pair<int, int>> points) {

	QGraphicsView *view;
	QGraphicsScene *scene = new QGraphicsScene();
	
	view = new QGraphicsView(scene);

	DrawBorder1(scene);
	QTimeLine* timer = runTimer();

	MyPoint *point = new MyPoint();

	QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
	animation->setItem(point);
	animation->setTimeLine(timer);

	ShowOneBall(animation, points);

	scene->addItem(point);
	view->show();
	timer->start();
	
}
