
#include <QGraphicsScene>
#include <QWidget>
#include <cmath>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QTextStream>
#include <QTimeLine>
#include <qfile.h>

class Callib {
public:
	Callib();
	void runAnimation(std::vector<std::pair<int, int>> points);
private:
	QTimeLine *runTimer();
	void ShowOneBall(QGraphicsItemAnimation *animation, std::vector<std::pair<int, int>> points);


};

