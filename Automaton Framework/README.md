# Automaton Framework

Simple implementation of a framework to create nfa/dfa's

# How to:

Create a class with Automaton as a superclass.

To add a State use:
```cpp
addState(int state_id, bool endpoint)
```
state_id is the id of the state
endpoint is whether this state is a valid endpoint or not

To add a Transition use:
```cpp
State::addTransition(string input, vector<Transition> possible_transitions)
```
input being the input for the transition
possible_transitions being a vector containing all the possible transitions

For more information check the Examples in Automatons/Examples