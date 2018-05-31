/*Author: Zihan Zhu*/
#include "LoginW.h"
#include <QtWidgets/QApplication>
#include <QApplication>  
#include <QWidget>  

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LoginW w;
	w.show();
	return a.exec();
}