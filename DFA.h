#ifndef _DFA_H_
#define _DFA_H_

#define DOT '.'

#include <string>
#include <vector>
#include <set>
#include <map>
using std::string;
using std::vector;
using std::map;
using std::set;

class State {
public:
    map<string,int> transitions;
    bool accepting;

    State() {}
    State(bool a): accepting(a) {}
    State(const State &o): transitions(o.transitions),
                           accepting(o.accepting) {}
    ~State() {}
};

class DFA {
public:
    int start;
    int active;
    set<string> alphabet;
    vector<State> states;

    DFA(set<string> a, int s): start(0),
                               active(0),
                               alphabet(a),
                               states(s) {}
    DFA(const DFA &o): start(o.start),
                       active(o.active),
                       alphabet(o.alphabet),
                       states(o.states) {}
    ~DFA() {}

    /* swaps final states */
    void complement();
    /* define the start state */
    void set_start(int);
    /* choose whether a state is accepting */
    void set_accept(int, bool);
    /* reset for reading a new string */
    void reset();
    /* adds a new (accepting?) state and returns its index */
    int add_state(bool);
    /* x --str--> y */
    void updateTransition(int, string, int);
    /* reads character or string */
    void read(string);
    bool accept();
    string print();
};

#endif
