//Author: Zihan Zhu
#pragma once
#include <QtWidgets/QDialog>
//#include "ui_Calculator.h"
#include <QLineEdit>
#include <QString>
#include <qkeyeventtransition.h>
#include <QKeyEvent>
#include <string>

class Calculator : public QDialog
{
	Q_OBJECT
public:
	Calculator(QWidget *parent = 0);
	~Calculator() {};

protected:
	QPushButton* button_0;
	QPushButton* button_1;
	QPushButton* button_2;
	QPushButton* button_3;
	QPushButton* button_4;
	QPushButton* button_5;
	QPushButton* button_6;
	QPushButton* button_7;
	QPushButton* button_8;
	QPushButton* button_9;
	QPushButton* button_plus;
	QPushButton* button_minus;
	QPushButton* button_multiply;
	QPushButton* button_divide;
	QPushButton* button_equal;
	QPushButton* button_ln;
	QPushButton* button_root;
	QPushButton* button_power;
	QPushButton* button_expn;
	QPushButton* button_lpar;
	QPushButton* button_rpar;
	QPushButton* button_point;//小数点
	QPushButton* button_clear;
	QPushButton* button_delete;//删除一个字符
	QLineEdit* lineEdit;//输入框
	void keyPressEvent(QKeyEvent *e);

private slots:
	void on_button_clicked();
};
