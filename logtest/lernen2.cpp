// lernen2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>

#include "TestClass.h"
#include "TestClass3.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	TestClass test1;
	test1.printSomething();
	TestClass2 test2;
	test2.printSomething();
	TestClass3 test3;
	test3.printSOmething();
	LOGGER.WriteErrorLog("Shutting down system");
	getchar();
    return 0;
}

