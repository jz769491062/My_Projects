/*Author: Zihan Zhu*/
/*The login window. Check Employee_list.txt to see default user information.*/
#include "LoginW.h"  
#include "Employee.h"
#include "file_list.h"
#include "AdminW.h"
#include <QFileDialog>  
#include <QMessageBox>
#include <QLineEdit>

LoginW::LoginW(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Admin::getPtr()->employees.clear();//清空profile以确保返回登录界面时不会重复录入
	setStyleSheet("background-color:rgb(230,230,250)");
	QObject::connect(this, SIGNAL(success()), this, SLOT(onsuccessful()));
	QObject::connect(this, SIGNAL(admin_success()), this, SLOT(admin_onsuccessful()));
	QFile file("Employee_list.txt");
	if (!file.open(QFile::ReadWrite | QFile::Text))
	{//读取失败的话，给警告
		QMessageBox::warning(this, tr("Error"), tr("Cannot read employee file:%1").arg(file.errorString()));
	}
	QTextStream in(&file);
	QString type, name, password, file_name,buffer;
	while (!in.atEnd())
	{
		std::vector<QString> extra,no;
		in >> type;
		in >> name;
		in >> password;
		if (type == "Admin")
		{
			Admin::getPtr()->setname(name);
			Admin::getPtr()->setpass(password);
		}
		else if (type != "")
		{//如果不是Admin或空行
			in >> buffer;
			int ex_count, no_count;
			in >> ex_count;
			if (ex_count!=0)
			{
				for (size_t i = 0; i < ex_count; i++)
				{
					in >> buffer;
					extra.push_back(buffer);
				}
			}
			in >> buffer;
			in >> no_count;
			if (no_count != 0)
			{
				for (size_t i = 0; i < no_count; i++)
				{
					in >> buffer;
					no.push_back(buffer);
				}
			}
			Admin::getPtr()->Createworkerbyname(type, name, password,extra,no);
		}
	}
}

void LoginW::login()
{
	QString uname = ui.lineEdit->text();
	QString paswd = ui.lineEdit_2->text();
	//如果是管理员
	if (uname== Admin::getPtr()->getname() && paswd== Admin::getPtr()->getpass())
	{
		QMessageBox::information(this, "Admin login Info", "Admin login success.\n");
		emit admin_success();
		close();
	}
	else if ( Admin::getPtr()->login_correct(uname,paswd) )
	{
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