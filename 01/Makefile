CC=g++
V=-std=c++14

all: test run 

calculator.o: calculator/calculator.cpp calculator/calculator.hpp
	$(CC) $(V) -c calculator/calculator.cpp

main.o: main.cpp calculator/calculator.hpp
	$(CC) $(V) -c main.cpp

test.o: test.cpp calculator/calculator.hpp
	$(CC) $(V) -c test.cpp

calc_compile: main.o calculator.o
	$(CC) $(V) -o calc main.o calculator.o

test_compile: test.o calculator.o
	$(CC) $(V) -o test test.o calculator.o

clean:
	rm -rf *.o calc test

run: calc_compile
	./calc "2 + 3 * 4 - -2"

test: test_compile
	./test