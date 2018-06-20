#pragma once

#include "userdatdll_global_.h"
//��Ҫ�ڱ��^�ļ������������^�ļ���
#include <QApplication>
#include <QFileDialog>  
#include <QMessageBox>
#include <QLineEdit>
#include <QObject>
#include <string>
#include "sqlite3.h"
#include "stdlib.h"
#include <cstdio>
#include <QFile>

class USERDATDLL_EXPORT DBConnect
{//���ڳ�����
public:
	~DBConnect();
	static DBConnect* getSelf()//��ȡ����Աָ�룬��Ϊ��static���Բ�����Դ�ļ�����
	{
		static DBConnect m("Employee_list.db");
		return &m;
	}
	void exec_command(char* command, int(*callback)(void *, int, char **, char **));
private:
	DBConnect(char * filename);
	static DBConnect Self;
	sqlite3 * db;
	char* ee;
};

class USERDATDLL_EXPORT DataReader {
public:
	virtual ~DataReader() {};
	//DataReader() {};
	virtual bool FirstRead() = 0;
	virtual bool update() = 0;
	virtual void add() = 0;//AdminW's functions
	virtual void del(int curr_row) = 0;
	virtual void change(int curr_col, QString type, QString name, QString Password) = 0;
	virtual void Admin_add() = 0;//Admin's constructor
	virtual void rewrite() = 0;//file_manip's destructor
};

class USERDATDLL_EXPORT txtReader : public DataReader
{
public:
	txtReader() {};
	~txtReader() {};
	bool FirstRead();
	bool update();
	void add();
	void del(int curr_row);
	void change(int curr_col, QString type, QString name, QString Password);
	void Admin_add();
	void rewrite();
};

class USERDATDLL_EXPORT dbReader : public DataReader
{
public:
	dbReader() {};
	~dbReader() {};
	bool FirstRead();
	bool update();
	void add();
	void del(int curr_row);
	void change(int curr_col, QString type, QString name, QString Password);
	void Admin_add();
	void rewrite();
};