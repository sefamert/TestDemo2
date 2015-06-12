#include "sefa.h"
#include <QDebug>
#include <unistd.h>

Sefa :: Sefa()
	: BaseTest()
{
}

int Sefa :: start()
{
	setState(STATE_STARTING);
	return 0;
}
int Sefa :: afterstart()
{
	setState(STATE_RUNNING);
	return 0;
}
int Sefa :: stop()
{
	setState(STATE_IDLE);
	qDebug("case solved!, stopping");
	return 0;
}
int Sefa :: run()
{
	int duration = 3;
	for (int i = 0; i < duration; i++) {
		qDebug("message %d out of %d", i, duration);
		sleep(1);
	}
	setState(STATE_STOPPING);

	return 0;
}
const QList<QString> Sefa :: getTestResults()
{
	QStringList list;
	list << "Everything is ok";
	return list;
}
int Sefa :: testResult()
{

	return 0;
}

