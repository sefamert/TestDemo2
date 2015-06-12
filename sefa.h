#ifndef STRESSTEST_H
#define STRESSTEST_H

#include "basetest.h"

class Sefa : public BaseTest
{
public:
	Sefa();
	int start();
	int stop();
	int run();
	int afterstart();
	const QList<QString> getTestResults();
	int testResult();

};

#endif // STRESSTEST_H
