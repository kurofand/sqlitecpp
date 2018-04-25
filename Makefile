CC=c++

CFLAGS=-std=c++11 -lsqlite3

all:
	$(CC) $(CFLAGS) main.cpp -o sqlite
