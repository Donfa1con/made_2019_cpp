CC=g++
V=-std=c++14

all: test 

format.o: format/format.cpp format/format.hpp
	$(CC) $(V) -c format/format.cpp

test.o: test.cpp format/format.hpp
	$(CC) $(V) -c test.cpp

test_compile: test.o format.o
	$(CC) $(V) -o test test.o format.o

clean:
	rm -rf *.o test

test: test_compile
	./test