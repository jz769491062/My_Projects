/********************************************************************************
** Form generated from reading UI file 'LoginW.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINW_H
#define UI_LOGINW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWClass
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LoginWClass)
    {
        if (LoginWClass->objectName().isEmpty())
            LoginWClass->setObjectName(QStringLiteral("LoginWClass"));
        LoginWClass->resize(600, 400);
        centralWidget = new QWidget(LoginWClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(120, 40, 291, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(190, 220, 150, 23));
        pushButton_3->setMaximumSize(QSize(150, 16777215));
        LoginWClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LoginWClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        LoginWClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LoginWClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LoginWClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LoginWClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LoginWClass->setStatusBar(statusBar);

        retranslateUi(LoginWClass);
        QObject::connect(pushButton_3, SIGNAL(clicked()), LoginWClass, SLOT(login()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit_2, SLOT(setFocus()));
        QObject::connect(lineEdit_2, SIGNAL(returnPressed()), pushButton_3, SLOT(click()));

        QMetaObject::connectSlotsByName(LoginWClass);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWClass)
    {
        LoginWClass->setWindowTitle(QApplication::translate("LoginWClass", "Login Window", 0));
        label->setText(QApplication::translate("LoginWClass", "Username\357\274\232", 0));
        label_2->setText(QApplication::translate("LoginWClass", "Password\357\274\232", 0));
        pushButton_3->setText(QApplication::translate("LoginWClass", "Log in", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWClass: public Ui_LoginWClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINW_H
