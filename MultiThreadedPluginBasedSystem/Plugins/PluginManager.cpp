#include "stdafx.h"
#include "PluginManager.h"
#include "Help.h"

PluginManager::~PluginManager( )
{ 
	while( !m_plugins.empty( ) ){
		FreeLibrary( m_plugins.top( ) );
		m_plugins.pop( );
	}
}

PluginManager::PluginManager( )
{ }

bool PluginManager::LoadPlugin(LPCWSTR path )
{
	HMODULE LibraryHandle = LoadLibrary( path );
	m_plugins.push( LibraryHandle );
	return true;
}
