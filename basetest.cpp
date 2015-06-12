#include "basetest.h"
#include <QDateTime>
BaseTest::BaseTest()
{
	state = STATE_IDLE;
}

BaseTest::TestState BaseTest::getState()
{
	return state;
}

void BaseTest::setState(BaseTest::TestState s)
{
	state = s;
}
void BaseTest::testSiteANDtestOperator(QString site,QString oprtr)
{
	testSite=site;
	testOperator=oprtr;
}

void BaseTest :: starttime(QDateTime dt)
{
	startTime=dt;
}
void BaseTest :: finishtime(QDateTime dt)
{
	finishTime=dt;
}

