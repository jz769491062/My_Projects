/********************************************************************************
** Form generated from reading UI file 'file_manip.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_MANIP_H
#define UI_FILE_MANIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_file_manip
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListWidget *left_list;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_4;
    QPushButton *btn_save;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QListWidget *right_list;
    QLabel *label_5;

    void setupUi(QDialog *file_manip)
    {
        if (file_manip->objectName().isEmpty())
            file_manip->setObjectName(QStringLiteral("file_manip"));
        file_manip->resize(567, 353);
        horizontalLayoutWidget = new QWidget(file_manip);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 530, 281));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        left_list = new QListWidget(horizontalLayoutWidget);
        left_list->setObjectName(QStringLiteral("left_list"));

        verticalLayout_2->addWidget(left_list);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setTextFormat(Qt::AutoText);
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setWordWrap(true);

        verticalLayout->addWidget(label_4);

        btn_save = new QPushButton(horizontalLayoutWidget);
        btn_save->setObjectName(QStringLiteral("btn_save"));

        verticalLayout->addWidget(btn_save);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        right_list = new QListWidget(horizontalLayoutWidget);
        right_list->setObjectName(QStringLiteral("right_list"));

        verticalLayout_3->addWidget(right_list);


        horizontalLayout->addLayout(verticalLayout_3);

        label_5 = new QLabel(file_manip);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 300, 531, 31));
        label_5->setScaledContents(false);
        label_5->setWordWrap(true);

        retranslateUi(file_manip);
        QObject::connect(left_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), file_manip, SLOT(move_file_right()));
        QObject::connect(right_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), file_manip, SLOT(move_file_left()));
        QObject::connect(btn_save, SIGNAL(clicked()), file_manip, SLOT(write_and_close()));

        QMetaObject::connectSlotsByName(file_manip);
    } // setupUi

    void retranslateUi(QDialog *file_manip)
    {
        file_manip->setWindowTitle(QApplication::translate("file_manip", "file_manip", 0));
        label_2->setText(QApplication::translate("file_manip", "Accessible files", 0));
        label->setText(QApplication::translate("file_manip", "Set selected file's accessibility", 0));
        label_4->setText(QApplication::translate("file_manip", "Double click file name to change accessibility.", 0));
        btn_save->setText(QApplication::translate("file_manip", "Save and quit", 0));
        label_3->setText(QApplication::translate("file_manip", "Inaccessible files", 0));
        label_5->setText(QApplication::translate("file_manip", "Clicking 'Save and quit' will apply change to all users with the same occupation as this user. Quit by clicking the upper right corner to apply change to this user only.", 0));
    } // retranslateUi

};

namespace Ui {
    class file_manip: public Ui_file_manip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_MANIP_H
