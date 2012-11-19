#!/usr/bin/make -f

all: clean main

test: all 
	valgrind ./main.bin

main:
	g++ -g -Wall main.cpp -o bin

clean:
	rm bin *.o -f

