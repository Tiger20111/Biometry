#include "trajectory.h"
#include "varioustrajectory.h"

typedef std::pair<double, double>(*pointFunc)(double, double, double);

Trajectory::Trajectory() {

}


pointFunc Trajectory::getTrajectory(int idTrajectory) {
	switch (idTrajectory) {
	case 0:
		return &NextPointCircle;
	case 1:
		return &NextPointSpiral;
	case 2:
		return &NextPointLissazi;
	case 3:
		return &NextPointLove;
	default:
		return nullptr;
	}
}

ArgumentsTrajectory *Trajectory::getArguments(int idTrajectory) {
	switch (idTrajectory) {
	case 0:
		return ArgumentsCircle();
	case 1:
		return ArgumentsSpiral();
	case 2:
		return ArgumentsLissazi();
	case 3:
		return ArgumentsLove();
	}
}


//void CircleMotionFromFile(QGraphicsItemAnimation *animation, std::pair<double, double>(*funcPoint)(std::pair<double, double>), QString input) {
//	std::pair<double, double>next_point(0, 0);
//	QFile fileOut(input);
//	QTextStream readStream(&fileOut);
//	for (int i = 0; i < 26; ++i) {
//		readStream >> next_point.first >> next_point.second;
//		animation->setPosAt(i / 26.0, QPointF(next_point.first, next_point.second));
//	}
//}
