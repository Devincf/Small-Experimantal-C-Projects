// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <iostream>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{


	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		std::cout << "Loaded TestPlugin 1!" << std::endl;
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		std::cout << "Unloaded TestPlugin 1!" << std::endl;
		break;
	}
	return TRUE;
}

