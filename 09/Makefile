CC=g++
V=-std=c++14

all: test 

threadpool.o: threadpool/threadpool.cpp threadpool/threadpool.hpp
	$(CC) $(V) -c threadpool/threadpool.cpp

test.o: test.cpp threadpool/threadpool.hpp
	$(CC) $(V) -c test.cpp

test_compile: test.o threadpool.o
	$(CC) $(V) -o test test.o threadpool.o

clean:
	rm -rf *.o test

test: test_compile
	./test