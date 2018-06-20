/*Author:Zihan Zhu*/
/*Allows Admin to modify other users' profile.*/
#include "sqlite3.h"
//#include "UserDatDLL_.h"
#include "AdminW.h"
//#include "Employee_.h"
#include "UserData.h"
#include "employee.h"
#include "LoginW.h"
#include "file_manip.h"
#include "stdlib.h"
#include <cstdio>
#include <QFile>
#include <QComboBox>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>

AdminW::AdminW(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setStyleSheet("background-color:rgb(230,230,250)");
	QFont font("Times New Roman", 14, 63);
	ui.label->setFont(font);
	QFont font_title("Times New Roman", 14, 50);
	ui.label_title->setFont(font);
	ui.typeBox->insertItem(0, "Worker");
	ui.typeBox->insertItem(1, "Chief");
	ui.typeBox->insertItem(2, "Manager");
	ui.tbl->setColumnCount(3);
	ui.tbl->setRowCount(Admin::getPtr()->employees.size() + 1);
	ui.tbl->setSelectionMode(QAbstractItemView::SingleSelection);
	QStringList header;
	header << "Name" << "Type" << "Password";
	ui.tbl->setHorizontalHeaderLabels(header);
	ui.tbl->setColumnWidth(0, 66);
	ui.tbl->setColumnWidth(1, 66);
	ui.tbl->setColumnWidth(2, 66);
	//单击已选中格子（慢双击）即可修改数据。双击就成修改文件权限了
	ui.tbl->setEditTriggers(QAbstractItemView::SelectedClicked);
	ui.Button_delete->hide();//初始隐藏删除模块，直到一个用户被选中

	//Admin固定出现在第一行
	ui.tbl->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->getname())));
	ui.tbl->item(0, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tbl->setItem(0, 1, new QTableWidgetItem("Admin"));
	ui.tbl->item(0, 1)->setTextAlignment(Qt::AlignCenter);
	ui.tbl->item(0, 1)->setFlags(ui.tbl->item(0, 1)->flags() & (~Qt::ItemIsEditable));//Admin type格无法被编辑
	ui.tbl->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->getpass())));
	ui.tbl->item(0, 2)->setTextAlignment(Qt::AlignCenter);

	for (size_t i = 0; i < Admin::getPtr()->employees.size(); i++)
	{
		ui.tbl->setItem(i + 1, 0, new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->employees[i]->getname())));
		ui.tbl->item(i + 1, 0)->setTextAlignment(Qt::AlignCenter);
		ui.tbl->setItem(i + 1, 1, new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->employees[i]->getType())));
		ui.tbl->item(i + 1, 1)->setTextAlignment(Qt::AlignCenter);
		ui.tbl->setItem(i + 1, 2, new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->employees[i]->getpasswrd())));
		ui.tbl->item(i + 1, 2)->setTextAlignment(Qt::AlignCenter);
	}
	loadFinished = true;
	setAttribute(Qt::WA_DeleteOnClose);//确保析构函数执行
}

AdminW::~AdminW()
{
	//关闭admin界面时再更新一遍
	if (Admin::getPtr()->getReader()->update() == false)
	{
		QMessageBox::information(this, "Cannot write file", "Wrong file name? \n");
		qDebug() << "Cannot write file" << endl;
	}
}

void AdminW::add_user()
{
	Manager mgr;
	//添加新成员至employees
	Admin::getPtr()->Createworkerbyname(ui.typeBox->currentText().toStdString(), ui.lineEdit_name->text().toStdString(),
		ui.lineEdit_pswd->text().toStdString(), {}, {});//新用户只有默认访问
	loadFinished = false;
	ui.tbl->setRowCount(Admin::getPtr()->employees.size()+1);//更新行数
	ui.tbl->setItem(Admin::getPtr()->employees.size(), 0,
		new QTableWidgetItem(ui.lineEdit_name->text()));
	ui.tbl->item(Admin::getPtr()->employees.size(), 0)->setTextAlignment(Qt::AlignCenter);
	ui.tbl->setItem(Admin::getPtr()->employees.size(), 1,
		new QTableWidgetItem(ui.typeBox->currentText()));
	ui.tbl->item(Admin::getPtr()->employees.size(), 1)->setTextAlignment(Qt::AlignCenter);
	ui.tbl->setItem(Admin::getPtr()->employees.size(), 2,
		new QTableWidgetItem(ui.lineEdit_pswd->text()));
	ui.tbl->item(Admin::getPtr()->employees.size(), 2)->setTextAlignment(Qt::AlignCenter);
	loadFinished = true;

	Admin::getPtr()->getReader()->add();
}

void AdminW::delete_user()
{	//从文件中删除
	Admin::getPtr()->getReader()->del(ui.tbl->currentRow());
	//从employees删除
	auto it = Admin::getPtr()->employees.begin() + ui.tbl->currentRow()-1;
	Admin::getPtr()->employees.erase(it);
	//将其从表格中删除
	ui.tbl->removeRow(ui.tbl->currentRow());
}

void AdminW::changeinfo()
{
	if (loadFinished)
	{
		int curr_row = ui.tbl->currentRow();
		int curr_col = ui.tbl->currentColumn();
		QString Command;
		if (curr_col == 2)
		{
			if (ui.tbl->item(curr_row, 1)->text() != "Admin")
			{
				Admin::getPtr()->employees[curr_row - 1]->setpasswrd(ui.tbl->item(curr_row, curr_col)->text().toStdString());
			}
			Admin::getPtr()->getReader()->change(curr_col, 
				ui.tbl->item(curr_row, 1)->text().toStdString(),
				ui.tbl->item(curr_row, 0)->text().toStdString(),
				ui.tbl->item(curr_row, 2)->text().toStdString());
		}
		else if (curr_col == 1)
		{
			if (ui.tbl->item(curr_row, curr_col)->text() != "Worker" &&
				ui.tbl->item(curr_row, curr_col)->text() != "Chief"&&
				ui.tbl->item(curr_row, curr_col)->text() != "Manager")
			{
				QMessageBox::information(this, "Invalid usertype", "Usertype:Worker,Chief,Manager. \n");
				return;
			}
			//添加新成员至employees
			Admin::getPtr()->Createworkerbyname(ui.tbl->item(curr_row, curr_col)->text().toStdString(),
				ui.tbl->item(curr_row, 0)->text().toStdString(),
				ui.tbl->item(curr_row, 2)->text().toStdString(), {}, {});//新用户只有默认访问

			ui.tbl->setRowCount(Admin::getPtr()->employees.size() + 1);//更新行数
			loadFinished = false;
			ui.tbl->setItem(Admin::getPtr()->employees.size(), 0,
				new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getname())));
			ui.tbl->item(Admin::getPtr()->employees.size(), 0)->setTextAlignment(Qt::AlignCenter);
			ui.tbl->setItem(Admin::getPtr()->employees.size(), 1,
				new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getType())));
			ui.tbl->item(Admin::getPtr()->employees.size(), 1)->setTextAlignment(Qt::AlignCenter);
			ui.tbl->setItem(Admin::getPtr()->employees.size(), 2,
				new QTableWidgetItem(QString::fromStdString(Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getpasswrd())));
			ui.tbl->item(Admin::getPtr()->employees.size(), 2)->setTextAlignment(Qt::AlignCenter);
			Admin::getPtr()->getReader()->change(curr_col,
				ui.tbl->item(curr_row, 1)->text().toStdString(),
				ui.tbl->item(curr_row, 0)->text().toStdString(),
				ui.tbl->item(curr_row, 2)->text().toStdString());
			//删除旧成员
			delete_user();
			loadFinished = true;
		}
		else if (curr_col == 0)
		{
			if (ui.tbl->item(curr_row, 1)->text() != "Admin")
			{
				Admin::getPtr()->employees[curr_row - 1]->setname(ui.tbl->item(curr_row, curr_col)->text().toStdString());
			}
			Admin::getPtr()->getReader()->change(curr_col,
				ui.tbl->item(curr_row, 1)->text().toStdString(),
				ui.tbl->item(curr_row, 0)->text().toStdString(),
				ui.tbl->item(curr_row, 2)->text().toStdString());
		}
	}
}

void AdminW::adm_return_login()
{
	if (Admin::getPtr()->getReader()->update() == false)
	{
		QMessageBox::information(this, "Cannot write file", "Wrong file name? \n");
		return;
	}
	LoginW* logW = new LoginW;
	logW->show();
	close();
}

void AdminW::open_manip()
{
	int cur_row = ui.tbl->currentRow();
	int cur_col = ui.tbl->currentColumn();
	if (cur_row==0)//如果是admin的位置
	{
		QMessageBox::information(this, "Invalid usertype", "Admin doesn't access files. \n");
		return;
	}
	bool loginsucc = Admin::getPtr()->login_correct(ui.tbl->item(cur_row, 0)->text().toStdString(),
		ui.tbl->item(cur_row, 2)->text().toStdString());//肯定是true。只是借用login_correct换一下current_worker
	if (!loginsucc)
	{
		QMessageBox::information(this, "Error", "Cannot get current worker's files. \n");
		return;
	}
	if (Admin::getPtr()->getCurrentWorker() != NULL)
	{
		if (Admin::getPtr()->getReader()->update()==false)
		{
			QMessageBox::information(this, "Cannot write file", "Wrong file name? \n");
			return;
		}
	}
	file_manip* man = new file_manip;
	man->show();
}
