// app1.cpp : �������̨Ӧ�ó������ڵ㡣
//
//#pragma comment(lib,"appdll1.lib")

//#include "export___.h"
#include "stdafx.h"
#include <vector>
#include <iostream>
#include "UserData.h"
#include "employee.h"

//#include "baseTest.h"

int main()
{
	//auto ii = Admin::getPtr();
	//Admin::getPtr()->curr->say();
	//Admin::getPtr()->blah->say();
	//Admin::getPtr()->read();
	//auto jj = Admin::getPtr();
	Admin::getPtr()->getReader()->Admin_add();
	auto ii = Admin::getPtr();
	system("pause");
    return 0;
}