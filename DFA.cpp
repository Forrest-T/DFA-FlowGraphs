#include "stdlib.h"
#include "DFA.h"

void DFA::reset() { active = start; }

void DFA::set_start(int i) { start = i; }

bool DFA::accept() { return states[active].accepting; }

void DFA::set_accept(int i, bool a) { states[i].accepting = a; }

void DFA::complement() { 
    for (auto &state : states)
        state.accepting ^= true;
}

int DFA::add_state(bool a) {
    states.push_back(State(a));
    return states.size()-1;
}

void DFA::updateTransition(int s, string e, int d) {
    if (std::max(s,d) >= (int)states.size()
        || std::min(s,d) < 0
        || alphabet.find(e) == alphabet.end()) return;
    states[s].transitions[e] = d;
}

void DFA::read(string s) { active = states[active].transitions[s]; }

string DFA::print() {
    string s("DFA:\n");
    s.append("  start: ");
    s.append(std::to_string(start)+"\n");
    s.append("  active: ");
    s.append(std::to_string(active)+"\n");
    s.append("  States: "+std::to_string(states.size())+"\n");
    for (unsigned int i = 0; i < states.size(); i++) {
        s.append("    state #");
        s.append(std::to_string(i));
        s.append("  accepting: ");
        s.append((states[i].accepting)?"yes":"no");
        s.append("\n");
        for (auto &trans : states[i].transitions) {
            s.append("      #");
            s.append(std::to_string(i));
            s.append(" --");
            s.append(trans.first);
            s.append("--> #");
            s.append(std::to_string(trans.second));
            s.append("\n");
        }
    }
    return s;
}
