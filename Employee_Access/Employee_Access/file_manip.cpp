/*Author: Zihan Zhu*/
/*Allows Admin to manipulate the user's file accessibility.*/
#include "file_manip.h"  
#include "ui_file_manip.h"  
#include "Employee.h"
#include<QHBoxLayout>  
#include "LoginW.h"
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <algorithm>

file_manip::file_manip(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("File List"));
	setStyleSheet("background-color:rgb(230,230,250)");

	std::vector<QString> files = Admin::getPtr()->getCurrentWorker()->getWords();//用户默认可访问
	std::vector<QString> extra = Admin::getPtr()->getCurrentWorker()->get_ea();
	std::vector<QString> no = Admin::getPtr()->getCurrentWorker()->get_ed();

	std::vector<QString> result(Admin::getPtr()->getCurrentWorker()->get_ea().size()+
		Admin::getPtr()->getCurrentWorker()->getWords().size());
	auto itU = std::set_union(extra.begin(), extra.end(), files.begin(), files.end(), result.begin());
	result.resize(itU - result.begin());
	std::vector<QString> fresult(result.size());
	auto itD = std::set_difference(result.begin(), result.end(), no.begin(), no.end(), fresult.begin());
	fresult.resize(itD - fresult.begin());

	for (size_t i = 0; i < fresult.size(); i++)
	{
		ui.left_list->insertItem(i, fresult[i]);
	}
	QDir dir("words/");
	if (!dir.exists())
	{
		QMessageBox::warning(this, "Cannot get path", "'words/' is not a valid directory");
		close();
	}
	QStringList filter;
	filter << QString("*.txt");
	dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
	dir.setNameFilters(filter);  //设置文件名称过滤器，只为filter格式
	//用户不可访问的文件列表
	std::vector<QString> dirset;
	for (size_t i = 0; i < dir.count(); i++)
	{
		dirset.push_back("words/" + dir[i]);
	}
	std::vector<QString> Rset(dir.count());
	auto iter = std::set_difference(dirset.begin(), dirset.end(), fresult.begin(), fresult.end(),
		 Rset.begin());
	Rset.resize(iter - Rset.begin());
	iter = Rset.begin();
	for (size_t i = 0; i < Rset.size(); i++)
	{
		if (iter != Rset.end())
		{
			ui.right_list->insertItem(i, *iter);
			iter++;
		}
	}
	setAttribute(Qt::WA_DeleteOnClose);//确保析构函数执行
}

file_manip::~file_manip()
{
	if (to_write)//对所有同岗位员工生效。只修改employee_words。
	{
		Admin::getPtr()->getCurrentWorker()->clearWords();
		for (size_t i = 0; i < ui.left_list->count(); i++)
		{
			Admin::getPtr()->getCurrentWorker()->addWords(ui.left_list->item(i)->text());
		}//这段是全体和个人的区别。set的一系列操作会保证文件不重复
	}
	//直接退出，则只对那个用户生效，只修改extra和no
	std::vector<QString> FinalSet;
	for (size_t i = 0; i < ui.left_list->count(); i++)
	{
		FinalSet.push_back(ui.left_list->item(i)->text());
	}
	std::vector<QString> Words = Admin::getPtr()->getCurrentWorker()->getWords();//规避vector iterators incompatible问题
	std::sort(FinalSet.begin(), FinalSet.end());
	std::sort(Words.begin(), Words.end());

	std::vector<QString> NoSet(Words.size());
	std::vector<QString>::iterator it = std::set_difference(Words.begin(), Words.end(),
		FinalSet.begin(), FinalSet.end(), NoSet.begin());
	NoSet.resize(it - NoSet.begin());
	it = NoSet.begin();
	Admin::getPtr()->getCurrentWorker()->clear_ed();//clear以便重写
	while (it != NoSet.end())
	{
		Admin::getPtr()->getCurrentWorker()->add_ed(*it);
		it++;
	}

	std::vector<QString> ExtraSet(FinalSet.size());
	std::vector<QString>::iterator ite = std::set_difference(FinalSet.begin(), FinalSet.end(),
		Words.begin(), Words.end(), ExtraSet.begin());
	ExtraSet.resize(ite - ExtraSet.begin());
	ite = ExtraSet.begin();
	Admin::getPtr()->getCurrentWorker()->clear_ea();
	while (ite != ExtraSet.end())
	{
		Admin::getPtr()->getCurrentWorker()->add_ea(*ite);
		ite++;
	}
}

void file_manip::write_and_close()
{
	to_write = true;
	close();
}

void file_manip::move_file_right()
{
	int r = ui.left_list->currentRow();
	ui.right_list->insertItem(ui.right_list->count(), ui.left_list->currentItem()->text());
	ui.left_list->takeItem(r);
}

void file_manip::move_file_left()
{
	int r = ui.right_list->currentRow();
	ui.left_list->insertItem(ui.left_list->count(), ui.right_list->currentItem()->text());
	ui.right_list->takeItem(r);
}