#ifndef PARSE_H_
#define PARSE_H_

#include "DFA.h"
#include "FG.h"
#include <string>
#include <map>
//#define DEBUG
using std::string;
using std::pair;
using std::map;

typedef struct {
    string name;
    string func;
    bool entry;
    bool ret;
} NodeInfo;

typedef struct {
    string s;
    string e;
    string d;
} EdgeInfo;

int readGraph(char *flowFile, FG **g);
NodeInfo parse_node(string);
EdgeInfo parse_edge(string);

int readSpec(char *specFile, DFA **d);
pair<string,bool> state1(string);
pair<string,bool> state2(string);
string edge(string);

#endif
