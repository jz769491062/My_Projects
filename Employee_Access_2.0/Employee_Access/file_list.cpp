/*Author: Zihan Zhu*/
/*A list of files user can view after logging in.*/
#include "file_list.h"  
#include "employee.h"
#include<QHBoxLayout>  
#include "LoginW.h"
#include <string>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

file_list::file_list(QWidget *parent) :
	QDialog(parent)
{
	setWindowTitle(tr("File List"));
	setStyleSheet("background-color:rgb(230,230,250)");
	returnButton = new QPushButton(("Return to login window"));
	QObject::connect(returnButton, SIGNAL(clicked()),this, SLOT(return_to_login()));
	auto ttt = Admin::getPtr();
	//��ȡ�ļ�
	std::vector<std::string> files = Admin::getPtr()->getCurrentWorker()->getWords();
	std::vector<std::string> extra = Admin::getPtr()->getCurrentWorker()->get_ea();
	std::vector<std::string> no = Admin::getPtr()->getCurrentWorker()->get_ed();

	//files.erase(remove(files.begin(), files.end(), ""), files.end());
	//extra.erase(remove(extra.begin(), extra.end(), ""), extra.end());
	//no.erase(remove(no.begin(), no.end(), ""), no.end());
	std::sort(files.begin(), files.end());
	std::sort(extra.begin(), extra.end());
	std::sort(no.begin(), no.end());
	std::vector<std::string> result(extra.size()+files.size());
	auto itU = std::set_union(extra.begin(), extra.end(), files.begin(), files.end(), result.begin());
	result.resize(itU - result.begin());
	std::vector<std::string> fresult(result.size());
	auto itD = std::set_difference(result.begin(), result.end(), no.begin(), no.end(), fresult.begin());
	fresult.resize(itD - fresult.begin());

	//�󲿵��б�
	left_list = new QListWidget;
	//�Ҳ�Ϊ�ļ�����
	right_stack = new QStackedWidget(this);
	for (size_t i = 0; i < fresult.size(); i++)
	{
		left_list->insertItem(i, QString::fromStdString(fresult[i]));
		//�ļ���λ��Visual Studio 2015\Projects\Employee_Access\x64\Debug\words
		std::string str = std::string(fresult[i]);
		QFile file(QString::fromStdString(str));
		if (!file.open(QFile::ReadWrite | QFile::Text))
		{//��ȡʧ�ܵĻ���������
			QMessageBox::warning(this, tr("Error"), tr("Cannot read file:%1").arg(file.errorString()));
		}
		QTextStream in(&file);
		label = new QLabel(in.readAll());
		right_stack->addWidget(label);
		file.close();
	}
	//������ʽ
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(left_list);
	QVBoxLayout *right_lay = new QVBoxLayout(this);
	right_lay->addWidget(right_stack, 0, Qt::AlignHCenter);
	right_lay->addWidget(returnButton, 0, Qt::AlignHCenter);
	mainLayout->addLayout(right_lay);
	mainLayout->setMargin(8);
	mainLayout->setSpacing(8);
	mainLayout->setStretchFactor(left_list, 3);
	mainLayout->setStretchFactor(right_lay, 6);
	//ÿ�ε������б�stackҲ���ű�
	connect(left_list, SIGNAL(currentRowChanged(int)), right_stack, SLOT(setCurrentIndex(int)));
}

void file_list::return_to_login()
{
	LoginW* logW = new LoginW();
	logW->show();
	close();
}
