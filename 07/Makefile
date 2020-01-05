CC=g++
V=-std=c++14

all: test 

test.o: test.cpp format.hpp
	$(CC) $(V) -c test.cpp

test_compile: test.o
	$(CC) $(V) -o test test.o

clean:
	rm -rf *.o test

test: test_compile
	./test 