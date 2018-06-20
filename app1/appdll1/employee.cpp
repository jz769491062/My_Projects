//#include "stdafx.h"
//#include "employee.h"
//
//Admin* Admin::self = new Admin();
//
//Admin::Admin()
//{
//	curr = new worker;
//	blah = new chief;
//}
//
//void Admin::read()
//{
//	ij.push_back(curr);
//	ij.push_back(blah);
//}

/*Author: Zihan Zhu*/
/*Functions related to verifying and creating user profile.*/
#include <iostream>
#include "stdafx.h"
#include "sqlite3.h"
#include "UserData.h"
#include "employee.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Admin* Admin::_self = new Admin;//因为是静态变量所以这里定义

Admin::Admin()
{//Don't put admin in Employee_words!!!
	_reader = NULL;
	current_worker = NULL;
	std::ifstream fi("TXT_OR_DB.txt");
	if (!fi.is_open())
	{//读取失败的话，给警告
		std::cout << "Cannot read employee words" << std::endl;
		return;
	}
	//QTextStream rin(&fi);
	std::string configWrd;
	fi >> configWrd;
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
		std::cout << "Malformed config file?" << std::endl;
	}
}

Admin* Admin::getPtr()//获取管理员指针，因为是static所以不能在源文件定义
{
	if (_self == NULL)
	{
		_self = new Admin;
	}
	return _self;
}

Admin::~Admin()
{
	delete _reader;
	_reader = NULL;
};

Worker* Admin::getCurrentWorker() //获取当前指针
{
	//Worker是父类，所以Worker*也可以指向科长和经理
	return current_worker;
}
std::string Admin::getname() const
{
	return name;
}
std::string Admin::getpass() const
{
	return passw;
}
void Admin::setname(std::string& str)
{
	name = str;
}
void Admin::setpass(std::string& str)
{
	passw = str;
}
void Admin::clearWorkerWords()
{
	workerW.clear();
}
void Admin::clearChiefWords()
{
	chiefW.clear();
}
void Admin::clearManagerWords()
{
	managerW.clear();
}
void Admin::addWorkerWords(std::string& wd)
{
	workerW.push_back(wd);
}
void Admin::addChiefWords(std::string& wd)
{
	chiefW.push_back(wd);
}
void Admin::addManagerWords(std::string& wd)
{
	managerW.push_back(wd);
}
void Admin::setTxtReader()
{
	if (_reader == NULL) {
		_reader = new txtReader();
	}
}
void Admin::setDbReader()
{
	if (_reader == NULL) {
		_reader = new dbReader();
	}
}
DataReader* & Admin::getReader()
{
	return _reader;
}
const std::vector<std::string> & Admin::getWorkerWords() { return workerW; };
const std::vector<std::string> & Admin::getChiefWords() { return chiefW; };
const std::vector<std::string> & Admin::getManagerWords() { return managerW; };

//根据员工名字创建相应对象
void Admin::Createworkerbyname(std::string &usertype, std::string& username, std::string&password,
	std::vector<std::string> ea, std::vector<std::string> ed)
{
	for (size_t i = 0; i < employees.size(); i++)
	{
		if (employees[i]->getType() == usertype&&
			employees[i]->getname() == username&&
			employees[i]->getpasswrd() == password)
		{
			if (ea.size() != 0)
			{
				if (ea[0].size()>0)
				{
					employees[i]->add_ea(ea[0]);
				}
			}
			if (ed.size() != 0)
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
		Worker* wo = new Worker(username, password, ea, ed);
		employees.push_back(wo);
	}
	else if (usertype == "Chief")
	{
		Chief* ch = new Chief(username, password, ea, ed);
		employees.push_back(ch);
	}
	else if (usertype == "Manager")
	{
		Manager* ma = new Manager(username, password, ea, ed);
		employees.push_back(ma);
	}
}

bool Admin::login_correct(std::string &username, std::string &password)
{
	for (size_t i = 0; i < employees.size(); i++)
	{
		if (employees[i]->getname() == username && employees[i]->getpasswrd() == password)
		{
			current_worker = employees[i];
			return true;
		}
	}
	return false;
}

Worker::Worker() {};
Worker::~Worker() {};

Worker::Worker(std::string n, std::string pa, std::vector<std::string> ex,
	std::vector<std::string> no) :name(n), passwrd(pa), ea(ex), ed(no) {};

std::string Worker::getname()
{
	return name;
}

std::string Worker::getpasswrd()
{
	return passwrd;
}
void Worker::setname(std::string &str)
{
	name = str;
}
void Worker::setpasswrd(std::string &str)
{
	passwrd = str;
}

void Worker::add_ea(std::string&wd)
{
	ea.push_back(wd);
}
std::vector<std::string>& Worker::get_ea()
{
	return ea;
}
void Worker::clear_ea()
{
	ea.clear();
}
void Worker::add_ed(std::string&wd)
{
	ed.push_back(wd);
}
std::vector<std::string>& Worker::get_ed()
{
	return ed;
}
void Worker::clear_ed()
{
	ed.clear();
}
std::string Worker::getType() {
	return (std::string)"Worker";
}

std::vector<std::string> Worker::getWords()//返回不同版本的Words
{
	return Admin::getPtr()->getWorkerWords();
}

void Worker::clearWords() {
	Admin::getPtr()->clearWorkerWords();
}

void Worker::addWords(std::string&wd) {
	Admin::getPtr()->addWorkerWords(wd);
}

std::vector<std::string> Chief::getWords() {
	return Admin::getPtr()->getChiefWords();
}

Chief::Chief() {};
Chief::Chief(std::string n, std::string pa, std::vector<std::string> ex,
	std::vector<std::string> no) :Worker(n, pa, ex, no) {};
Chief::~Chief() {};

std::string Chief::getType() {
	return (std::string)"Chief";
}

void Chief::clearWords() {
	Admin::getPtr()->clearChiefWords();
}

void Chief::addWords(std::string&wd) {
	Admin::getPtr()->addChiefWords(wd);
}

Manager::Manager() {};
Manager::Manager(std::string n, std::string pa, std::vector<std::string> ex,
	std::vector<std::string> no) :Chief(n, pa, ex, no) {};
Manager::~Manager() {};

std::vector<std::string> Manager::getWords() {
	return Admin::getPtr()->getManagerWords();
}

void Manager::clearWords() {
	Admin::getPtr()->clearManagerWords();
}

void Manager::addWords(std::string&wd) {
	Admin::getPtr()->addManagerWords(wd);
}

std::string Manager::getType() {
	return (std::string)"Manager";
}