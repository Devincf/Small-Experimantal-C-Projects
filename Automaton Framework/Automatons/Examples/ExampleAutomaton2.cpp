#include "ExampleAutomaton2.h"


ExampleAutomaton2::ExampleAutomaton2( ){
	//initialize start

	//load States
	addState( 0, false )
		->addTransition( "", {
			{"",1 }
		} )
		->addTransition( "", {
			{"",3}
		} );

	addState( 1, false )
		->addTransition( "0", {
			{ "",2 }
		} )
		->addTransition( "1", {
			{ "",1 }
		} );

	addState( 2, true )
		->addTransition( "0", {
			{ "",1 }
		} )
		->addTransition( "1", {
			{ "",2 }
		} );

	addState( 3, false )
		->addTransition( "0", {
			{ "",3 }
		} )
		->addTransition( "1", {
			{ "",4 }
		} );

	addState( 4, true )
		->addTransition( "0", {
			{ "",4 }
		} )
		->addTransition( "1", {
			{ "",5 }
		} );

	addState( 5, true )
		->addTransition( "0", {
			{ "",5 }
		} )
		->addTransition( "1", {
			{ "",3 }
		} );
}


ExampleAutomaton2::~ExampleAutomaton2( ){ }
