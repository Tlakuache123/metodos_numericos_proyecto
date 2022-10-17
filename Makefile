# Compilador
CC = g++

CFLAGS = -Wall -g

all: main

main: main.o matrix.o
	$(CC) $(CFLAGS) -o main main.o matrix.o

main.o: main.cpp matrix.o
	$(CC) $(CFLAGS) main.cpp

matrix.o: matrix.h matrix.cpp
	$(CC) $(CFLAGS) -c matrix.o matrix.cpp

clean:
	rm -rf *.o
