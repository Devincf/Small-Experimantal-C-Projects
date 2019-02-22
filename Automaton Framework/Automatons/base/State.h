#pragma once
#ifndef State_h_
#define State_h_

#include <map>
#include <string>
#include <vector>

struct Transition{
	std::string output;
	int nextState;
};

struct Result{
	Transition transition;
	std::string input;
};


class State{
public:
	State( );
	State( const int&, const bool& );
	~State( );

	const bool canEnd( )const;

	State* addTransition( const std::string, const std::vector<Transition> );
	std::vector<Result> findAllTransitions( std::string );

private:
	int m_id;
	bool m_canEnd;

	std::map<std::string, std::vector<Transition>> m_transitions;


};

#endif