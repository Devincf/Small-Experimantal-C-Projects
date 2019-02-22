#pragma once
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <stack>
#include <Windows.h>

class PluginManager{
public:
	~PluginManager( );
	PluginManager( );

	bool LoadPlugin( LPCWSTR path );
	
 private:
	 std::stack<HMODULE> m_plugins;

};

#endif
