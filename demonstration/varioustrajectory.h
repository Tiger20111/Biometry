#include <cmath>
#include <QWidget>
#include "animationball.h"

std::pair<double, double> NextPointCircle(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsCircle();

std::pair<double, double> NextPointSpiral(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsSpiral();

std::pair<double, double> NextPointLissazi(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsLissazi();

std::pair<double, double> NextPointLove(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsLove();



//class Circle {
//public:
//	typedef std::pair<double, double>(*pointFunc)(double, double, double);
//	Circle::pointFunc getFunc();
//	ArgumentsTrajectory getArguments();
//private:
//	std::pair<double, double> NextPointCircle(double time, double radius, double frequency);
//};

