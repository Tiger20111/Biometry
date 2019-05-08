#include "animationball.h"
#include "demonstration.h"
#include "myitem.h"


void DrawBorder(QGraphicsScene *scene, double radius, double posWindowX, double posWindowY) {
	scene->setSceneRect(0, 0, posWindowX, posWindowY);
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


Ball::Ball() {
	//time = radius * 10;
	//frequency = (2 * 3.14 * numTurn) / time;

	//startX = posWindowX / 2;
	//startY = posWindowY / 2;

}

QTimeLine *Ball::runTimer() {
	QTimeLine *timer = new QTimeLine(30000);
	timer->setFrameRange(0, 100);
	timer->setUpdateInterval(10);
	return timer;
}

void Ball::setTrajectoryParametrs(int idTrajectory) {
	Trajectory* trajectory = new Trajectory();
	ArgumentsTrajectory* arguments = trajectory->getArguments(idTrajectory);

//	numTurn = arguments->numTurn;
	radius = arguments->radius;
	frequency = arguments->frequency;
	time = arguments->time;
	startX = arguments->startX;	
	startY = arguments->startY;
}

void Ball::runTrajectory(QGraphicsItemAnimation *animation,	int idTrajectory) {
	std::pair<double, double>next_point(0, 0);
	double step = 0;

	Trajectory* trajectory = new Trajectory();
	auto pointFunc = trajectory->getTrajectory(idTrajectory);

	QFile fileOut(outputFile);
	QTextStream writeStream(&fileOut);
	writeStream << sin(1.57) << "\n";
	if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	for (int i = 0; i < (int)time; ++i) {
		step = ((double)i / time);
		next_point = pointFunc((double)i, radius, frequency);
		writeStream <<(i / time) << " " << next_point.first << " " << next_point.second << "\n";
		animation->setPosAt(step, QPointF(next_point.first, next_point.second));
	}
	fileOut.close();
}



void Ball::runAnimation() {
	QGraphicsView *view;
	QGraphicsScene *scene = new QGraphicsScene();
	view = new QGraphicsView(scene);

	setTrajectoryParametrs(0);

	DrawBorder(scene, radius, posWindowX, posWindowY);

	QTimeLine* timer = runTimer();

	MyItem *item = new MyItem(startX, startY, sizeBall);
	QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
	animation->setItem(item);
	animation->setTimeLine(timer);

	runTrajectory(animation, 2);

	scene->addItem(item);
	view->show();
	timer->start();

}


//std::pair<double, double> (*pointFunc)(std::pair<double, double>) = NULL;
//pointFunc = &NextPointCos;
//CircleMotionFromFile(animation, pointFunc, inputFile);
