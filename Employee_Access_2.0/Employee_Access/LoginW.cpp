/*Author: Zihan Zhu*/
/*The login window. Check Employee_list.txt to see default user information.*/
//#include "UserDatDLL_.h"
#include "LoginW.h"  
//#include "Employee_.h"
#include "UserData.h"
#include "employee.h"
#include "file_list.h"
#include "AdminW.h"
#include <QFileDialog>  
#include <QMessageBox>
#include <QLineEdit>
#include "sqlite3.h"
#include <string>

LoginW::LoginW(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	std::vector<Worker*> ggg = Admin::getPtr()->employees;
	auto fff = Admin::getPtr();
	Admin::getPtr()->employees.clear();//清空profile以确保返回登录界面时不会重复录入
	setStyleSheet("background-color:rgb(230,230,250)");
	QObject::connect(this, SIGNAL(success()), this, SLOT(onsuccessful()));
	QObject::connect(this, SIGNAL(admin_success()), this, SLOT(admin_onsuccessful()));
	if (!Admin::getPtr()->getReader()->FirstRead())
	{
		QMessageBox::warning(this, QObject::tr("Error"),
			QObject::tr("Cannot read employee file"));
	}
}

void LoginW::login()
{
	auto ba = Admin::getPtr();
	std::string uname = ui.lineEdit->text().toStdString();
	std::string paswd = ui.lineEdit_2->text().toStdString();
	//如果是管理员
	if (uname== Admin::getPtr()->getname() && paswd== Admin::getPtr()->getpass())
	{
		auto hhh = Admin::getPtr();
		std::vector<Worker*> tempo = Admin::getPtr()->employees;
		QMessageBox::information(this, "Admin login Info", "Admin login success.\n");
		emit admin_success();
		close();
	}
	else if ( Admin::getPtr()->login_correct(uname,paswd) )
	{
		auto bb = Admin::getPtr();
		std::vector<Worker*> tempor = Admin::getPtr()->employees;
		QMessageBox::information(this, "Login Info", "Login success.\n");
		emit success();
		close();
	}
	else
	{
		QMessageBox::information(this, 
			"Login Info", "Incorrect username or password, please retry.\n");
		ui.lineEdit->clear();
		ui.lineEdit_2->clear();
		ui.lineEdit->setFocus();
	}
}

void LoginW::onsuccessful()
{
	file_list* dlg = new file_list;
	dlg->show();
	close();
}

void LoginW::admin_onsuccessful()
{
	AdminW* adm = new AdminW;
	adm->show();
	close();
}