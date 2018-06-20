/*Author: Zihan Zhu*/
#pragma once
#include <QtWidgets/QDialog>
//#include "UserDatDLL_.h"
#include "UserData.h"
#include <QListView>
#include <QListWidget>
#include <QLabel>
#include <QtGui>
#include <QStackedWidget>
#include <QFile>

class file_list : public QDialog
{
	Q_OBJECT
public:
	file_list(QWidget *parent = Q_NULLPTR);
	~file_list() {};
private:
	QLabel *label;
	QListWidget *left_list;//左侧的列表
	QStackedWidget *right_stack;//右侧的文件内容
	QPushButton *returnButton;
private slots:
	void return_to_login();
};
