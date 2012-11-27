#!/usr/bin/make -f

all: clean main

test: all 
	valgrind ./bin

main:
	g++ -g -Wall -Wextra -Werror -pedantic -std=c++11 main.cpp -o bin

clean:
	rm bin *.o -f

