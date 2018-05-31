/*Author:Zihan Zhu*/
/*Allows Admin to modify other users' profile.*/
#include "AdminW.h"
#include "Employee.h"
#include "LoginW.h"
#include "file_manip.h"
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
	ui.tbl->setRowCount(Admin::getPtr()->employees.size());
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

	for (size_t i = 0; i < Admin::getPtr()->employees.size(); i++)
	{
		ui.tbl->setItem(i, 0, new QTableWidgetItem(Admin::getPtr()->employees[i]->getname()));
		ui.tbl->item(i, 0)->setTextAlignment(Qt::AlignCenter);
		ui.tbl->setItem(i, 1, new QTableWidgetItem(Admin::getPtr()->employees[i]->getType()));
		ui.tbl->item(i, 1)->setTextAlignment(Qt::AlignCenter);
		ui.tbl->setItem(i, 2, new QTableWidgetItem(Admin::getPtr()->employees[i]->getpasswrd()));
		ui.tbl->item(i, 2)->setTextAlignment(Qt::AlignCenter);
	}
	setAttribute(Qt::WA_DeleteOnClose);//确保析构函数执行
}

AdminW::~AdminW()
{
	update_list();//关闭admin界面时再更新一遍
}

void AdminW::update_list()
{
	QFile file("Employee_list.txt");
	if (file.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream in(&file);
		in << "Admin " << Admin::getPtr()->getname() << " " << Admin::getPtr()->getpass() << endl;//Admin不能忘
		for (size_t i = 0; i < Admin::getPtr()->employees.size(); i++)
		{
			in << Admin::getPtr()->employees[i]->getType() << " " <<
				Admin::getPtr()->employees[i]->getname() << " "
				<< Admin::getPtr()->employees[i]->getpasswrd() <<" Extra: " <<
				Admin::getPtr()->employees[i]->get_ea().size() << " ";
			if (Admin::getPtr()->employees[i]->get_ea().size()>0)
			{
				for (size_t j = 0; j < Admin::getPtr()->employees[i]->get_ea().size(); j++)
				{
					in << Admin::getPtr()->employees[i]->get_ea()[j] << " ";
				}
			}
			in << "No: " << Admin::getPtr()->employees[i]->get_ed().size() << " ";
			if (Admin::getPtr()->employees[i]->get_ed().size()>0)
			{
				for (size_t j = 0; j < Admin::getPtr()->employees[i]->get_ed().size(); j++)
				{
					in << Admin::getPtr()->employees[i]->get_ed()[j] << " ";
				}
			}
			if (i != Admin::getPtr()->employees.size() - 1)
			{//最后一行无需再创建新空行
				in << endl;
			}
		}
		file.close();
	}
	else
	{
		QMessageBox::information(this, "Cannot write file", "Wrong file name? \n");
	}

	QFile File("Employee_words.txt");
	if (File.open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream in(&File);
		std::vector<QString> workerWW = Admin::getPtr()->getWorkerWords();
		std::vector<QString> chiefWW = Admin::getPtr()->getChiefWords();
		std::vector<QString> managerWW = Admin::getPtr()->getManagerWords();//避开vector iterators incompatible
		std::vector<QString> tempWW(chiefWW.size());
		in << "Worker" << " " << workerWW.size();
		for (size_t j = 0; j < workerWW.size(); j++)
		{//输出工人能访问的文件名
			in << " " <<workerWW[j];
		}
		in << endl;

		in << "Chief" << " " << (chiefWW.size()-workerWW.size());
		auto itera = std::set_difference(chiefWW.begin(),
			chiefWW.end(), workerWW.begin(),workerWW.end(),tempWW.begin());
		tempWW.resize(itera - tempWW.begin());
		itera = tempWW.begin();
		while (itera!=tempWW.end())
		{//输出科长能访问的文件名
			in << " " << (*itera);
			itera++;
		}
		in << endl;

		in << "Manager" << " " << (managerWW.size()-chiefWW.size());
		tempWW.clear();
		tempWW.resize(managerWW.size());
		itera = std::set_difference(managerWW.begin(),managerWW.end(), chiefWW.begin(),
			chiefWW.end(), tempWW.begin());
		tempWW.resize(itera - tempWW.begin());
		while (itera != tempWW.end())
		{//输出经理能访问的文件名
			in << " " << (*itera);
			itera++;
		}
		File.close();
	}
	else
	{
		QMessageBox::information(this, "Cannot write file", "Wrong file name? \n");
	}
}

void AdminW::add_user()
{
	//添加新成员至employees
	Admin::getPtr()->Createworkerbyname(ui.typeBox->currentText(), ui.lineEdit_name->text(),
		ui.lineEdit_pswd->text(), {}, {});//新用户只有默认访问

	ui.tbl->setRowCount(Admin::getPtr()->employees.size());//更新行数
	ui.tbl->setItem(Admin::getPtr()->employees.size() - 1, 0,
		new QTableWidgetItem(ui.lineEdit_name->text()));
	ui.tbl->item(Admin::getPtr()->employees.size() - 1, 0)->setTextAlignment(Qt::AlignCenter);
	ui.tbl->setItem(Admin::getPtr()->employees.size() - 1, 1,
		new QTableWidgetItem(ui.typeBox->currentText()));
	ui.tbl->item(Admin::getPtr()->employees.size() - 1, 1)->setTextAlignment(Qt::AlignCenter);
	ui.tbl->setItem(Admin::getPtr()->employees.size() - 1, 2,
		new QTableWidgetItem(ui.lineEdit_pswd->text()));
	ui.tbl->item(Admin::getPtr()->employees.size() - 1, 2)->setTextAlignment(Qt::AlignCenter);
	QMessageBox::information(this, "Add user Info", "User creation success.\n");
}

void AdminW::delete_user()
{
	//将其从表格中删除
	ui.tbl->removeRow(ui.tbl->currentRow());
	//从profile删除，并重写txt文件
	auto it = Admin::getPtr()->employees.begin() + ui.tbl->currentRow();
	Admin::getPtr()->employees.erase(it);
	QMessageBox::information(this, "Delete user Info", "user delete success.\n");
}

void AdminW::changeinfo()
{
	int curr_row = ui.tbl->currentRow();
	int curr_col = ui.tbl->currentColumn();
	if (curr_col ==2)
	{
		Admin::getPtr()->employees[curr_row]->getpasswrd() = ui.tbl->item(curr_row, curr_col)->text();
	}
	else if (curr_col==1)
	{
		if (ui.tbl->item(curr_row,curr_col)->text()!="Worker" && 
			ui.tbl->item(curr_row, curr_col)->text() != "Chief"&&
			ui.tbl->item(curr_row, curr_col)->text() != "Manager"&&
			ui.tbl->item(curr_row, curr_col)->text() != "Admin")
		{
			QMessageBox::information(this, "Invalid usertype", "Usertype:Worker,Chief,Manager,Admin. \n");
			return;
		}
		Admin::getPtr()->employees[curr_row]->getType() = ui.tbl->item(curr_row, curr_col)->text();
	}
	else if (curr_col == 0)
	{
		Admin::getPtr()->employees[curr_row]->getname() = ui.tbl->item(curr_row, curr_col)->text();
	}
}

void AdminW::adm_return_login()
{
	update_list();
	LoginW* logW = new LoginW;
	logW->show();
	close();
}

void AdminW::open_manip()
{
	int cur_row = ui.tbl->currentRow();
	int cur_col = ui.tbl->currentColumn();
	if (ui.tbl->item(cur_row, 1)->text() == "Admin")
	{
		QMessageBox::information(this, "Invalid usertype", "Admin doesn't access files. \n");
		return;
	}
	bool temp = Admin::getPtr()->login_correct(ui.tbl->item(cur_row, 0)->text(),
		ui.tbl->item(cur_row, 2)->text());//temp 肯定是true。只是借用login_correct换一下current_worker
	update_list();//确保上次更改被记录
	file_manip* man = new file_manip;
	man->show();
}
