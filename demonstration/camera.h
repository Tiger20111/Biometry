#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <ctime>

using namespace std;
using namespace cv;

class Camera {
public:
	void recordVideo(double time);
};