CMP = gcc
FLAGS = -g -Wall -Wextra -lm

.PHONY: clean all

all: test_DFA

%.o: %.c
	$(CMP) $(FLAGS) -c -o $@ $<

DFA.c: DFA.h
DFA_print.c: DFA_print.h

test_DFA: DFA_test.o DFA.o DFA_print.o
	$(CMP) $(FLAGS) -o $@ $^
clean:
	rm -rf *.o test_DFA
