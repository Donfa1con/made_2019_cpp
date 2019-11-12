CC=g++
V=-std=c++14

all: test run

matrix.o: matrix/matrix.cpp matrix/matrix.hpp
	$(CC) $(V) -c matrix/matrix.cpp

main.o: main.cpp matrix/matrix.hpp
	$(CC) $(V) -c main.cpp

test.o: test.cpp matrix/matrix.hpp
	$(CC) $(V) -c test.cpp

main_compile: main.o matrix.o
	$(CC) $(V) -o main main.o matrix.o

test_compile: test.o matrix.o
	$(CC) $(V) -o test test.o matrix.o

clean:
	rm -rf *.o main test

run: main_compile
	./main

test: test_compile
	./test