#include <QGraphicsScene>
#include <QWidget>
#include <cmath>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QTextStream>
#include <QTimeLine>
#include <qfile.h>
#include "animationball.h"

typedef std::pair<double, double>(*pointFunc)(double, double, double);

class Trajectory {
public:
	Trajectory();
	pointFunc getTrajectory(int idTrajectory);
	ArgumentsTrajectory *getArguments(int idTrajectory);
private:

	
};