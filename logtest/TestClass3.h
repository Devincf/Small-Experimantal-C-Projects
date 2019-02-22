#pragma once
#ifndef TESTCLASS3_H
#define TESTCLASS3_H
#include "Log.h"
class TestClass3
{
public:
	TestClass3();
	void printSOmething() { LOGGER.ClearConsole(); LOGGER.WriteSuccessLog("Console Cleared!"); }
	~TestClass3();
};

#endif