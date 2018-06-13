#include "FG.h"

string FG::print() {
    string s("FG:\n");
    s += "  Functions:\n";
    for (auto &f : funcs) {
        s += "    ";
        s += f.first;
        s += ", entry point: ";
        s += f.second;
        s += "\n";
    }
    s += "  Nodes:\n";
    for (auto &n : nodes) {
        s += "    ";
        s += n.first;
        if (n.second.returning) s += "\n      (returning)";
        s += "\n";
        for (auto &e : n.second.transitions) {
            s += "      --";
            s += e.first;
            s += "--> ";
            s += e.second;
            s += "\n";
        }
    }
    return s;
}
