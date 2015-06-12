#include "basetest.h"
#include "sefa.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QVariant>

#include <iostream>
#include <cstring>

using namespace std;

/*
 * camel casing,      +
 * Serialization:     +
 *	- versioning, signature     +
 *	- endianness(little-endian,big-endian)
 * Event loop
 * QHash ve QMap arasındakı fark?				+
 *
 * github:
 *	- URL
 *	- git remote
 *	- git push|pull
 *	- ssh-keygen
 */

void enterNameSurname(QString &oprtr,QString &site)
{
	QTextStream qtin(stdin);
	QString name,surname;
		cout<<"Please enter name and surname: ";
		qtin>>name>>surname;
		name.append(" ");
		name.append(surname);
		oprtr=name;
		cout<<"\nPlease enter your site: ";
		qtin>>site;

}

int chooseTest(void)
{
	cout<<"Please choose the test which you want : \n";
	cout<<"(1)-Functionality Test \n";
	cout<<"(2)-Stress Test \n";
	cout<<"(3)-Performance Test  :  ";
	int choose;
	cin>>choose;
	return choose;
}

void afterChooseTest(Sefa t,QDataStream &stream)
{
	int num;
	t.starttime(QDateTime :: currentDateTime());
	qDebug()<<QDateTime :: currentDateTime();
	num=t.getState();
	qDebug() << "test with state" << t.getState();

	stream << QString("test with state")<< num;								//Stream

	t.start();

	num=t.getState();
	qDebug() << "test with state" << t.getState();

	stream << QString("test with state")<< num;								//Stream

	/* wait test to start */
	while (t.getState() == BaseTest::STATE_STARTING)
	{
		t.afterstart();
	}

	qDebug("test is started");
	/* now the test is running, wait it for to be completed */

	num=t.getState();
	qDebug() << "test with state" << t.getState();

		stream << QString("test with state")<< num;							//Stream

	while (t.getState() == BaseTest::STATE_RUNNING)
		t.run();
	num=t.getState();

	stream << QString("test with state")<< num;								//Stream

	t.stop();

	num=t.getState();
	qDebug() << "test finished with state" << t.getState();

		stream << QString("test finished with state")<< num;				//Stream

	/* save test results to the disk */

	t.finishtime(QDateTime :: currentDateTime());
	qDebug()<<QDateTime :: currentDateTime();

}

void afterWritingFile(void)
{
	qDebug("\n\nAfter Writing File:\n\n");
	QFile file2("setting.dat");
	file2.open(QIODevice::ReadOnly);
	//while(file2.isOpen() == 0);
	QDataStream stream2(&file2);
	QString str,str2;
	int num2;
	stream2>>num2;
	if(num2!=0x11223344)
	{
		qDebug("This folder is wrong");
		return ;
	}

	stream2>>str;
	qDebug()<<str;

	stream2>>str>>str2;
	qDebug() << str<<str2;

	stream2 >> str;
	qDebug() << str;

	stream2 >> str>>num2;
	qDebug() << str<<num2;

	stream2 >> str>>num2;
	qDebug() << str<<num2;

	stream2 >> str>>num2;
	qDebug() << str<<num2;

	stream2 >> str>>num2;
	qDebug() << str<<num2;

	stream2 >> str>>num2;
	qDebug() << str<<num2;


}

int main(int argc, char *argv[])
{
	(void)argc; //make compiler happy
	(void)argv;
	QFile file("setting.dat");
	file.open(QIODevice::WriteOnly);
	QDataStream stream(&file);

	int sign=0x11223344;
	stream<<sign;															//Stream
	QString version("Version 0");
	stream<<version;

	QString oprtr,site;
	enterNameSurname(oprtr,site);
	qDebug()<<oprtr<<site<<endl;

	stream<<oprtr<<site;													//Stream

	Sefa t;
//---------------------------------------------------------------------------------------
	t.testSiteANDtestOperator(oprtr,site);
	int num;
	num=chooseTest();
	if(num==1)
	{
		stream<<QString("Selected test is Functionality Test ");						//Stream

	}															//go to Functionality Test
	else if(num==2)
	{
		stream<<QString("Selected test is Stress Test ");							//Stream

	}															//go to Stress Test
	else if(num==3)
	{
		stream<<QString("Selected test is Performance Test ");						//Stream

	}															//go to Performance Test
	else
	{
		qDebug("Wrong input");
		return 0;
	}
//-----------------------------------------------------------------------------------------

	afterChooseTest(t,stream);

	file.close();

	afterWritingFile();

	return 0;
}
