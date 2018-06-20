#include "stdafx.h"
#include "UserData.h"
#include "employee.h"
#include "sqlite3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

/* ******************* DBConnect stuff starts here *************** */
DBConnect DBConnect::Self("Employee_list.db");

std::vector<std::string> te;
//�����ӣ����ݿ�ѹ���󣬳���ִ�п죬�ʺϲ���Ƶ��ʱʹ�ã����ݿ�
//�����ӣ����ݿ�ѹ��С������ִ�������ʺ���������ʱʹ��,web��վ
DBConnect::DBConnect(char * filename)
{
	if (sqlite3_open(filename, &db) == SQLITE_OK)
	{
		std::cout << "Data opened" << std::endl;
	}
	else
	{
		std::cout << "Cannot open data" << std::endl;
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
	std::string command = "delete from extra where uname = '" + Admin::getPtr()->getCurrentWorker()->getname() + "';";
	DBConnect::getSelf()->exec_command((char*)(command.c_str()), 0);
	command = "delete from denied where uname = '" + Admin::getPtr()->getCurrentWorker()->getname() + "';";
	DBConnect::getSelf()->exec_command((char*)(command.c_str()), 0);
	if (Admin::getPtr()->getCurrentWorker()->get_ea().size() != 0)
	{
		for (size_t j = 0; j < Admin::getPtr()->getCurrentWorker()->get_ea().size(); j++)
		{
			command = "INSERT INTO extra (uname,addwords) VALUES ('" +
				Admin::getPtr()->getCurrentWorker()->getname() + "','" +
				Admin::getPtr()->getCurrentWorker()->get_ea()[j] + "');";
			DBConnect::getSelf()->exec_command((char*)(command.c_str()), 0);
		}
	}
	if (Admin::getPtr()->getCurrentWorker()->get_ed().size() != 0)
	{
		for (size_t j = 0; j < Admin::getPtr()->getCurrentWorker()->get_ed().size(); j++)
		{
			command = "INSERT INTO denied (uname,delwords) VALUES ('" +
				Admin::getPtr()->getCurrentWorker()->getname() + "','" +
				Admin::getPtr()->getCurrentWorker()->get_ed()[j] + "');";
			DBConnect::getSelf()->exec_command((char*)(command.c_str()), 0);
		}
	}
}

void txtReader::rewrite()
{
	//����ʵ�֣���Ϊtxt�汾���ļ���д��update()����
}

/* ******************* Admin_add start here *************** */
int pushtovec(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		te.push_back((std::string)columnvalue[i]);
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
	std::ifstream file("Employee_words.txt");
	if (!file.is_open())
	{//��ȡʧ�ܵĻ���������
		printf("Cannot read employee words \n");
	}
	//std::ifstream in(file);
	std::string type, temp; int file_count;
	while (!file.eof())
	{
		file >> type;
		if (type == "Worker")
		{
			file >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				file >> temp;
				Admin::getPtr()->addWorkerWords(temp);
			}
		}
		else if (type == "Chief")
		{
			for (size_t i = 0; i < Admin::getPtr()->getWorkerWords().size(); i++)
			{
				Admin::getPtr()->addChiefWords((std::string)Admin::getPtr()->getWorkerWords()[i]);
			}
			file >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				file >> temp;
				Admin::getPtr()->addChiefWords(temp);
			}
		}
		else if (type == "Manager")
		{
			for (size_t i = 0; i < Admin::getPtr()->getChiefWords().size(); i++)
			{
				Admin::getPtr()->addManagerWords((std::string)Admin::getPtr()->getChiefWords()[i]);
			}
			file >> file_count;
			for (size_t i = 0; i < file_count; i++)
			{
				file >> temp;
				Admin::getPtr()->addManagerWords(temp);
			}
		}
	}
	file.close();
}

/* ******************* add,del,and change()d start here *************** */
void dbReader::add()
{//��Ϊ�ո�createworkerbyname������employees��ĩλ�����´�����Ա��
		std::string comman = "INSERT INTO list (type,name,password) VALUES ('" +
			Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getType() + "','"
			+ Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getname() + "','"
			+ Admin::getPtr()->employees[Admin::getPtr()->employees.size() - 1]->getpasswrd() + "');";
	DBConnect::getSelf()->exec_command((char*)(comman.c_str()), 0);
}

void dbReader::del(int curr_row)
{
	std::string commanD = "delete from list where name = '" + 
		Admin::getPtr()->employees[curr_row - 1]->getname()
		+ "' and type = '" + Admin::getPtr()->employees[curr_row - 1]->getType() + "';";
	DBConnect::getSelf()->exec_command((char*)(commanD.c_str()), 0);
	commanD = "delete from extra where uname = '" +
		Admin::getPtr()->employees[curr_row - 1]->getname() + "';";
	DBConnect::getSelf()->exec_command((char*)(commanD.c_str()), 0);
	commanD = "delete from denied where uname = '" +
		Admin::getPtr()->employees[curr_row - 1]->getname() + "';";
	DBConnect::getSelf()->exec_command((char*)(commanD.c_str()), 0);
}

void dbReader::change(int curr_col, std::string type, std::string name, std::string Password)
{
	std::string Command;
	if (curr_col == 2)
	{
		Command = "UPDATE list SET password= '" + Password + "' where name = '"
			+ name + "';";
		DBConnect::getSelf()->exec_command((char*)(Command.c_str()), 0);
	}
	else if (curr_col == 1)
	{
		Command = "INSERT INTO list (type,name,password) VALUES ('" +
			type + "','"+ name + "','"+ Password + "');";
		DBConnect::getSelf()->exec_command((char*)(Command.c_str()), 0);
	}
	else if (curr_col == 0)
	{
		Command = "UPDATE list SET name= '" + name + "' where password = '"
			+ Password + "';";
		DBConnect::getSelf()->exec_command((char*)(Command.c_str()), 0);
	}
}

void txtReader::add() {}

void txtReader::del(int curr_row) {}

void txtReader::change(int curr_col, std::string type, std::string name, std::string Password) {}

/* ******************* sqlite3 firstRead and update start here *************** */
std::vector<std::string> inf;
std::vector<std::string> ex;
std::vector<std::string> no;

int addinfo(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		if ((std::string)columnvalue[i] != "")
		{
			ex.push_back((std::string)columnvalue[i]);
		}
	}
	return 0;
}

int noinfo(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		if ((std::string)columnvalue[i] != "")
		{
			no.push_back((std::string)columnvalue[i]);
		}
	}
	return 0;
}

int pushinfo(void *para, int ncolumn, char ** columnvalue, char *columnname[])
{
	for (int i = 0; i < ncolumn; i++)
	{
		if ((std::string)columnvalue[i] == "Admin")
		{
			Admin::getPtr()->setname((std::string)columnvalue[i + 1]);
			Admin::getPtr()->setpass((std::string)columnvalue[i + 2]);
			return 0;
		}
		inf.push_back((std::string)columnvalue[i]);
	}

	std::string COMmand = "select addwords from extra where uname = '" + inf[1] + "';";
	DBConnect::getSelf()->exec_command((char*)(COMmand.c_str()), addinfo);
	COMmand = "select delwords from denied where uname = '" + inf[1] + "';";
	DBConnect::getSelf()->exec_command((char*)(COMmand.c_str()), addinfo);
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
	std::vector<std::string> workerWW = Admin::getPtr()->getWorkerWords();
	std::vector<std::string> chiefWW = Admin::getPtr()->getChiefWords();
	std::vector<std::string> managerWW = Admin::getPtr()->getManagerWords();//�ܿ�vector iterators incompatible
	std::vector<std::string> tempWW(chiefWW.size());
	std::sort(workerWW.begin(), workerWW.end());
	std::sort(chiefWW.begin(), chiefWW.end());
	std::sort(managerWW.begin(), managerWW.end());

	//TODO:����employees�����û�ǰ������Ϣ
	std::string command;
	for (size_t i = 0; i < Admin::getPtr()->employees.size(); i++)
	{//����name����type?
		command = "UPDATE list SET type = '" + Admin::getPtr()->employees[i]->getType()
			+ "' WHERE type != 'Admin' AND name = '" + Admin::getPtr()->employees[i]->getname() + "');";
		DBConnect::getSelf()->exec_command((char*)(command.c_str()), addinfo);
	}
	DBConnect::getSelf()->exec_command("delete from member", 0);
	for (size_t i = 0; i < Admin::getPtr()->getWorkerWords().size(); i++)
	{
		command = "INSERT INTO member (type,files) VALUES ('Worker','"
			+ Admin::getPtr()->getWorkerWords()[i]+ "');";
		DBConnect::getSelf()->exec_command((char*)(command.c_str()), addinfo);
	}
	auto itera = std::set_difference(chiefWW.begin(),
		chiefWW.end(), workerWW.begin(), workerWW.end(), tempWW.begin());
	tempWW.resize(itera - tempWW.begin());
	itera = tempWW.begin();
	while (itera != tempWW.end())
	{//����Ƴ��ܷ��ʵ��ļ���
		command = "INSERT INTO member (type,files) VALUES ('Chief','"+ *itera + "');";
		DBConnect::getSelf()->exec_command((char*)(command.c_str()), addinfo);
		itera++;
	}
	tempWW.clear();
	tempWW.resize(managerWW.size());
	itera = std::set_difference(managerWW.begin(), managerWW.end(), chiefWW.begin(),
		chiefWW.end(), tempWW.begin());
	tempWW.resize(itera - tempWW.begin());
	itera = tempWW.begin();
	while (itera != tempWW.end())
	{//��������ܷ��ʵ��ļ���
		command = "INSERT INTO member (type,files) VALUES ('Manager','" + *itera + "');";
		DBConnect::getSelf()->exec_command((char*)(command.c_str()), addinfo);
		itera++;
	}
	tempWW.clear();
	return true;
}
/* ****************** txt firstread and update start here **************** */
bool txtReader::FirstRead()
{
	std::fstream in("Employee_list.txt");
	if (!in.is_open())
	{//��ȡʧ�ܵĻ���������
		return false;
	}
	std::string type, name, password, file_name, buffer;
	while (!in.eof())
	{
		std::vector<std::string> extra, no;
		in >> type;
		in >> name;
		in >> password;
		if (type == "Admin")
		{
			Admin::getPtr()->setname(name);
			Admin::getPtr()->setpass(password);
		}
		else if (type != "")
		{//�������Admin�����
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
	std::ofstream out("Employee_list.txt");
	if (out.is_open())
	{
		//QTextStream in(&out);
		out << "Admin " << Admin::getPtr()->getname() << " " << Admin::getPtr()->getpass() << std::endl;//Admin������
		for (size_t i = 0; i < Admin::getPtr()->employees.size(); i++)
		{
			out << Admin::getPtr()->employees[i]->getType() << " " <<
				Admin::getPtr()->employees[i]->getname() << " "
				<< Admin::getPtr()->employees[i]->getpasswrd() << " Extra: " <<
				Admin::getPtr()->employees[i]->get_ea().size() << " ";
			if (Admin::getPtr()->employees[i]->get_ea().size()>0)
			{
				for (size_t j = 0; j < Admin::getPtr()->employees[i]->get_ea().size(); j++)
				{
					out << Admin::getPtr()->employees[i]->get_ea()[j] << " ";
				}
			}
			out << "No: " << Admin::getPtr()->employees[i]->get_ed().size() << " ";
			if (Admin::getPtr()->employees[i]->get_ed().size()>0)
			{
				for (size_t j = 0; j < Admin::getPtr()->employees[i]->get_ed().size(); j++)
				{
					out << Admin::getPtr()->employees[i]->get_ed()[j] << " ";
				}
			}
			if (i != Admin::getPtr()->employees.size() - 1)
			{//���һ�������ٴ����¿���
				out << std::endl;
			}
		}
		out.close();
	}
	else
	{
		return false;
	}

	std::ofstream outfile("Employee_words.txt");
	if (outfile.is_open())
	{
		//QTextStream in(&File);
		std::vector<std::string> workerWW = Admin::getPtr()->getWorkerWords();
		std::vector<std::string> chiefWW = Admin::getPtr()->getChiefWords();
		std::vector<std::string> managerWW = Admin::getPtr()->getManagerWords();//�ܿ�vector iterators incompatible
		std::vector<std::string> tempWW(chiefWW.size());
		outfile << "Worker" << " " << workerWW.size();
		for (size_t j = 0; j < workerWW.size(); j++)
		{//��������ܷ��ʵ��ļ���
			outfile << " " << workerWW[j];
		}
		outfile << std::endl;

		outfile << "Chief" << " " << (chiefWW.size() - workerWW.size());
		std::vector<std::string>::iterator itera = std::set_difference(chiefWW.begin(),
			chiefWW.end(), workerWW.begin(), workerWW.end(), tempWW.begin());
		tempWW.resize(itera - tempWW.begin());
		itera = tempWW.begin();
		while (itera != tempWW.end())
		{//����Ƴ��ܷ��ʵ��ļ���
			outfile << " " << (*itera);
			itera++;
		}
		outfile << std::endl;

		outfile << "Manager" << " " << (managerWW.size() - chiefWW.size());
		tempWW.clear();
		tempWW.resize(managerWW.size());
		itera = std::set_difference(managerWW.begin(), managerWW.end(), chiefWW.begin(),
			chiefWW.end(), tempWW.begin());
		tempWW.resize(itera - tempWW.begin());
		itera = tempWW.begin();
		while (itera != tempWW.end())
		{//��������ܷ��ʵ��ļ���
			outfile << " " << (*itera);
			itera++;
		}
		outfile.close();
	}
	else {
		return false;
	}
	return true;
}
