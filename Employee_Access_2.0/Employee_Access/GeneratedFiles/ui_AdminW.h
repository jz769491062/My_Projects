/********************************************************************************
** Form generated from reading UI file 'AdminW.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINW_H
#define UI_ADMINW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminW
{
public:
    QLabel *label_type;
    QLabel *label_name;
    QLabel *label_pswd;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_pswd;
    QPushButton *Button_create;
    QPushButton *Button_delete;
    QLabel *label_title;
    QComboBox *typeBox;
    QLabel *label;
    QTableWidget *tbl;
    QPushButton *btn_return_login;

    void setupUi(QWidget *AdminW)
    {
        if (AdminW->objectName().isEmpty())
            AdminW->setObjectName(QStringLiteral("AdminW"));
        AdminW->resize(493, 355);
        label_type = new QLabel(AdminW);
        label_type->setObjectName(QStringLiteral("label_type"));
        label_type->setGeometry(QRect(250, 50, 51, 21));
        label_name = new QLabel(AdminW);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(250, 90, 51, 21));
        label_pswd = new QLabel(AdminW);
        label_pswd->setObjectName(QStringLiteral("label_pswd"));
        label_pswd->setGeometry(QRect(250, 130, 51, 21));
        lineEdit_name = new QLineEdit(AdminW);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(330, 90, 113, 21));
        lineEdit_pswd = new QLineEdit(AdminW);
        lineEdit_pswd->setObjectName(QStringLiteral("lineEdit_pswd"));
        lineEdit_pswd->setGeometry(QRect(330, 130, 113, 20));
        Button_create = new QPushButton(AdminW);
        Button_create->setObjectName(QStringLiteral("Button_create"));
        Button_create->setGeometry(QRect(340, 170, 81, 31));
        Button_delete = new QPushButton(AdminW);
        Button_delete->setObjectName(QStringLiteral("Button_delete"));
        Button_delete->setGeometry(QRect(10, 300, 201, 21));
        label_title = new QLabel(AdminW);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(320, 10, 111, 31));
        label_title->setLineWidth(1);
        label_title->setTextFormat(Qt::AutoText);
        label_title->setAlignment(Qt::AlignCenter);
        label_title->setIndent(0);
        typeBox = new QComboBox(AdminW);
        typeBox->setObjectName(QStringLiteral("typeBox"));
        typeBox->setGeometry(QRect(330, 50, 111, 21));
        label = new QLabel(AdminW);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 10, 131, 21));
        label->setAlignment(Qt::AlignCenter);
        tbl = new QTableWidget(AdminW);
        tbl->setObjectName(QStringLiteral("tbl"));
        tbl->setGeometry(QRect(10, 40, 201, 231));
        tbl->setRowCount(0);
        tbl->setColumnCount(0);
        tbl->verticalHeader()->setVisible(false);
        btn_return_login = new QPushButton(AdminW);
        btn_return_login->setObjectName(QStringLiteral("btn_return_login"));
        btn_return_login->setGeometry(QRect(310, 300, 151, 21));

        retranslateUi(AdminW);
        QObject::connect(lineEdit_name, SIGNAL(returnPressed()), lineEdit_pswd, SLOT(setFocus()));
        QObject::connect(tbl, SIGNAL(cellClicked(int,int)), Button_delete, SLOT(show()));
        QObject::connect(Button_delete, SIGNAL(clicked()), AdminW, SLOT(delete_user()));
        QObject::connect(Button_create, SIGNAL(clicked()), AdminW, SLOT(add_user()));
        QObject::connect(tbl, SIGNAL(cellChanged(int,int)), AdminW, SLOT(changeinfo()));
        QObject::connect(lineEdit_pswd, SIGNAL(returnPressed()), Button_create, SLOT(click()));
        QObject::connect(btn_return_login, SIGNAL(clicked()), AdminW, SLOT(adm_return_login()));
        QObject::connect(tbl, SIGNAL(cellDoubleClicked(int,int)), AdminW, SLOT(open_manip()));

        QMetaObject::connectSlotsByName(AdminW);
    } // setupUi

    void retranslateUi(QWidget *AdminW)
    {
        AdminW->setWindowTitle(QApplication::translate("AdminW", "Admin Window", 0));
        label_type->setText(QApplication::translate("AdminW", "UserType:", 0));
        label_name->setText(QApplication::translate("AdminW", "Username:", 0));
        label_pswd->setText(QApplication::translate("AdminW", "Password:", 0));
        Button_create->setText(QApplication::translate("AdminW", "Create User", 0));
        Button_delete->setText(QApplication::translate("AdminW", "Delete User at selected line", 0));
        label_title->setText(QApplication::translate("AdminW", "Create User:", 0));
        label->setText(QApplication::translate("AdminW", "User List:", 0));
        btn_return_login->setText(QApplication::translate("AdminW", "Return to login window", 0));
    } // retranslateUi

};

namespace Ui {
    class AdminW: public Ui_AdminW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINW_H
