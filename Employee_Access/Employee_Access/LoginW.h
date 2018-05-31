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
	//��Ӧ��½��ť
	void login();
	//��Ӧ��½�ɹ�
	void onsuccessful();
	//��Ӧ����Ա��½�ɹ�
	void admin_onsuccessful();
private:
	Ui::LoginWClass ui;
signals:
	void admin_success();
	void success();
};
