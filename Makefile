CMP = g++
FLAGS = -g --std=c++11 -Wall -Wextra -lm

.PHONY: clean all

all: run test_DFA

%.o: %.cpp %.h
	$(CMP) $(FLAGS) -c -o $@ $<

DFA.cpp: DFA.h
parse.cpp: parse.h

run: main.cpp parse.o DFA.o FG.o CFG.o
	$(CMP) $(FLAGS) -o $@ $^
test_DFA: DFA_test.o DFA.o
	$(CMP) $(FLAGS) -o $@ $^
clean:
	rm -rf *.o test_DFA run
