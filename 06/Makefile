CC=g++
V=-std=c++14

all: test 

BigInt.o: BigInt/BigInt.cpp BigInt/BigInt.hpp
	$(CC) $(V) -c BigInt/BigInt.cpp

test.o: test.cpp BigInt/BigInt.hpp
	$(CC) $(V) -c test.cpp

test_compile: test.o BigInt.o
	$(CC) $(V) -o test test.o BigInt.o

clean:
	rm -rf *.o test

test: test_compile
	./test