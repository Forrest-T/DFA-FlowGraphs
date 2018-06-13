#include "string.h"
#include "parse.h"
#include "DFA.h"
#include "FG.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::set;

int readSpec(char *specFile, DFA **d) {
    ifstream file;
    string line;
    file.open(specFile);
    if(!file.is_open()) {
        cout << "could not open file" << endl;
        return 0;
    }

    // read lines from file
    vector<string> lines;
    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // parse lines into alphabet and states
    string start;
    set<string> alphabet;
    set<pair<string,bool>> states;
    for (auto &line : lines) {
        if (line[0] == '=') start = state1(line).first;
        states.insert(state1(line));
        alphabet.insert(edge(line));
    }
    // create DFA
    *d = new DFA(alphabet,0);
    map<string,int> s2i;
    for (auto &state : states)
        s2i[state.first] = (*d)->add_state(state.second);
    (*d)->set_start(s2i[start]);
    for (auto &line : lines) {
        (*d)->updateTransition(s2i[state1(line).first],edge(line),s2i[state2(line).first]);
    }
#ifdef DEBUG
    cout << (*d)->print() << endl;
#endif
    return 1;
}

pair<string,bool> state1(string line) {
    return pair<string,bool>(line.substr(line.find_first_of({'(','['})+1, line.substr(line.find_first_of({'(','['})+1).find_first_of({')',']'})),line.find_first_of('(')<line.find_first_of(']'));
}
pair<string,bool> state2(string line) {
    line = line.substr(line.find_first_of({']',')'})+1);
    return pair<string,bool>(line.substr(line.find_first_of({'(','['})+1, line.substr(line.find_first_of({'(','['})+1).find_first_of({')',']'})),line.find_last_of(')')<line.find_last_of(']'));
}
string edge(string line) {
    return line.substr(line.find_first_of('-')+1,line.find_last_of('-')-line.find_first_of('-')-1);
}

int readGraph(char *flowFile, FG **g) {
    ifstream file;
    string line;
    file.open(flowFile);
    if(!file.is_open()) {
        cout << "could not open file" << endl;
        return 0;
    }

    // read lines from file
    vector<string> lines;
    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    map<string,Node> nodes;
    map<string,string> funcs;
    for (auto &line : lines)
        if (!line.substr(0,4).compare("node")) {
            NodeInfo n = parse_node(line);
            nodes[n.name] = Node(n.ret);
            if (n.entry) funcs[n.func] = n.name;
        }
    *g = new FG(funcs, nodes);
    for (auto &line : lines)
        if (!line.substr(0,4).compare("edge")) {
            EdgeInfo e = parse_edge(line);
            (*g)->addTransition(e.s, e.e, e.d);
        }
#ifdef DEBUG
    cout << (*g)->print() << endl;
#endif

    return 1;
}

NodeInfo parse_node(string line) {
    NodeInfo info;
    line = line.substr(line.find_first_of(' ')+1);
    info.name = line.substr(0, line.find_first_of(' '));
    line = line.substr(line.find_first_of(' ')+6);
    info.func = line.substr(0, line.find_first_of(')'));
    line = line.substr(line.find_first_of(' ')+1);
    line = line.substr(0, line.find_first_of({'\r', '\n'}));
    info.entry = !line.compare("entry");
    info.ret = !line.compare("ret");
    return info;
}

EdgeInfo parse_edge(string line) {
    EdgeInfo info;
    line = line.substr(line.find_first_of(' ')+1);
    info.s = line.substr(0,line.find_first_of(' '));
    line = line.substr(line.find_first_of(' ')+1);
    line = line.substr(line.find_first_not_of(' '));
    info.d = line.substr(0,line.find_first_of(' '));
    line = line.substr(line.find_first_of(' ')+1);
    line = line.substr(line.find_first_not_of(' '));
    info.e = line.substr(0,line.find_first_of({'\r', '\n'}));
    return info;
}
