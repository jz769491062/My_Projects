/*Author: Zihan Zhu*/
//#pragma comment(lib,"UserDatDLL.lib")
#include <Windows.h>
#include "LoginW.h"
//#include "UserDatDLL_.h"
//#include "Employee_.h"
#include "UserData.h"
#include "employee.h"
#include <QtWidgets/QApplication>
#include <QApplication>  
#include <QWidget>  

int main(int argc, char *argv[])
{
	Admin::getPtr()->getReader()->Admin_add();
	auto ii = Admin::getPtr();
	QApplication a(argc, argv);
	LoginW w;
	w.show();
	return a.exec();
}
//TO STUDY: factory coding, lambda, RTTI