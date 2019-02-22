#pragma once
#ifndef Automaton_h_
#define Automaton_h_

#include <array>

#include "State.h"
class Automaton
{
  public:
	bool Test(const std::string &, const int x = 0, const int y = 0);

	Automaton();
	~Automaton();

  protected:
	std::vector<State *> m_vec;
	State *addState(int x, bool y);
};

#endif