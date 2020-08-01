#include "CameraApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CameraApp w;
	w.show();
	return a.exec();
}


