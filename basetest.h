#ifndef BASETEST_H
#define BASETEST_H

#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVariant>

class BaseTest
{
public:
	BaseTest();

	enum TestState {
		STATE_IDLE,
		STATE_STARTING,
		STATE_RUNNING,
		STATE_STOPPING,
	};

	virtual int start() = 0;
	virtual int stop() = 0;
	virtual int run() = 0;
	virtual const QList<QString> getTestResults() = 0;
	TestState getState();
	void starttime(QDateTime dt);
	void finishtime(QDateTime dt);

	void testSiteANDtestOperator(QString site,QString oprtr);
	virtual int testResult() = 0;

protected:
	void setState(TestState s);

	QStringList log;							/* will be filled by sub-classes */		//Burada neler tutulacaktı?
	QHash<QString, QVariant> testParameters;    /* will be set by sub-class users */	//Burada neler tutulacaktı?
private:
	TestState state;					//yapıldı
	QDateTime startTime;				//yapıldı
	QDateTime finishTime;				//yapıldı
	QString testSite;					//yapıldı
	QString testOperator;				//yapıldı
	/* run time */
};

#endif // BASETEST_H
