#include <ctime>
#include <iostream>

#include "Automatons/Examples/ExampleAutomaton.h"
#include "Automatons/Examples/ExampleAutomaton2.h"

double TestBluePrint( int r ){
	double duration = 0, totalduration = 0;
	const int runs{ r };
	std::clock_t start;
	//Variables/Objects to be initialized before test


	for( size_t i = 0; i < runs; i++ ){
		start = clock( );


		duration = ( clock( ) - start ) / ( double ) CLOCKS_PER_SEC;
		std::cout << "Duration for this run of " << __FUNCTION__ << "() is : " << duration << "\n";

		totalduration += duration;
	}


	return totalduration / runs;
}

double Test1( int r ){
	double duration = 0, totalduration = 0;
	const int runs{ r };
	std::clock_t start;
	//Variables/Objects to be initialized before test
	ExampleAutomaton a;
	ExampleAutomaton2 a2;


	for( size_t i = 0; i < runs; i++ ){
		start = clock( );

		std::cout << std::boolalpha << a.Test("10101") << "\n";

		//std::cout << std::boolalpha << a2.Test( "011100" ) << "\n";

		duration = ( clock( ) - start ) / ( double ) CLOCKS_PER_SEC;
		std::cout << "Duration for this run of " << __FUNCTION__ << "() is : " << duration << "\n";

		totalduration += duration;
	}

	std::cout.flush( );
	return totalduration / runs;
}

void printTime( double time ){
	std::cout << "\nThe average time to complete the given Test was " << time << "ms";
}

int main( ){

	printTime( Test1( 1 ) );
	return 0;
}