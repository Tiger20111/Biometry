#include "demonstration.h"
#include <QtWidgets/QApplication>
#include "camera.h"
#include "callib.h"

void demonstration() {
	Ball* ball = new Ball();
	ball->runAnimation();
	//Camera camera;
	//camera.recordVideo();
}

void recordVideo() {
	double time = 40000;
	Camera camera;
	camera.recordVideo(time);
}

void callibration() {
	std::vector<std::pair<int, int>> points;
	points.push_back({ 100, 100 });
	points.push_back({ 100, 100 });
	points.push_back({ 1570, 100 });
	points.push_back({ 2570, 800 });
	points.push_back({ 100, 800 });

	Callib* callibration = new Callib();
	callibration->runAnimation(points);

	//Camera camera;
	//camera.recordVideo();
}

void delay() {
	clock_t t0 = clock();

	for (;;) {
		clock_t t1 = clock();
		if ((t1 - t0) > 1000) break;
	}
}

void openFace() {
	//	char input_file_name[11] = "Nikita.csv";
	//	VideoProcesser v(input_file_name);
	//	pair<vector<double>, vector<double> > ans = v.solve();
}

void comparison() {

}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	callibration();
	delay();
	demonstration();
	openFace();
	comparison();


	return a.exec();
}


