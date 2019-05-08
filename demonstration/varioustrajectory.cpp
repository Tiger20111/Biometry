#include "varioustrajectory.h"

std::pair<double, double> NextPointCircle(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	new_point.first = radius * sin(frequency * time);
	new_point.second = radius * cos(frequency * time);
	return new_point;
}

ArgumentsTrajectory *ArgumentsCircle() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 1;
	arguments->radius = 200;
//	arguments->time = arguments->radius * 10;
	arguments->time = 1000;
	//arguments->frequency = (2 * 3.14 * (arguments->radius)) / (arguments->time / arguments->numTurn);
	arguments->frequency = 0.01;
	arguments->startX = 400;
	arguments->startY = 400;
	return arguments;
}

std::pair<double, double> NextPointSpiral(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	new_point.first = radius * sin(3 * frequency * time + 1.57);
	new_point.second = radius * sin(2 * frequency * time);
	return new_point;
}

ArgumentsTrajectory *ArgumentsSpiral() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 1;
	arguments->radius = 100;
	arguments->frequency = 0.01;
	arguments->time = 1000;
	arguments->startX = 400;
	arguments->startY = 400;
	return arguments;
}

std::pair<double, double> NextPointLissazi(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	new_point.first = radius * sin(frequency * (time + (3.14 / 2)));
	new_point.second = radius * cos(2 * frequency * time);
	return new_point;
}

ArgumentsTrajectory *ArgumentsLissazi() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 0;
	arguments->radius = 0;
	arguments->frequency = 0;
	arguments->time = 0;
	arguments->startX = 0;
	arguments->startY = 0;
	return arguments;
}

std::pair<double, double> NextPointLove(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	new_point.first = radius * (16 * pow(sin(frequency * time), 3));
	new_point.second = radius * (13 * cos(frequency * time) - 5 * cos(2 * frequency * time) - 2 * cos(3 * frequency * time) - cos(4 * frequency * time));
	return new_point;
}

ArgumentsTrajectory *ArgumentsLove() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 0;
	arguments->radius = 0;
	arguments->frequency = 0;
	arguments->time = 0;
	arguments->startX = 0;
	arguments->startY = 0;
	return arguments;
}

//Circle::pointFunc Circle::getFunc() {
//	return &Circle::NextPointCircle;
//}