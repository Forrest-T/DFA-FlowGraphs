#include "DFA.h"
#include "stdio.h"
#include <string>
using std::string;

static int failed = 0;

void test(DFA &d, const char *s, int accept) {
    d.reset();
    while(*s!='\0') d.read(string(1,*(s++)));
    if (accept == d.accept())
        printf("\t\033[32mCORRECT\033[37m\t %s \"%s\"\n", accept?"accepted":"rejected", s);
    else
        (printf("\t\033[31mWRONG\033[37m\t %s \"%s\"\n", accept?"rejected":"accepted", s), failed++);
}

void test_even() {
    DFA d(set<string>{"a","b"}, 0);
    int q0 = d.add_state(1);
    d.set_start(q0);
    int q1 = d.add_state(0);
    d.updateTransition(q0, "a", q1);
    d.updateTransition(q1, "a", q0);
    d.updateTransition(q0, "b", q1);
    d.updateTransition(q1, "b", q0);
    test(d, "", 1);
    test(d, "a", 0);
    test(d, "b", 0);
    test(d, "aa", 1);
    test(d, "bbb", 0);
}

void test_end_a() {
    DFA d(set<string>{"a","s","d","f","g"}, 0);
    int q0 = d.add_state(0);
    int q1 = d.add_state(1);
    d.set_start(q0);
    d.updateTransition(q0, "a", q1);
    d.updateTransition(q1, "a", q1);
    d.updateTransition(q0, "s", q0);
    d.updateTransition(q1, "s", q0);
    d.updateTransition(q0, "d", q0);
    d.updateTransition(q1, "d", q0);
    d.updateTransition(q0, "f", q0);
    d.updateTransition(q1, "f", q0);
    d.updateTransition(q0, "g", q0);
    d.updateTransition(q1, "g", q0);
    test(d, "", 0);
    test(d, "a", 1);
    test(d, "s", 0);
    test(d, "agf", 0);
    test(d, "sdfasdgasdfasdfa", 1);
}

int main() {
    printf("Testing even number of characters\n");
    test_even();
    printf("Testing ends in a\n");
    test_end_a();

    printf("Number of failed tests: %d\n", failed);
}

