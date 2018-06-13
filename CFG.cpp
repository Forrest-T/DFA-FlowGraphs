#include "CFG.h"
#include "DFA.h"
#include "FG.h"
#include <iostream>
#include <map>
using std::cout;
using std::endl;
using std::pair;

CFG::CFG(const DFA &D, const FG &F): S(GLOBAL_S) {
    /* CFG variables */
    V.insert(S);
    for (unsigned int i = 0; i < D.states.size(); i++)
        for (unsigned int j = 0; j < D.states.size(); j++) {
            for (const pair<string,Node> &p : F.nodes)
                V.insert(Variable(i, p.first, j));
            for (const string &s : D.alphabet)
                V.insert(Variable(i,s,j));
        }
    /* CFG terminals */
    for (const string &s : D.alphabet)
        T.insert(s);
    /* CFG production rules */
    // Rule 1
    for (unsigned int i = 0; i < D.states.size(); i++)
        if (D.states[i].accepting)
            P[GLOBAL_S].insert({Variable(D.start,F.funcs.at("main"),i)});
    // Rule 2
    for (const pair<string,Node> &pair : F.nodes) {
        const Node &n = pair.second;
        map<string,string>::const_iterator e = n.transitions.find("eps");
        if (e == n.transitions.end()) continue;
        for (unsigned int i = 0; i < D.states.size(); i++)
            for (unsigned int j = 0; j < D.states.size(); j++)
                P[Variable(i,pair.first,j)].insert({Variable(i,e->second,j)});
    }
    // Rule 3
    for (const pair<string,Node> &pair : F.nodes) {
        const Node &n = pair.second;
        for (const auto &edge : n.transitions) {
            if (!edge.first.compare("eps")) continue;
            for (unsigned int a = 0; a < D.states.size(); a++)
            for (unsigned int b = 0; b < D.states.size(); b++)
            for (unsigned int c = 0; c < D.states.size(); c++)
            for (unsigned int d = 0; d < D.states.size(); d++)
                P[Variable(a,pair.first,d)].insert(
                        {Variable(a,edge.first,b),
                         Variable(b,F.funcs.at(edge.first),c),
                         Variable(c,edge.second,d)});
        }
    }
    // Rule 4
    for (const pair<string,Node> &pair : F.nodes)
        if (pair.second.returning)
            for (unsigned int i = 0; i < D.states.size(); i++)
                P[Variable(i,pair.first,i)].insert({Variable("eps")});
    // Rule 5
    for (unsigned int i = 0; i < D.states.size(); i++)
        for (const string &s : D.alphabet)
            P[Variable(i,s,D.states[i].transitions.at(s))].insert({Variable(s)});

#ifdef DEBUG
    // print production rules
    for (const auto &p : P) {
        cout << p.first << ":" << endl;
        for (const auto &vec : p.second) {
            for (const auto &v : vec) cout << "  " << v;
            cout << endl;
        }
    }
#endif
}

string CFG::test() {
    map<Variable,vector<Variable>> s;
    for (const auto &t : T)
        s[Variable(t)] = {Variable(t)};
    unsigned int size;
    do {
        size = s.size();
        for (const auto &p : P) {
            if (s.count(p.first)) continue;
            for (const auto &vec : p.second) {
                bool producing = true;
                for (const auto &v : vec)
                    producing = producing && s.count(v);
                if (producing) s[p.first] = vec;
            }
        }
    } while (s.size() != size && !s.count(GLOBAL_S));
    if (!s.count(GLOBAL_S))
        return "Empty - specification not violated";
    return "Specification violated: "+produce(s, GLOBAL_S);
}

string CFG::produce(map<Variable,vector<Variable>> m,Variable v) {
    if (v.type == Variable::STRING && v != GLOBAL_S)
        return v.name;
    string s("");
    for (const Variable &V : m[v]) {
        string production = produce(m, V);
        if (!production.compare("eps")) continue;
        s += produce(m, V);
        if (s[s.length()-1] != ' ') s += " ";
    }
    return s;
}

bool Variable::operator==(const Variable &o) const {
    return qi == o.qi
        && qj == o.qj
        && !name.compare(o.name);
}

bool Variable::operator<(const Variable &r) const {
    if (type < r.type) return true;
    if (type > r.type) return false;
    if (name.compare(r.name)<0) return true;
    if (name.compare(r.name)>0) return false;
    if (qi < r.qi) return true;
    if (qi > r.qi) return false;
    return qj < r.qj;
}

ostream &operator<<(ostream &o, const Variable &v) {
    if (v.type == Variable::STRING)
        return o<<"["<<v.name<<"]";
    else
        return o<<"[q"<<v.qi<<", "<<v.X<<", q"<<v.qj<<"]";
}

Variable &Variable::operator=(const Variable &v) {
    type = v.type;
    name = v.name;
    qi = v.qi;
    qj = v.qj;
    return *this;
}
