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
1.�����в���������
2.ת���ɺ�׺��check()���±��ŷ���λ��
*/