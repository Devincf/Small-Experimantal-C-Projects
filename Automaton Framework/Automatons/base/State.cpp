#include "State.h"



State::State( ){ }

State::State( const int& id, const bool& canend = false ) :m_id( id ), m_canEnd( canend ){

}


State::~State( ){ }

State* State::addTransition( const std::string str, const std::vector<Transition> x ){
	//create new map entry if key str nonexistant
	//inserts all transitions into key str otherwise
	if( m_transitions.find( str ) == m_transitions.end( ) ){
		m_transitions.insert( std::pair<std::string, std::vector<Transition>>( str, x ) );
	} else{
		m_transitions[str].insert( m_transitions[str].begin( ), x.begin( ), x.end( ) );
	}
	//returns pointer to this obj
	return this;
}

std::vector<Result> State::findAllTransitions( std::string s ){
	std::vector<Result> v{ };

	//for every possible string possibility (input : 1010 -> 1,10,101,1010)
	for( int i = 0; i < s.size( ); i++ ){
		std::string temp = s.substr( 0, i + 1 );
		//if map contains key then add all �berg�nge to temp object v
		if( m_transitions.find( temp ) != m_transitions.end( ) ){
			for( auto i : m_transitions[temp] ){
				v.push_back( { i,temp } );
			}
		}
	}

	//add all paths with e-symbol

	for( auto i : m_transitions[""] ){
		v.push_back( { i,"" } );
	}

	return v;
}

const bool State::canEnd( ) const{
	return m_canEnd;
}