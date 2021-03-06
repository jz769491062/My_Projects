#pragma once

#include "export___.h"
//不要在表頭文件包含其他表頭文件！例如：如果两个cpp包含了同一个h，那么被包含的h可能会打架。
//把函数实现在源文件里，避免在头文件实现。
#include <string>

#include "stdlib.h"
#include <cstdio>

class APPDLL DBConnect
{//用于长连接
public:
	~DBConnect();
	static DBConnect* getSelf()//获取管理员指针，因为是static所以不能在源文件定义
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