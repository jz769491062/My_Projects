#pragma once
#include <vector>
#include <iostream>
#include "export___.h"

class APPDLL DataReader;

class APPDLL Worker
{
public:
	Worker();
	Worker(std::string n, std::string pa, std::vector<std::string> ex,std::vector<std::string> no);
	~Worker();
	std::string getname();
	std::string getpasswrd();
	void setname(std::string &str);
	void setpasswrd(std::string &str);
	virtual std::vector<std::string> getWords();//返回不同版本的Words
	virtual void clearWords();
	virtual void addWords(std::string&wd);
	void add_ea(std::string&wd);
	std::vector<std::string>& get_ea();
	void clear_ea();
	void add_ed(std::string&wd);
	std::vector<std::string>& get_ed();
	void clear_ed();
	virtual std::string getType();
protected://使变量能被子类调用
	std::string name;
	std::string passwrd;
	std::vector<std::string> ea;//额外可访问
	std::vector<std::string> ed;//额外不可访问
};

class APPDLL Chief :public Worker
{
public:
	Chief();
	Chief(std::string n, std::string pa, std::vector<std::string> ex,
		std::vector<std::string> no);
	~Chief();
	virtual std::vector<std::string> getWords();
	virtual void clearWords();
	virtual void addWords(std::string&wd);
	virtual std::string getType();
};

class APPDLL Manager :public Chief
{
public:
	Manager();
	Manager(std::string n, std::string pa, std::vector<std::string> ex,
		std::vector<std::string> no);
	~Manager();
	virtual std::vector<std::string> getWords();
	virtual void clearWords();
	virtual void addWords(std::string&wd);
	virtual std::string getType();
};

class APPDLL Admin
{
public:
	static Admin* getPtr();//获取管理员指针，因为是static所以不能在源文件定义
	~Admin();
	void Createworkerbyname(std::string & usertype, std::string& username, std::string&password,
		std::vector<std::string> ea, std::vector<std::string> ed); //根据员工名字创建相应对象
	bool login_correct(std::string &username, std::string &password); //登入信息是否正确
	Worker* getCurrentWorker(); //获取当前指针
	std::string getname() const;
	std::string getpass() const;
	void setname(std::string& str);
	void setpass(std::string& str);
	void clearWorkerWords();
	void clearChiefWords();
	void clearManagerWords();
	void addWorkerWords(std::string& wd);
	void addChiefWords(std::string& wd);
	void addManagerWords(std::string& wd);
	void setTxtReader();
	void setDbReader();
	DataReader* & getReader();
	const std::vector<std::string> & getWorkerWords();
	const std::vector<std::string> & getChiefWords();
	const std::vector<std::string> & getManagerWords();
	std::vector<Worker*> employees;
private:
	Admin();//是private，使Admin对象无法直接被创建
	static Admin* _self;//静态变量，定义位于源文件里
	Worker* current_worker;//默认为worker，最大父类
	std::string name;
	std::string passw;
	std::vector<std::string> workerW;
	std::vector<std::string> chiefW;
	std::vector<std::string> managerW;
	DataReader* _reader;
};

/*#pragma once
#include <vector>
#include <iostream>

#ifndef APPDLL1_EXPORTS
#define APPDLL __declspec( dllimport ) 
#else
#define APPDLL __declspec( dllexport ) 
#endif // !APPDLL1_EXPORTS


//#define DllExport   __declspec( dllexport )  

class  APPDLL employee
{
public:
	employee() {};
	~employee() {};
	virtual void say() = 0;
};

class  APPDLL   worker : public employee
{
public:

	void say()
	{
		std::cout << "worker" << std::endl;
	}
};

class  APPDLL   chief: public employee
{
public:

	void say()
	{
		std::cout << "chief" << std::endl;
	}
};


class  APPDLL  Admin
{
public:
	Admin();
	static Admin* getPtr()
	{
		return self;
	}

	std::vector<employee*> ij;
	worker* curr;
	chief * blah;

	void read();
private :
	static Admin * self;
	
	};*/