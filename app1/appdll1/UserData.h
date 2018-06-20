#pragma once

#include "export___.h"
//��Ҫ�ڱ��^�ļ������������^�ļ������磺�������cpp������ͬһ��h����ô��������h���ܻ��ܡ�
//�Ѻ���ʵ����Դ�ļ��������ͷ�ļ�ʵ�֡�
#include <string>

#include "stdlib.h"
#include <cstdio>

class APPDLL DBConnect
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
 	class sqlite3 * db;
	char* ee;
};

class APPDLL DataReader {
public:
	virtual ~DataReader() {};
	//DataReader() {};
	virtual bool FirstRead() = 0;
	virtual bool update() = 0;
	virtual void add() = 0;//AdminW's functions
	virtual void del(int curr_row) = 0;
	virtual void change(int curr_col, std::string type, std::string name, std::string Password) = 0;
	virtual void Admin_add() = 0;//Admin's constructor
	virtual void rewrite() = 0;//file_manip's destructor
};

class APPDLL txtReader : public DataReader
{
public:
	txtReader() {};
	~txtReader() {};
	bool FirstRead();
	bool update();
	void add();
	void del(int curr_row);
	void change(int curr_col, std::string type, std::string name, std::string Password);
	void Admin_add();
	void rewrite();
};

class APPDLL dbReader : public DataReader
{
public:
	dbReader() {};
	~dbReader() {};
	bool FirstRead();
	bool update();
	void add();
	void del(int curr_row);
	void change(int curr_col, std::string type, std::string name, std::string Password);
	void Admin_add();
	void rewrite();
};