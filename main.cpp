#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "FG.h"
#include "DFA.h"
#include "CFG.h"
#include "parse.h"
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Missing input file argument\n");
        printf("Usage: ./run ___.spec ___.cfg\n");
        exit(1);
    }
    DFA *d = NULL;
    FG *f = NULL;
    // parse DFA
    int status = readSpec(argv[1], &d);
    if (status == 0) exit(1);
    // parse FG
    status = readGraph(argv[2], &f);
    if (status == 0) exit(1);
    // complement DFA
    d->complement();
    // TODO: CFG product
    CFG C(*d, *f);
    // TODO: emptiness test
    cout << C.test() << endl;

    delete d;
    delete f;
    return 0;
}
