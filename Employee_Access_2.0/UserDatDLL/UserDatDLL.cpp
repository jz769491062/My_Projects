#include "stdafx.h"
#include "UserDatDLL_.h"
#include "Employee_.h"
#include "sqlite3.h"
#include "qtextstream.h"
#include "qdebug.h"

/* ******************* DBConnect stuff starts here *************** */
DBConnect DBConnect::Self("Employee_list.db");

std::vector<QString> te;
//长连接：数据库压力大，程序执行快，适合操作频繁时使用，数据库
//短连接：数据库压力小，程序执行慢，适合连接数多时使用,web网站
DBConnect::DBConnect(char * filename)
{
	if (sqlite3_open(filename, &db) == SQLITE_OK)
	{
		qDebug() << "Data opened" << endl;
	}
	else
	{
		qDebug() << "Cannot open data" << endl;
		exit(1);
	}
	ee = "";
}

void DBConnect::exec_command(char* command, int(*callback)(void *, int, char **, char **))
{
	int rcc = sqlite3_exec(db, command, callback, 0, &ee);
}

DBConnect::~DBConnect()
{
	sqlite3_close(db);
}

/* ******************* rewrite() starts here *************** */
void dbReader::rewrite()
{
	QString command = QString("delete from extra where uname ='%1'").
		arg(Admin::getPtr()->getCurrentWorker()->getname());
	DBConnect::getSelf()->exec_command(command.toLatin1().data(), 0);
	command = QString("delete from denied where uname ='%1'").
		arg(Admin::getPtr()->getCurrentWorker()->getname());
	DBConnect::getSelf()->exec_command(command.toLatin1().data(), 0);

	if (Admin::getPtr()->getCurrentWorker()->get_ea().size() != 0)
	{
		for (size_t j = 0; j < Admin::getPtr()->getCurrentWorker()->get_ea().size(); j++)
		{
			command = QString("INSERT INTO extra (uname,addwords) VALUES ('%1','%2');").
				arg(Admin::getPtr()->getCurrentWorker()->getname()).
				arg(Admin::getPtr()->getCurrentWorker()->get_ea()[j]);
			DBConnect::getSelf()->exec_command(command.toLatin1().data(), 0);
		}
	}
	if (Admin::getPtr()->getCurrentWorker()->get_ed().size() != 0)
	{
		for (size_t j = 0; j < Admin::getPtr()->getCurrentWorker()->get_ed().size(); j++)
		{
			command = QString("INSERT INTO denied (uname,delwords) VALUES ('%1','%2');").
				arg(Admin::getPtr()->getCurrentWorker()->getname()).
				arg(Admin::getPtr()->getCurrentWorker()->get_ed()[j]);
			DBConnect::getSelf()->exec_command(command.toLatin1().data(), 0);
		}
	}
}

void txtReader::rewrite()
{
	//不需实现，因为txt版本的文件改写由update()进行
}

/* ******************* Admin_add start here *************** */
int pushtovec(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		te.push_back((QString)columnvalue[i]);
	}
	return 0;
}

void dbReader::Admin_add()
{
	DBConnect::getSelf()->exec_command("select files from member where type = 'Worker'", pushtovec);
	for (size_t i = 0; i < te.size(); i++)
	{
		Admin::getPtr()->addWorkerWords(te[i]);
	}
	DBConnect::getSelf()->exec_command("select files from member where type = 'Chief'", pushtovec);
	for (size_t i = 0; i < te.size(); i++)
	{
		Admin::getPtr()->addChiefWords(te[i]);
	}
	DBConnect::getSelf()->exec_command("select files from member where type = 'Manager'", pushtovec);
	for (size_t i = 0; i < te.size(); i++)
	{
		Admin::getPtr()->addManagerWords(te[i]);
	}
}

void txtReader::Admin_add()
{
	QFile file("Employee_words.txt");
	if (!file.open(QFile::ReadOnly | QFile::Text))
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
				Admin::getPtr()->addWorkerWords(temp);
			}
		}
		else if (type == "Chief")
		{
			for (size_t i = 0; i < Admin::getPtr()->getWorkerWords().size(); i++)
			{
				Admin::getPtr()->addChiefWords((QString)Admin::getPtr()->getWorkerWords()[i]);
			}
			in >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				in >> temp;
				Admin::getPtr()->addChiefWords(temp);
			}
		}
		else if (type == "Manager")
		{
			for (size_t i = 0; i < Admin::getPtr()->getChiefWords().size(); i++)
			{
				Admin::getPtr()->addManagerWords((QString)Admin::getPtr()->getChiefWords()[i]);
			}
			in >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				in >> temp;
				Admin::getPtr()->addManagerWords(temp);
			}
		}
	}
	file.close();
}

/* ******************* add,del,and change()d start here *************** */
void dbReader::add()
{//因为刚刚createworkerbyname，所以employees的末位就是新创建的员工
	QString comman = QString("INSERT INTO list (type,name,password) VALUES ('%1','%2','%3');").
		arg(Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getType()).
		arg(Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getname()).
		arg(Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getpasswrd());
	DBConnect::getSelf()->exec_command(comman.toLatin1().data(), 0);
}

void dbReader::del(int curr_row)
{
	QString commanD = QString("delete from list where name = '%1' and type = '%2';").
		arg(Admin::getPtr()->employees[curr_row - 1]->getname()).arg(Admin::getPtr()->employees[curr_row - 1]->getType());
	DBConnect::getSelf()->exec_command(commanD.toLatin1().data(), 0);
	commanD = QString("delete from extra where uname = '%1';").
		arg(Admin::getPtr()->employees[curr_row - 1]->getname());
	DBConnect::getSelf()->exec_command(commanD.toLatin1().data(), 0);
	commanD = QString("delete from denied where uname = '%1';").
		arg(Admin::getPtr()->employees[curr_row - 1]->getname());
	DBConnect::getSelf()->exec_command(commanD.toLatin1().data(), 0);
}

void dbReader::change(int curr_col, QString type, QString name, QString Password)
{
	QString Command;
	if (curr_col == 2)
	{
		Command = QString("UPDATE list SET password= '%1' WHERE name = '%2';").
			arg(Password).arg(name);
		DBConnect::getSelf()->exec_command(Command.toLatin1().data(), 0);
	}
	else if (curr_col == 1)
	{
		Command = QString("INSERT INTO list (type,name,password) VALUES ('%1','%2','%3');").
			arg(type).arg(name).arg(Password);
		DBConnect::getSelf()->exec_command(Command.toLatin1().data(), 0);
	}
	else if (curr_col == 0)
	{
		Command = QString("UPDATE list SET name= '%1' WHERE password = '%2';").arg(name).arg(Password);
		DBConnect::getSelf()->exec_command(Command.toLatin1().data(), 0);
	}
}

void txtReader::add() {}

void txtReader::del(int curr_row) {}

void txtReader::change(int curr_col, QString type, QString name, QString Password) {}

/* ******************* sqlite3 firstRead and update start here *************** */
std::vector<QString> inf;
std::vector<QString> ex;
std::vector<QString> no;

int addinfo(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		if ((QString)columnvalue[i] != "")
		{
			ex.push_back((QString)columnvalue[i]);
		}
	}
	return 0;
}

int noinfo(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		if ((QString)columnvalue[i] != "")
		{
			no.push_back((QString)columnvalue[i]);
		}
	}
	return 0;
}

int pushinfo(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		if ((QString)columnvalue[i] == "Admin")
		{
			Admin::getPtr()->setname((QString)columnvalue[i + 1]);
			Admin::getPtr()->setpass((QString)columnvalue[i + 2]);
			return 0;
		}
		inf.push_back((QString)columnvalue[i]);
	}
	QString COMmand = QString("select addwords from extra where uname = '%1'").arg(inf[1]);
	DBConnect::getSelf()->exec_command(COMmand.toLatin1().data(), addinfo);
	COMmand = QString("select delwords from denied where uname = '%1'").arg(inf[1]);
	DBConnect::getSelf()->exec_command(COMmand.toLatin1().data(), noinfo);
	Admin::getPtr()->Createworkerbyname(inf[0], inf[1], inf[2], ex, no);
	ex.clear();
	no.clear();
	inf.clear();
	return 0;
}

bool dbReader::FirstRead()
{
	DBConnect::getSelf()->exec_command("select * from list", pushinfo);
	return true;
}

bool dbReader::update()
{
	std::vector<QString> workerWW = Admin::getPtr()->getWorkerWords();
	std::vector<QString> chiefWW = Admin::getPtr()->getChiefWords();
	std::vector<QString> managerWW = Admin::getPtr()->getManagerWords();//避开vector iterators incompatible
	std::vector<QString> tempWW(chiefWW.size());
	std::sort(workerWW.begin(), workerWW.end());
	std::sort(chiefWW.begin(), chiefWW.end());
	std::sort(managerWW.begin(), managerWW.end());

	//TODO:根据employees更新用户前三项信息
	QString command;
	for (size_t i = 0; i < Admin::getPtr()->employees.size(); i++)
	{//根据name更新type?
		command = QString("UPDATE list SET type = '%1' WHERE type != 'Admin' AND name = '%2');").
			arg(Admin::getPtr()->employees[i]->getType()).arg(Admin::getPtr()->employees[i]->getname());
	}

	DBConnect::getSelf()->exec_command("delete from member", 0);
	for (size_t i = 0; i < Admin::getPtr()->getWorkerWords().size(); i++)
	{
		command = QString("INSERT INTO member (type,files) VALUES ('Worker','%1');").
			arg(Admin::getPtr()->getWorkerWords()[i]);
		DBConnect::getSelf()->exec_command(command.toLatin1().data(), 0);
	}
	auto itera = std::set_difference(chiefWW.begin(),
		chiefWW.end(), workerWW.begin(), workerWW.end(), tempWW.begin());
	tempWW.resize(itera - tempWW.begin());
	itera = tempWW.begin();
	while (itera != tempWW.end())
	{//输出科长能访问的文件名
		command = QString("INSERT INTO member (type,files) VALUES ('Chief','%1');").
			arg(*itera);
		DBConnect::getSelf()->exec_command(command.toLatin1().data(), 0);
		itera++;
	}
	tempWW.clear();
	tempWW.resize(managerWW.size());
	itera = std::set_difference(managerWW.begin(), managerWW.end(), chiefWW.begin(),
		chiefWW.end(), tempWW.begin());
	tempWW.resize(itera - tempWW.begin());
	itera = tempWW.begin();
	while (itera != tempWW.end())
	{//输出经理能访问的文件名
		command = QString("INSERT INTO member (type,files) VALUES ('Manager','%1');").
			arg(*itera);
		DBConnect::getSelf()->exec_command(command.toLatin1().data(), 0);
		itera++;
	}
	tempWW.clear();
	return true;
}
/* ****************** txt firstread and update start here **************** */
bool txtReader::FirstRead()
{
	QFile file("Employee_list.txt");
	if (!file.open(QFile::ReadWrite | QFile::Text))
	{//读取失败的话，给警告
		return false;
	}
	QTextStream in(&file);
	QString type, name, password, file_name, buffer;
	while (!in.atEnd())
	{
		std::vector<QString> extra, no;
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
			if (ex_count != 0)
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
			Admin::getPtr()->Createworkerbyname(type, name, password, extra, no);
		}
	}
	return true;
}

bool txtReader::update()
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
				<< Admin::getPtr()->employees[i]->getpasswrd() << " Extra: " <<
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
		return false;
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
			in << " " << workerWW[j];
		}
		in << endl;

		in << "Chief" << " " << (chiefWW.size() - workerWW.size());
		std::vector<QString>::iterator itera = std::set_difference(chiefWW.begin(),
			chiefWW.end(), workerWW.begin(), workerWW.end(), tempWW.begin());
		tempWW.resize(itera - tempWW.begin());
		itera = tempWW.begin();
		while (itera != tempWW.end())
		{//输出科长能访问的文件名
			in << " " << (*itera);
			itera++;
		}
		in << endl;

		in << "Manager" << " " << (managerWW.size() - chiefWW.size());
		tempWW.clear();
		tempWW.resize(managerWW.size());
		itera = std::set_difference(managerWW.begin(), managerWW.end(), chiefWW.begin(),
			chiefWW.end(), tempWW.begin());
		tempWW.resize(itera - tempWW.begin());
		itera = tempWW.begin();
		while (itera != tempWW.end())
		{//输出经理能访问的文件名
			in << " " << (*itera);
			itera++;
		}
		File.close();
	}
	else {
		return false;
	}
	return true;
}
