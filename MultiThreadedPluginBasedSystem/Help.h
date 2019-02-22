#pragma once
#include <windows.h>

LPCWSTR charArrToLPCWSTR( char* cstr )
{
	wchar_t wtext[64];
	mbstowcs( wtext, cstr, strlen( cstr ) + 1 );//Plus null
	LPWSTR ptr = wtext;
	return ptr;
}
