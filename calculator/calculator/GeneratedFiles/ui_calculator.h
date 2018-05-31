/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_calculatorClass
{
public:

    void setupUi(QDialog *calculatorClass)
    {
        if (calculatorClass->objectName().isEmpty())
            calculatorClass->setObjectName(QStringLiteral("calculatorClass"));
        calculatorClass->resize(600, 400);

        retranslateUi(calculatorClass);

        QMetaObject::connectSlotsByName(calculatorClass);
    } // setupUi

    void retranslateUi(QDialog *calculatorClass)
    {
        calculatorClass->setWindowTitle(QApplication::translate("calculatorClass", "calculator", 0));
    } // retranslateUi

};

namespace Ui {
    class calculatorClass: public Ui_calculatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
