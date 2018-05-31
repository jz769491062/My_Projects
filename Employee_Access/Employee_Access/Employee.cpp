/*Author: Zihan Zhu*/
/*Functions related to verifying and creating user profile.*/
#include "Employee.h"
#include <QFile>
#include <QObject>
#include <qdebug.h>
#include <QTextStream>
#include <QMessageBox>

Admin* Admin::_self = NULL;//因为是静态变量所以这里定义

Admin::Admin()
{//Don't put admin in Employee_words!!!
	QFile file("Employee_words.txt");
	if (!file.open(QFile::ReadWrite | QFile::Text))
	{//读取失败的话，给警告
		qDebug() << "Cannot read employee words" << endl;
	}
	QTextStream in(&file);
	QString type, temp; int file_count;
	while (!in.atEnd())
	{
		in >> type;
		if (type == "Worker")
		{
			in >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				in >> temp;
				workerW.push_back(temp);
			}
		}
		else if (type == "Chief")
		{
			chiefW.insert(chiefW.begin(), workerW.begin(), workerW.end());
			in >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				in >> temp;
				chiefW.push_back(temp);
			}
		}
		else if (type == "Manager")
		{
			managerW.insert(managerW.begin(), chiefW.begin(), chiefW.end());
			in >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				in >> temp;
				managerW.push_back(temp);
			}
		}
	}
}

//根据员工名字创建相应对象
void Admin::Createworkerbyname(QString &usertype, QString& username, QString&password,
	std::vector<QString> ea, std::vector<QString> ed)
{
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

void Worker::clearWords()
{
	Admin::getPtr()->clearWorkerWords();
}

void Worker::addWords(QString&wd)
{
	Admin::getPtr()->addWorkerWords(wd);
}

std::vector<QString> Chief::getWords()
{
	return Admin::getPtr()->getChiefWords();
}

void Chief::clearWords()
{
	Admin::getPtr()->clearChiefWords();
}

void Chief::addWords(QString&wd)
{
	Admin::getPtr()->addChiefWords(wd);
}

std::vector<QString> Manager::getWords()
{
	return Admin::getPtr()->getManagerWords();
}

void Manager::clearWords()
{
	Admin::getPtr()->clearManagerWords();
}

void Manager::addWords(QString&wd)
{
	Admin::getPtr()->addManagerWords(wd);
}