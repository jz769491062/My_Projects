#pragma once
#include <QWidget>
#include "ui_AdminW.h"
#include <qstandarditemmodel.h>
#include <qtableview.h>
#include <QtSql\QSql>
#include <QtSql\QSqlDatabase>
#include <QtSql\QSqlError>
#include <QtSql\QSqlQuery>

class AdminW : public QWidget
{
	Q_OBJECT

public:
	AdminW(QWidget *parent = Q_NULLPTR);
	~AdminW();
private:
	Ui::AdminW ui;
	bool loadFinished = false;
private slots:
	void add_user();
	void delete_user();
	void changeinfo();
	void adm_return_login();
	void open_manip();
};
