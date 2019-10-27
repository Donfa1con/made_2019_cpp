CC=g++
V=-std=c++14

all: test 

allocator.o: allocator/allocator.cpp allocator/allocator.hpp
	$(CC) $(V) -c allocator/allocator.cpp

test.o: test.cpp allocator/allocator.hpp
	$(CC) $(V) -c test.cpp

test_compile: test.o allocator.o
	$(CC) $(V) -o test test.o allocator.o

clean:
	rm -rf *.o test

test: test_compile
	./test