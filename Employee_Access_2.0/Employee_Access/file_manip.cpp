/*Author: Zihan Zhu*/
/*Allows Admin to manipulate the user's file accessibility.*/
#include "file_manip.h"  
#include "ui_file_manip.h"
//#include "UserDatDLL_.h"
//#include "Employee_.h"
#include "UserData.h"
#include "employee.h"
#include<QHBoxLayout>  
#include "LoginW.h"
#include <string>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <algorithm>

file_manip::file_manip(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("File List"));
	setStyleSheet("background-color:rgb(230,230,250)");

	std::vector<std::string> files = Admin::getPtr()->getCurrentWorker()->getWords();//�û�Ĭ�Ͽɷ���
	std::vector<std::string> extra = Admin::getPtr()->getCurrentWorker()->get_ea();
	std::vector<std::string> no = Admin::getPtr()->getCurrentWorker()->get_ed();
	//files.erase(remove(files.begin(), files.end(), ""), files.end());
	//extra.erase(remove(extra.begin(), extra.end(), ""), extra.end());
	//no.erase(remove(no.begin(), no.end(), ""), no.end());
	std::sort(files.begin(), files.end());
	std::sort(extra.begin(), extra.end());
	std::sort(no.begin(), no.end());//sort
	std::vector<std::string> result(Admin::getPtr()->getCurrentWorker()->get_ea().size()+
		Admin::getPtr()->getCurrentWorker()->getWords().size());
	auto itU = std::set_union(extra.begin(), extra.end(), files.begin(), files.end(), result.begin());
	result.resize(itU - result.begin());
	std::vector<std::string> fresult(result.size());
	auto itD = std::set_difference(result.begin(), result.end(), no.begin(), no.end(), fresult.begin());
	fresult.resize(itD - fresult.begin());

	for (size_t i = 0; i < fresult.size(); i++)
	{
		ui.left_list->insertItem(i, QString::fromStdString(fresult[i]));
	}
	QDir dir("words/");
	if (!dir.exists())
	{
		QMessageBox::warning(this, "Cannot get path", "'words/' is not a valid directory");
		close();
	}
	QStringList filter;
	filter << QString("*.txt");
	dir.setFilter(QDir::Files | QDir::NoSymLinks); //�������͹�������ֻΪ�ļ���ʽ
	dir.setNameFilters(filter);  //�����ļ����ƹ�������ֻΪfilter��ʽ
	//�û����ɷ��ʵ��ļ��б�
	std::vector<std::string> dirset;
	for (size_t i = 0; i < dir.count(); i++)
	{
		dirset.push_back("words/" + dir[i].toStdString());
	}
	std::vector<std::string> Rset(dir.count());
	auto iter = std::set_difference(dirset.begin(), dirset.end(), fresult.begin(), fresult.end(),
		 Rset.begin());
	Rset.resize(iter - Rset.begin());
	iter = Rset.begin();
	for (size_t i = 0; i < Rset.size(); i++)
	{
		if (iter != Rset.end())
		{
			ui.right_list->insertItem(i, QString::fromStdString(*iter));
			iter++;
		}
	}
	setAttribute(Qt::WA_DeleteOnClose);//ȷ����������ִ��
}

file_manip::~file_manip()
{
	if (to_write)//������ͬ��λԱ����Ч��ֻ�޸�employee_words��
	{
		Admin::getPtr()->getCurrentWorker()->clearWords();
		for (size_t i = 0; i < ui.left_list->count(); i++)
		{
			Admin::getPtr()->getCurrentWorker()->addWords(ui.left_list->item(i)->text().toStdString());
		}//�����ȫ��͸��˵�����set��һϵ�в����ᱣ֤�ļ����ظ�
	}
	//ֱ���˳�����ֻ���Ǹ��û���Ч��ֻ�޸�extra��no
	std::vector<std::string> FinalSet;
	for (size_t i = 0; i < ui.left_list->count(); i++)
	{
		FinalSet.push_back(ui.left_list->item(i)->text().toStdString());
	}
	//���vector iterators incompatible���⣬ͬʱ���̴��볤��
	std::vector<std::string> Words = Admin::getPtr()->getCurrentWorker()->getWords();
	std::sort(FinalSet.begin(), FinalSet.end());
	std::sort(Words.begin(), Words.end());

	std::vector<std::string> NoSet(Words.size());
	std::vector<std::string>::iterator it = std::set_difference(Words.begin(), Words.end(),
		FinalSet.begin(), FinalSet.end(), NoSet.begin());
	NoSet.resize(it - NoSet.begin());
	it = NoSet.begin();
	Admin::getPtr()->getCurrentWorker()->clear_ed();//clear�Ա���д
	while (it != NoSet.end())
	{
		Admin::getPtr()->getCurrentWorker()->add_ed(*it);
		it++;
	}

	std::vector<std::string> ExtraSet(FinalSet.size());
	std::vector<std::string>::iterator ite = std::set_difference(FinalSet.begin(), FinalSet.end(),
		Words.begin(), Words.end(), ExtraSet.begin());
	ExtraSet.resize(ite - ExtraSet.begin());
	ite = ExtraSet.begin();
	Admin::getPtr()->getCurrentWorker()->clear_ea();
	while (ite != ExtraSet.end())
	{
		Admin::getPtr()->getCurrentWorker()->add_ea(*ite);
		ite++;
	}
	Admin::getPtr()->getReader()->rewrite();
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