#ifndef FG_H_
#define FG_H_

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::pair;
using std::map;

class Node {
public:
    map<string,string> transitions;
    bool returning;

    Node() {}
    Node(bool r): transitions(), returning(r) {}
    ~Node() = default;
};

class FG {
public:
    /* function name --> entry node */
    map<string,string> funcs;
    map<string,Node> nodes;

    FG(map<string,string> f, map<string,Node> n): funcs(f), nodes(n) {}
    ~FG() = default;

    void addTransition(string s, string e, string d) { nodes[s].transitions[e] = d; }
    string print();
};

#endif
