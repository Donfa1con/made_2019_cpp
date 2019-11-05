CC=g++
V=-std=c++14

all: test run 

analyzer.o: analyzer/analyzer.cpp analyzer/analyzer.hpp
	$(CC) $(V) -c analyzer/analyzer.cpp

main.o: main.cpp analyzer/analyzer.hpp
	$(CC) $(V) -c main.cpp

test.o: test.cpp analyzer/analyzer.hpp
	$(CC) $(V) -c test.cpp

main_compile: main.o analyzer.o
	$(CC) $(V) -o main main.o analyzer.o

test_compile: test.o analyzer.o
	$(CC) $(V) -o test test.o analyzer.o

clean:
	rm -rf *.o main test

run: main_compile
	./main

test: test_compile
	./test