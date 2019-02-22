#pragma once
#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "Log.h"

class TestClass
{
public:

	virtual void printSomething() {
		LOGGER.WriteSuccessLog("Test!!!");
	}

	TestClass() {};
	~TestClass() {};
};

class TestClass2 : TestClass{
public:
	void printSomething() {
		LOGGER.WriteWarningLog("YEAAAAAHHH");
	}
	TestClass2() {};
	~TestClass2() {};
};
#endif
