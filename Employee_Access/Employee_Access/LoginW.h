/*Author: Zihan Zhu*/
#pragma once
#include "ui_dialog.h"
#include "ui_LoginW.h"
#include <QtWidgets/QMainWindow>

class LoginW : public QMainWindow
{
	Q_OBJECT
public:
	LoginW(QWidget *parent = Q_NULLPTR);
	~LoginW() {};
private slots:
	//响应登陆按钮
	void login();
	//响应登陆成功
	void onsuccessful();
	//响应管理员登陆成功
	void admin_onsuccessful();
private:
	Ui::LoginWClass ui;
signals:
	void admin_success();
	void success();
};
