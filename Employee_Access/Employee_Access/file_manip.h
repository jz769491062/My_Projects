/*Author: Zihan Zhu*/
#pragma once

#include <QDialog>
#include "ui_file_manip.h"
#include <QtWidgets/QDialog>
#include <QListView>
#include <QListWidget> 
#include <QLabel>
#include <QtGui>
#include <QStackedWidget>
#include <QFile>

class file_manip : public QDialog
{
	Q_OBJECT
public:
	file_manip(QWidget *parent = Q_NULLPTR);
	~file_manip();
private:
	Ui::file_manip ui;
	bool to_write = false;
	std::vector<QString> fresult;//��¼�ϳɺ�Ŀɷ����б��Ա�����ʱ���бȶ�
private slots:
	void move_file_right();//˫��������ļ��ᱻŲ���ұ�
	void move_file_left();//˫�����Ҳ��ļ��ᱻŲ�����
	void write_and_close();//д��employee_words��ʵ��ȫ�ֱ仯
};
