//Author: Zihan Zhu
#include "calculator.h"
#include <QtWidgets/QApplication>
//#include <crtdbg.h>
int main(int argc, char *argv[])
{
	QApplication::setStyle("Macintosh");
	QApplication app(argc, argv);
	Calculator w;
	w.setFocusPolicy(Qt::StrongFocus);
	w.setMinimumSize(100, 100);
	w.setMaximumSize(800, 800);
	w.show();
	return app.exec();
	//_CrtDumpMemoryLeaks();
}

/*
1.把所有操作读下来
2.转换成后缀：check()重新编排符号位置
*/