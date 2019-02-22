// MultiThreadedPluginBasedSystem.cpp : Defines the entry point for the console application.
// 
#define BOOST_LIB_DIAGNOSTIC 1
#include "stdafx.h"
/*
In this Project I will try to learn about different ways of loading systems using plugin based methods
e.g. loading a subsystem as a direct-link-library
I will also try and optimize such system using multithreading


Todo:
-Create a SubSystem/Plugin Manager
	-Loop through Directory and load all .dll
-Create Test Plugin
-Multithreading :^)
*/
#include <iostream>

#include <string>
#include "Plugins/PluginManager.h"

#include <boost/filesystem.hpp>


int main( int argc, char* argv[] )
{


	std::string exeName( argv[0] );
	std::string exePath = exeName.substr( 0, exeName.find_last_of( "\\" ) );

	PluginManager* pm = new PluginManager( );


	boost::filesystem::directory_iterator dir_it_end;
	for( boost::filesystem::directory_iterator dir_it( exePath + "\\dlls" );
		dir_it != dir_it_end;
		dir_it++ )
	{
		if( boost::filesystem::extension( *dir_it ) == ".dll" ){
			std::cout << *dir_it << std::endl;
			pm->LoadPlugin( dir_it->path().c_str() );
		}
	}
	

	delete pm;
	std::cout << "End of main()";
	getchar( );
    return 0;
}

