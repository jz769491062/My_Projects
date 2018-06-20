/*Author: Zihan Zhu*/
/*Defines Admin and other types of users.*/
#pragma once
#include "sqlite3.h"
#include <vector>
#include <QString>
#include <QtSql\QSql>
#include <QtSql\QSqlDatabase>
#include <QtSql\QSqlError>
#include <QtSql\QSqlQuery>
//#include "user_data_export.h"
#include "userdatdll_global_.h"

//���ڶ�����
//void exec_command(sqlite3 * mysq, char* command, int(*callback)(void *, int, char **, char **), char* filename);

//class DBConnect
//{//���ڳ�����
//public:
//	~DBConnect();
//	static DBConnect* getSelf()//��ȡ����Աָ�룬��Ϊ��static���Բ�����Դ�ļ�����
//	{
//		static DBConnect m("Employee_list.db");
//		return &m;
//		//if (Self == NULL)
//		//{
//		//	Self = new DBConnect("Employee_list.db");
//		//}
//		// return &Self;
//	}
//	void exec_command(char* command, int(*callback)(void *, int, char **, char **));
//	//void exec_select();
//private:
//	DBConnect(char * filename);
//	static DBConnect Self;
//	sqlite3 * db;
//	char* ee;
//};

class USERDATDLL_EXPORT DataReader;

class USERDATDLL_EXPORT Worker
{
public:
	Worker() {};
	Worker(QString n, QString pa, std::vector<QString> ex, 
		std::vector<QString> no) :name(n), passwrd(pa),ea(ex),ed(no){};
	~Worker() {};
	QString getname()
	{
		return name;
	}
	QString getpasswrd()
	{
		return passwrd;
	}
	void setname(QString &str)
	{
		name = str;
	}
	void setpasswrd(QString &str)
	{
		passwrd = str;
	}
	virtual std::vector<QString> getWords();//���ز�ͬ�汾��Words
	virtual void clearWords();
	virtual void addWords(QString&wd);
	void add_ea(QString&wd)
	{
		ea.push_back(wd);
	}
	std::vector<QString>& get_ea()
	{
		return ea;
	}
	void clear_ea()
	{
		ea.clear();
	}
	void add_ed(QString&wd)
	{
		ed.push_back(wd);
	}
	std::vector<QString>& get_ed()
	{
		return ed;
	}
	void clear_ed()
	{
		ed.clear();
	}
	virtual QString getType() {
		return (QString)"Worker";
	}
protected://ʹ�����ܱ��������
	QString name;
	QString passwrd;
	std::vector<QString> ea;//����ɷ���
	std::vector<QString> ed;//���ⲻ�ɷ���
};

class USERDATDLL_EXPORT Chief :public Worker
{
public:
	Chief() {};
	Chief(QString n, QString pa, std::vector<QString> ex,
		std::vector<QString> no) :Worker(n,pa,ex,no) {};
	~Chief() {};
	virtual std::vector<QString> getWords();
	virtual void clearWords();
	virtual void addWords(QString&wd);
	virtual QString getType() {
		return (QString)"Chief";
	}
};

class USERDATDLL_EXPORT Manager :public Chief
{
public:
	Manager() {};
	Manager(QString n, QString pa, std::vector<QString> ex,
		std::vector<QString> no) :Chief(n, pa, ex, no) {};
	~Manager() {};
	virtual std::vector<QString> getWords();
	virtual void clearWords();
	virtual void addWords(QString&wd);
	virtual QString getType() {
		return (QString)"Manager";
	}
};

class USERDATDLL_EXPORT Admin
{
public:
	static Admin* getPtr()//��ȡ����Աָ�룬��Ϊ��static���Բ�����Դ�ļ�����
	{
		//if (_self == NULL)
		//{
		//	_self = new Admin;
		//}
		return _self;
	}
	~Admin();
	void Createworkerbyname(QString & usertype, QString& username, QString&password,
		std::vector<QString> ea, std::vector<QString> ed); //����Ա�����ִ�����Ӧ����
	bool login_correct(QString &username, QString &password); //������Ϣ�Ƿ���ȷ
	Worker* getCurrentWorker() //��ȡ��ǰָ��
	{
		//Worker�Ǹ��࣬����Worker*Ҳ����ָ��Ƴ��;���
		return current_worker;
	}
	QString getname() const
	{
		return name;
	}
	QString getpass() const
	{
		return passw;
	}
	void setname(QString& str)
	{
		name = str;
	}
	void setpass(QString& str)
	{
		passw = str;
	}
	void clearWorkerWords()
	{
		workerW.clear();
	}
	void clearChiefWords()
	{
		chiefW.clear();
	}
	void clearManagerWords()
	{
		managerW.clear();
	}
	void addWorkerWords(QString& wd)
	{
		workerW.push_back(wd);
	}
	void addChiefWords(QString& wd)
	{
		chiefW.push_back(wd);
	}
	void addManagerWords(QString& wd)
	{
		managerW.push_back(wd);
	}
	void setTxtReader()
	{
		if (_reader == NULL) {
			_reader = new txtReader;
		}
	}
	void setDbReader()
	{
		if (_reader == NULL) {
			_reader = new dbReader;
		}
	}
	DataReader* & getReader()
	{
		return _reader;
	}
	const std::vector<QString> & getWorkerWords() { return workerW; };
	const std::vector<QString> & getChiefWords() { return chiefW; };
	const std::vector<QString> & getManagerWords() { return managerW; };
	std::vector<Worker*> employees;
private:
	Admin();//��private��ʹAdmin�����޷�ֱ�ӱ�����
	static Admin* _self;//��̬����������λ��Դ�ļ���
	Worker* current_worker;//Ĭ��Ϊworker�������
	QString name;
	QString passw;
	std::vector<QString> workerW;
	std::vector<QString> chiefW;
	std::vector<QString> managerW;
	DataReader* _reader;
};