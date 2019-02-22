#include "Automaton.h"

Automaton::Automaton()
{
}
Automaton::~Automaton()
{

    for (auto i : m_vec)
    {
        delete i;
    }
}

State *Automaton::addState(int x, bool y)
{
    State *tempState = new State(x, y);
    m_vec.push_back(tempState);
    return tempState;
}

bool Automaton::Test(const std::string &str, const int offset, const int currState)
{

    //return true if at end of string and can end in zustand
    if (offset == str.size() && m_vec.at(currState)->canEnd())
        return true;

    //load all Transitions from current zustand with specific str
    const auto transitions = m_vec.at(currState)->findAllTransitions(str.substr(offset));

    //return false if no Uebergang found
    if (transitions.size() == 0)
        return false;

    //for each Uebergang call Test again with different offset and the next State
    //if Test returns true, return true aswell.
    for (auto i : transitions)
    {
        if (Test(str, offset + i.input.size(), i.transition.nextState))
            return true;
    }

    return false;
}