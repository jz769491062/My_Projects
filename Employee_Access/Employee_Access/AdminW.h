#pragma once

#include <QWidget>
#include "Employee.h"
#include "ui_AdminW.h"
#include <qstandarditemmodel.h>
#include <qtableview.h>

class AdminW : public QWidget
{
	Q_OBJECT

public:
	AdminW(QWidget *parent = Q_NULLPTR);
	~AdminW();
private:
	Ui::AdminW ui;
	void update_list();
private slots:
	void add_user();
	void delete_user();
	void changeinfo();
	void adm_return_login();
	void open_manip();
};
