/*Author: Zihan Zhu*/
/*Functions related to verifying and creating user profile.*/
#include "stdafx.h"
#include "sqlite3.h"
#include "UserDatDLL_.h"
#include "Employee_.h"
#include <QFile>
#include <QObject>
#include <qdebug.h>
#include <QTextStream>
#include <QMessageBox>

Admin* Admin::_self = new Admin;//因为是静态变量所以这里定义

Admin::Admin()
{//Don't put admin in Employee_words!!!
	_reader = NULL;
	current_worker = NULL;
	QFile fi("TXT_OR_DB.txt");
	if (!fi.open(QFile::ReadOnly | QFile::Text))
	{//读取失败的话，给警告
		qDebug() << "Cannot read employee words" << endl;
		exit(1);
	}
	QTextStream rin(&fi);
	QString configWrd;
	rin >> configWrd;
	if (configWrd == "TXT")
	{
		setTxtReader();
	}
	else if (configWrd == "DB")
	{
		setDbReader();
	}
	else
	{
		qDebug() << "Malformed config file?" << endl;
		exit(1);
	}
}

Admin::~Admin() 
{
	delete _reader;
	_reader = NULL;
};

//根据员工名字创建相应对象
void Admin::Createworkerbyname(QString &usertype, QString& username, QString&password,
	std::vector<QString> ea, std::vector<QString> ed)
{
	ea.erase(remove(ea.begin(), ea.end(), ""), ea.end());
	ed.erase(remove(ed.begin(), ed.end(), ""), ed.end());
	for (size_t i = 0; i < employees.size(); i++)
	{
		if (employees[i]->getType()==usertype&&
			employees[i]->getname() == username&&
			employees[i]->getpasswrd() == password)
		{
			if (ea.size()!=0)
			{
				if (ea[0].size()>0)
				{
					employees[i]->add_ea(ea[0]);
				}
			}
			if (ed.size()!=0)
			{
				if (ed[0].size()>0)
				{
					employees[i]->add_ed(ed[0]);
				}
			}
			return;
		}
	}
	if (usertype == "Worker")
	{
		Worker* wo = new Worker(username, password,ea,ed);
		employees.push_back(wo);
	}
	else if (usertype == "Chief")
	{
		Chief* ch = new Chief(username, password,ea,ed);
		employees.push_back(ch);
	}
	else if (usertype == "Manager")
	{
		Manager* ma = new Manager(username, password,ea,ed);
		employees.push_back(ma);
	}
}

bool Admin::login_correct(QString &username, QString &password)
{
	for (size_t i = 0; i < employees.size(); i++)
	{
		if (employees[i]->getname()==username && employees[i]->getpasswrd() ==password)
		{
			current_worker = employees[i];
			return true;
		}
	}
	return false;
}

std::vector<QString> Worker::getWords()//返回不同版本的Words
{
	return Admin::getPtr()->getWorkerWords();
}

void Worker::clearWords(){
	Admin::getPtr()->clearWorkerWords();
}

void Worker::addWords(QString&wd){
	Admin::getPtr()->addWorkerWords(wd);
}

std::vector<QString> Chief::getWords(){
	return Admin::getPtr()->getChiefWords();
}

void Chief::clearWords(){
	Admin::getPtr()->clearChiefWords();
}

void Chief::addWords(QString&wd){
	Admin::getPtr()->addChiefWords(wd);
}

std::vector<QString> Manager::getWords(){
	return Admin::getPtr()->getManagerWords();
}

void Manager::clearWords(){
	Admin::getPtr()->clearManagerWords();
}

void Manager::addWords(QString&wd){
	Admin::getPtr()->addManagerWords(wd);
}