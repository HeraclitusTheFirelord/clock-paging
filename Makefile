CFLAGS=-g  -Wall --std=c++11

all:test

test:main.o pagingTest.o
	g++ ${CFLAGS} -o $@ $+

.cpp.o:
	g++ -c ${CFLAGS} -o $@ $+

clean:
	rm -f *.o test
