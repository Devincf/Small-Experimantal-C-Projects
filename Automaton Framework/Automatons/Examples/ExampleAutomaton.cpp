#include "ExampleAutomaton.h"



ExampleAutomaton::ExampleAutomaton( ){
	//define entry point to automat

	//add ZustUende
	addState( 0, false )
		->addTransition( "0", {
			{"",1} ,{"",0}
		} )
		->addTransition( "1", {
			{"",2} , {"",0}
		} );

	addState( 1, false )
		->addTransition( "0", {
			{"",3}
		} );

	addState( 2, false )
		->addTransition( "1", {
			{"",3}
		} );

	addState( 3, true )
		->addTransition( "0", {
			{ "",3 }
		} )
		->addTransition( "1", {
			{ "",3 }
		} );
}


ExampleAutomaton::~ExampleAutomaton( ){ }
