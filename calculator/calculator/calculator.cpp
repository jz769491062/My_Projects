//Author: Zihan Zhu
#pragma once
#include "calculator.h"
#include "CalculatorImp.h"
//#include "ui_Calculator.h"
#include <QPushButton>
#include <QGridLayout>
#include <cmath>
using namespace std;

//For storing data in QPushButtons
struct myname : QObjectUserData {
	QString name;  //按钮存储的数据
};

myname* createname(QString s)
{
	myname* nn = new myname();
	nn->name = s;
	return nn;
}

Calculator::Calculator(QWidget *parent) :QDialog(parent)
{
	button_0 = new QPushButton("0");
	button_1 = new QPushButton("1");
	button_2 = new QPushButton("2");
	button_3 = new QPushButton("3");
	button_4 = new QPushButton("4");
	button_5 = new QPushButton("5");
	button_6 = new QPushButton("6");
	button_7 = new QPushButton("7");
	button_8 = new QPushButton("8");
	button_9 = new QPushButton("9");
	button_plus = new QPushButton("+");
	button_minus = new QPushButton("-");
	button_multiply = new QPushButton("*");
	button_divide = new QPushButton("/");
	button_equal = new QPushButton("=");
	button_ln = new QPushButton("LogBase");
	button_root = new QPushButton("Root");
	button_power = new QPushButton("Power");
	button_expn = new QPushButton("Expn");
	button_lpar = new QPushButton("(");
	button_rpar = new QPushButton(")");
	button_point = new QPushButton(".");
	button_clear = new QPushButton("Clear");
	button_delete = new QPushButton("Delete");
	button_0->setUserData(Qt::UserRole, createname("0"));
	button_1->setUserData(Qt::UserRole, createname("1"));
	button_2->setUserData(Qt::UserRole, createname("2"));
	button_3->setUserData(Qt::UserRole, createname("3"));
	button_4->setUserData(Qt::UserRole, createname("4"));
	button_5->setUserData(Qt::UserRole, createname("5"));
	button_6->setUserData(Qt::UserRole, createname("6"));
	button_7->setUserData(Qt::UserRole, createname("7"));
	button_8->setUserData(Qt::UserRole, createname("8"));
	button_9->setUserData(Qt::UserRole, createname("9"));
	button_plus->setUserData(Qt::UserRole, createname("+"));
	button_minus->setUserData(Qt::UserRole, createname("-"));
	button_multiply->setUserData(Qt::UserRole, createname("*"));
	button_divide->setUserData(Qt::UserRole, createname("/"));
	button_equal->setUserData(Qt::UserRole, createname("="));
	button_ln->setUserData(Qt::UserRole, createname("LogBase"));
	button_root->setUserData(Qt::UserRole, createname("Root"));
	button_power->setUserData(Qt::UserRole, createname("Power"));
	button_expn->setUserData(Qt::UserRole, createname("Expn"));
	button_lpar->setUserData(Qt::UserRole, createname("("));
	button_rpar->setUserData(Qt::UserRole, createname(")"));
	button_point->setUserData(Qt::UserRole, createname("."));
	button_clear->setUserData(Qt::UserRole, createname("Clear"));
	button_delete->setUserData(Qt::UserRole, createname("Delete"));

	lineEdit = new QLineEdit("");
	lineEdit->setPlaceholderText("Enter equation here");

	//网格布局
	QGridLayout *Grid = new QGridLayout;
	Grid->addWidget(lineEdit, 1, 1, 1, 6, Qt::Alignment());
	//6个参数含义：1：部件的指针；2、3：所在行和列
	//占用几行和几列；对齐方式


	Grid->addWidget(button_1, 2, 1, Qt::Alignment());
	Grid->addWidget(button_2, 2, 2, Qt::Alignment());
	Grid->addWidget(button_3, 2, 3, Qt::Alignment());
	Grid->addWidget(button_plus, 2, 4, Qt::Alignment());
	Grid->addWidget(button_ln, 2, 5, Qt::Alignment());
	Grid->addWidget(button_lpar, 2, 6, Qt::Alignment());

	Grid->addWidget(button_4, 3, 1, Qt::Alignment());
	Grid->addWidget(button_5, 3, 2, Qt::Alignment());
	Grid->addWidget(button_6, 3, 3, Qt::Alignment());
	Grid->addWidget(button_minus, 3, 4, Qt::Alignment());
	Grid->addWidget(button_root, 3, 5, Qt::Alignment());
	Grid->addWidget(button_rpar, 3, 6, Qt::Alignment());

	Grid->addWidget(button_7, 4, 1, Qt::Alignment());
	Grid->addWidget(button_8, 4, 2, Qt::Alignment());
	Grid->addWidget(button_9, 4, 3, Qt::Alignment());
	Grid->addWidget(button_multiply, 4, 4, Qt::Alignment());
	Grid->addWidget(button_power, 4, 5, Qt::Alignment());
	Grid->addWidget(button_delete, 4, 6, Qt::Alignment());

	Grid->addWidget(button_0, 5, 1, Qt::Alignment());
	Grid->addWidget(button_clear, 5, 6, Qt::Alignment());
	Grid->addWidget(button_equal, 5, 3, Qt::Alignment());
	Grid->addWidget(button_divide, 5, 4, Qt::Alignment());
	Grid->addWidget(button_expn, 5, 5, Qt::Alignment());
	Grid->addWidget(button_point, 5, 2, Qt::Alignment());
	button_equal->setStyleSheet("background-color: rgb(3, 168, 158);");
	button_delete->setStyleSheet("background-color: rgb(107, 142, 35);");
	button_clear->setStyleSheet("background-color: rgb(199, 97, 20);");
	button_point->setStyleSheet("background-color: rgb(255, 227, 132);");
	//对话框变成Grid布局
	this->setLayout(Grid);

	//连接
	connect(button_clear, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_delete, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_equal, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

	connect(button_0, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_1, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_2, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_3, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_4, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_5, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_6, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_7, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_8, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_9, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

	connect(button_plus, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_minus, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_multiply, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_divide, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_ln, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_root, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_power, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_expn, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_lpar, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_rpar, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(button_point, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

void Calculator::keyPressEvent(QKeyEvent *e)
{
	update();
	switch (e->key())
	{//lose focus才能用以下东西
	case Qt::Key_C:
		emit button_clear->click();
		break;
	case Qt::Key_Backspace:
		emit button_delete->click();
		break;
	case Qt::Key_Enter:
		emit button_equal->click();
		break;
	default:
		break;
	}
	QWidget::keyPressEvent(e);
}

void Calculator::on_button_clicked()
{	//调出按钮存储的数据
	std::string strOld = lineEdit->text().toStdString();
	QObject *pObject = this->sender();
	QPushButton *pbtn = qobject_cast<QPushButton *>(pObject);
	myname* aa = (myname*)(pbtn->userData(Qt::UserRole));
	if (aa == NULL){ return; }

	if (aa->name == "=")
	{//如果上个算式刚刚计算完紧接着输入下个算式，清空已有算式
		lineEdit->setText(QString("%1").arg(Calculate(strOld)));
		return;
	}
	else if (aa->name == "Delete")
	{
		lineEdit->backspace();
		lineEdit->setFocus();
	}
	else if (aa->name == "Clear")
	{
		lineEdit->clear();
		lineEdit->setFocus();
	}
	else
	{
		lineEdit->setText(QString("%1%2").arg(QString::fromStdString(strOld), aa->name.at(0)));
		return;
	}
}