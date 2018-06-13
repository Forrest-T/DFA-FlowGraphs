#ifndef CFG_H_
#define CFG_H_

#include "DFA.h"
#include "FG.h"
#include <vector>
#include <string>
#include <set>
#include <map>
using std::vector;
using std::string;
using std::set;
using std::map;
using std::ostream;

class Variable {
public:
    /* Two possible types:
     *   string:   [    name   ]
     *   triple:   [ qi, X, qj ]
     */
    enum {STRING, TRIPLE} type;
    string name;
    string &X;
    int qi = 0;
    int qj = 0;

    Variable(string s):type(STRING),name(s),X(name){}
    Variable(int i, string s, int j):type(TRIPLE),name(s),X(name),qi(i),qj(j){}
    Variable(const Variable &v):type(v.type),name(v.name),X(name),qi(v.qi),qj(v.qj){}
    Variable &operator=(const Variable &);
    bool operator<(const Variable &) const;
    bool operator==(const Variable &) const;
    bool operator!=(const Variable &o) const {return !(*this == o);};
    ~Variable() {}

    friend ostream &operator<<(ostream &, const Variable &);
};

/* Initial production variable */
static Variable GLOBAL_S("<<>>");

class CFG {
public:
    set<Variable> V;
    set<string> T;
    map<Variable,set<vector<Variable>>> P;
    Variable S;

    CFG(const DFA&,const FG&);
    string test();
private:
    string produce(map<Variable,vector<Variable>>,Variable);
};

#endif
