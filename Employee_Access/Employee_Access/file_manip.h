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
	std::vector<QString> fresult;//记录合成后的可访问列表，以便析构时进行比对
private slots:
	void move_file_right();//双击的左侧文件会被挪到右边
	void move_file_left();//双击的右侧文件会被挪到左边
	void write_and_close();//写入employee_words，实现全局变化
};
